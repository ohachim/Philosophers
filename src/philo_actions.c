/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:17:38 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/08 20:51:20 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	mutex_print(char *action, t_philo_data *philo)
{
		pthread_mutex_lock(philo->print_mutex);

		print_time_stamp(philo->start_of_program);
		printf("%d %s\n", philo->id, action);
		pthread_mutex_unlock(philo->print_mutex);
}

void	philo_eat(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	mutex_print("is eating", philo);
	gettimeofday(&philo->last_eat_time, NULL);
	usleep(philo->params[TIME_TO_EAT]);
	if (philo->params[NB_EATS] != -1)
	{
		philo->number_eats += 1;
		if (philo->number_eats == philo->params[NB_EATS])
			g_philo_eat_goal += 1;
	}
	pthread_mutex_unlock(&philo->death_mutex);
}

void	philo_sleep(t_philo_data *philo)
{
	mutex_print("is sleeping", philo);
	usleep(philo->params[TIME_TO_SLEEP]);
}

void	philo_think(t_philo_data *philo)
{
	mutex_print("is thinking", philo);
}