/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:18:53 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 16:22:38 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

int		calculate_death(t_philo_data *philo)
{
	struct timeval current_time;
	long i;
	
	pthread_mutex_lock(&philo->death_mutex);
	gettimeofday(&current_time, NULL);
	i = get_milliseconds(current_time.tv_sec, current_time.tv_usec)
		- philo->last_eat_time;
	if (i > philo->params[TIME_TO_DIE])
	{
		g_terminate = 1;
		mutex_print("dead", philo, TRUE);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return 0;
}

void	*death_watch(void *args)
{
	t_philo_data *philo;

	philo = (t_philo_data*)args;
	while (1)
	{
		if (calculate_death(philo)
			|| g_philo_eat_goal == philo->params[NB_PHILOSOPHERS])
			g_terminate = 1;
		usleep(10);
	}
	return NULL;
}
static void	take_forks(t_philo_data *philo)
{
	mutex_print("has taken a fork", philo, FALSE);
	mutex_print("has taken a fork", philo, FALSE);
}

int		forks_used(t_philo_data* philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	pthread_mutex_lock(&philo->right_fork->fork_protect);
	if (philo->left_fork->used || philo->right_fork->used)
	{
		pthread_mutex_unlock(&philo->left_fork->fork_protect);
		pthread_mutex_unlock(&philo->right_fork->fork_protect);
		return (1);
	}
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	return (0);
}

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

void	swap_next_philo(t_philo_queue* queue)
{
	int j;

	j = (queue->front + 1) % queue->capacity;
	while (1)
	{
		swap(queue->front, j, queue);
		if (!forks_used(queue->philo_array[queue->front]))
			break;
		j = (j + 1) % queue->capacity;
	}
}

int		divide_by_2(int num)
{
	if (!(num % 2))
		return (num / 2);
	return ((num / 2) + 1);
}

void	*queue_watcher(void *args)
{
	int				nb_phil_half;
	t_philo_queue	*queue;

	queue = (t_philo_queue*)args;
	nb_phil_half = divide_by_2(queue->capacity);
	// printf("queue created: queue_size %d, nb %d\n", queue->capacity, nb_phil_half);
	while (!g_terminate)
	{
		if (queue->size == nb_phil_half + (queue->capacity / 2))
		{
			pthread_mutex_lock(&queue->lock);
			while (queue->size > nb_phil_half)
			{
				if (!forks_used(front(queue)))
					dequeue(queue);
				else
					swap_next_philo(queue);
			}
			pthread_mutex_unlock(&queue->lock);
		}
		usleep(50);
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
