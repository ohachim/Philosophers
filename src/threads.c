/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:18:53 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/20 15:29:48 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

unsigned int    get_milliseconds(unsigned int seconds, unsigned int microseconds) // should be unsigned?
{
    return((seconds * 1000) + (microseconds / 1000));
}

void	print_time_stamp( struct timeval start_of_program )
{
	struct timeval current_time;
	unsigned int start;
	unsigned int end;

	gettimeofday(&current_time, NULL);
	start = get_milliseconds(start_of_program.tv_sec, start_of_program.tv_usec);
	end = get_milliseconds(current_time.tv_sec, current_time.tv_usec);
	printf("[%u]\t", end - start);
}

int		calculate_death(t_philo_data *philo)
{
	struct timeval current_time;
	long i;
	
	pthread_mutex_lock(&philo->death_mutex);
	gettimeofday(&current_time, NULL);
	i = get_milliseconds(current_time.tv_sec, current_time.tv_usec) -
	get_milliseconds(philo->last_eat_time.tv_sec, philo->last_eat_time.tv_usec);
	if (i > philo->params[TIME_TO_DIE])
	{
		philo->dead = 1; // check what's needed.
		print_time_stamp(philo->start_of_program);
		printf(" diffrence %ld, philo id %d\n", i, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return 0;
}

void	*watch_philos(void *args)
{
	t_philo_data 	*philo;
	int			*params;

	philo = (t_philo_data*)args;
	params = philo->params;
	
	while (1)
	{
		if (g_philo_eat_goal == params[NB_PHILOSOPHERS])
			return (NULL);
		if (calculate_death(philo))
		{
			printf("%d died\n", philo->id);
			g_terminate = 1;
			return (NULL);
		}
	}
	return (NULL);
}

// static void	take_fork(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork,
// 					t_philo_data *philo)
// {
// 	pthread_mutex_lock(first_fork);
// 	mutex_print("has taken a fork", philo);
// 	pthread_mutex_lock(second_fork);
// 	mutex_print("has taken a fork", philo);
// }

void	*death_watch(void *args)
{
	t_philo_data *philo;
	philo = (t_philo_data*)args;

	while (1)
	{
		if (calculate_death(philo)
			|| g_philo_eat_goal == philo->params[NB_PHILOSOPHERS])
		{
			exit(0); // for now;
		}
		usleep(200);
	}
	return NULL;
}
void	*routine(void *args)
{
	t_philo_data *philo;
	pthread_t			watcher;
	t_fork	*first_fork;
	t_fork	*second_fork;

	philo = (t_philo_data*)args;
	first_fork = (philo->right_fork->id < philo->left_fork->id)
					? (philo->right_fork)
					: (philo->left_fork);

	second_fork =  (philo->right_fork->id > philo->left_fork->id)
					? (philo->right_fork)
					: (philo->left_fork);
	gettimeofday(&philo->last_eat_time, NULL);
	if (pthread_create(&watcher, NULL, death_watch, philo))
		return (NULL);
	while (1)
	{
		while (!philo->should_eat)
		{
		}
		mutex_print("wating for first fork", philo);
		pthread_mutex_lock(&first_fork->fork_protect);
		first_fork->used = 1;
		mutex_print("has taken the first fork", philo);
		mutex_print("wating for second fork", philo);
		pthread_mutex_lock(&second_fork->fork_protect);
		second_fork->used = 1;
		mutex_print("has taken the second fork", philo);
		philo_eat(philo);
		pthread_mutex_unlock(&first_fork->fork_protect);
		first_fork->used = 0;
		mutex_print("has dropped the first fork", philo);
		pthread_mutex_unlock(&second_fork->fork_protect);
		second_fork->used = 0;
		mutex_print("has dropeed the second fork", philo);
		pthread_mutex_lock(&philo->queue->lock);
		enqueue(philo->queue, philo);
		pthread_mutex_unlock(&philo->queue->lock);
		philo->should_eat = 0; // should maybe add it to enqueue
		philo_sleep(philo);
		philo_think(philo);
		// add it to rear of queue
	}
	return (NULL);
}

void	*queue_watcher(void *args)
{
	int i;
	
	t_philo_data *philo = (t_philo_data*)args;
	while (1) // need to find out how to stop it
	{
		i = 0;
		printf(" queue size: %d\n", philo->queue->size);
		if (!is_empty(philo->queue) && !(front(philo->queue))->left_fork->used && !(front(philo->queue))->right_fork->used)
		{
			pthread_mutex_lock(&philo->queue->lock);
			printf("will dequeue odd\n");
			dequeue(philo->queue);
			pthread_mutex_unlock(&philo->queue->lock);
		}
		usleep(200);
	}
	return (NULL);
}

int	start(t_philo_data *philosophers, int *params)
{
	pthread_t 	philo[params[NB_PHILOSOPHERS]];
	pthread_t	queue;
	int			i;

	i = 0;
	g_terminate = 0;
	printf("do I get here\n");
	if (pthread_create(&queue, NULL, queue_watcher, (void*)&(philosophers[i])))
		return (BAD_CREATE);
	while (i < params[NB_PHILOSOPHERS])
	{
		if (pthread_create(&philo[i], NULL, routine, (void*)&philosophers[i]))
			return (BAD_CREATE);
		if (pthread_detach(philo[i]))
			return (BAD_DETACH);
		++i;
	}
	pthread_join(queue, NULL);
	return (0);
}
