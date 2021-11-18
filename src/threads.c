/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:18:53 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/18 16:09:10 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	*routine(void *args)
{
	t_philo_data		*philo;
	struct timeval		last_eat_time;
	pthread_t			watcher;

	philo = (t_philo_data *)args;
	gettimeofday(&last_eat_time, NULL);
	philo->last_eat_time = get_milliseconds(last_eat_time.tv_sec,
			last_eat_time.tv_usec);
	if (pthread_create(&watcher, NULL, death_watch, philo))
		g_terminate = 1;
	while (!g_terminate)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start(t_philo_data **philosophers, int *params)
{
	pthread_t	*philo_threads;
	int			i;

	i = 0;
	g_terminate = 0;
	philo_threads = (pthread_t *)malloc(sizeof(pthread_t)
			* params[NB_PHILOSOPHERS]);
	if (!philo_threads)
		return (BAD_ALLOC);
	if (!params[NB_PHILOSOPHERS] || !params[NB_EATS])
		return (BAD_PARAMETERS);
	while (i < params[NB_PHILOSOPHERS])
	{
		if (pthread_create(&philo_threads[i], NULL,
				routine, (void*)philosophers[i]))
			return (BAD_CREATE);
		if (pthread_detach(philo_threads[i]))
			return (BAD_DETACH);
		++i;
	}
	while (!g_terminate)
		usleep(WAIT_TIME);
	del_mem((void **)&philo_threads);
	return (0);
}
