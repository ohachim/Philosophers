/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:18:53 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 17:00:13 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	*routine(void *args)
{
	t_philo_data		*philo;
	struct timeval		last_eat_time;
	pthread_t			watcher;

	philo = (t_philo_data*)args;
	gettimeofday(&last_eat_time, NULL);
	philo->last_eat_time = get_milliseconds(last_eat_time.tv_sec, last_eat_time.tv_usec);
	if (pthread_create(&watcher, NULL, death_watch, philo))
		return (NULL);
	while (1 && !g_terminate)
	{
		while (!philo->should_eat)
			usleep(10);
		philo_eat(philo);
		pthread_mutex_lock(&philo->queue->lock);
		enqueue(philo->queue, philo);
		pthread_mutex_unlock(&philo->queue->lock);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start(t_philo_data **philosophers, int *params)
{
	pthread_t 		philo_threads[params[NB_PHILOSOPHERS]];
	pthread_t		queue_thread;
	t_philo_queue	*queue;
	int			i;

	i = 0;
	g_terminate = 0;
	queue = philosophers[0]->queue;
	if (pthread_create(&queue_thread, NULL, queue_watcher, (void*)queue))
		return (BAD_CREATE);
	while (i < params[NB_PHILOSOPHERS])
	{
		if (pthread_create(&philo_threads[i], NULL, routine, (void*)philosophers[i]))
			return (BAD_CREATE);
		if (pthread_detach(philo_threads[i]))
			return (BAD_DETACH);
		++i;
	}
	pthread_join(queue_thread, NULL);
	return (0);
}
