/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:56:56 by ohachim           #+#    #+#             */
/*   Updated: 2021/12/08 16:38:33 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

static int	calculate_death(t_philo_data *philo)
{
	struct timeval	current_time;
	long			i;

	pthread_mutex_lock(&philo->death_mutex);
	gettimeofday(&current_time, NULL);
	i = get_milliseconds(current_time.tv_sec, current_time.tv_usec)
		- philo->last_eat_time;
	if (i > philo->params[TIME_TO_DIE])
	{
		mutex_print("died", philo);
		*(philo->terminate) = 1;
		pthread_mutex_unlock(&philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return (0);
}

void	*death_watch(void *args)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)args;
	while (!*(philo->terminate))
	{
		if (*(philo->philo_eat_goal) == philo->params[NB_PHILOSOPHERS])
			*(philo->terminate) = 1;
		calculate_death(philo);
		usleep(WAIT_TIME);
	}
	return (NULL);
}
