/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:18:53 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/13 13:03:30 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

long    get_milliseconds(unsigned int seconds, unsigned int microseconds) // should be unsigned?
{
    return(seconds * 1000 + microseconds / 1000);
}

void	print_time_stamp( struct timeval start_of_program )
{
	struct timeval current_time;
	long start;
	long end;
	gettimeofday(&current_time, NULL);
	
	start = get_milliseconds(start_of_program.tv_sec, start_of_program.tv_usec);
	end = get_milliseconds(current_time.tv_sec, current_time.tv_usec);
	printf("[%ld] ", end - start);
}

int		calculate_death(t_philosopher_data *philo)
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
		printf("diffrence %ld, philo id %d\n", i, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return 0;
}

void	*watch_philos(void *args)
{
	t_philosopher_data 	*philo;
	int			*params;

	philo = (t_philosopher_data*)args;
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
// 					t_philosopher_data *philo)
// {
// 	pthread_mutex_lock(first_fork);
// 	mutex_print("has taken a fork", philo);
// 	pthread_mutex_lock(second_fork);
// 	mutex_print("has taken a fork", philo);
// }

void	*death_watch(void *args)
{
	t_philosopher_data *philo;
	philo = (t_philosopher_data*)args;

	while (1)
	{
		if (calculate_death(philo)
			|| g_philo_eat_goal == philo->params[NB_PHILOSOPHERS])
		{
			g_terminate = 1;
			break;
		}
	}
	return NULL;
}
void	*routine(void *args)
{
	t_philosopher_data *philo;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	philo = (t_philosopher_data*)args;
	first_fork = (philo->right_fork->id < philo->left_fork->id)
					? &(philo->right_fork->fork_protect)
					: &(philo->left_fork->fork_protect);

	second_fork =  (philo->right_fork->id > philo->left_fork->id)
					? &(philo->right_fork->fork_protect)
					: &(philo->left_fork->fork_protect);
	gettimeofday(&philo->last_eat_time, NULL);
	while (1)
	{
		if (g_terminate || philo->dead)
			break;
		mutex_print("has taken the second fork", philo);
		pthread_mutex_lock(first_fork);
		pthread_mutex_lock(second_fork);
		mutex_print("has taken the first fork", philo);
		philo_eat(philo);
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}


int	start(t_philosopher_data *philosophers, int *params)
{
	pthread_t 	philo[params[NB_PHILOSOPHERS]];
	pthread_t	watcher;
	int			i;

	i = 0;
	g_terminate = 0;
	while (i < params[NB_PHILOSOPHERS])
	{
		if (pthread_create(&philo[i], NULL, routine, (void*)&philosophers[i]))
			return (BAD_CREATE);
		// if (pthread_detach(philo[i]))
		// 	return (BAD_DETACH);
		++i;
	}
	if (pthread_create(&watcher, NULL, watch_philos, (void*)philosophers))
		return (BAD_CREATE);
	while (g_terminate == 0){usleep(1000)};
	return (0);
}
