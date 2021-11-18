/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:17:38 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/18 04:28:38 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	mutex_print(char *action, t_philo_data *philo, int lock)
{
	pthread_mutex_lock(philo->print_mutex);
	print_time_stamp(philo->start_of_program);
	ft_putnbr(philo->id);
	ft_putchar(' ');
	ft_putstr(action);
	ft_putchar('\n');
	if (!lock)
		pthread_mutex_unlock(philo->print_mutex);
}

void	philo_eat(t_philo_data *philo)
{
	struct timeval	last_eat;

	prepare_to_eat(philo);
	take_forks(philo);
	pthread_mutex_lock(&philo->death_mutex);
	gettimeofday(&last_eat, NULL);
	mutex_print("is eating", philo, FALSE);
	philo->last_eat_time = get_milliseconds(last_eat.tv_sec, last_eat.tv_usec);
	ft_usleep(philo->params[TIME_TO_EAT]);
	drop_forks(philo);
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
	mutex_print("is sleeping", philo, FALSE);
	ft_usleep(philo->params[TIME_TO_SLEEP]);
}

void	philo_think(t_philo_data *philo)
{
	mutex_print("is thinking", philo, FALSE);
}
