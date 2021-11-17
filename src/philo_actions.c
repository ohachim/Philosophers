/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:17:38 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/17 23:37:32 by ohachim          ###   ########.fr       */
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

int		forks_taken(t_philo_data *philo)
{
	int	boolean;

	pthread_mutex_lock(&philo->right_fork->fork_protect);
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	boolean = (philo->left_fork->used || philo->right_fork->used); 
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
	return (boolean);
}

int		is_last_user(t_philo_data *philo, t_fork *fork)
{
	int	boolean;

	pthread_mutex_lock(&philo->right_fork->fork_protect);
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	boolean = (philo->id == fork->last_user_id); 
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
	return (boolean);
}

void	take_forks(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_protect);
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	mutex_print("has taken a fork", philo, FALSE);
	philo->right_fork->used = 1;
	mutex_print("has taken a fork", philo, FALSE);
	philo->left_fork->used = 1;
	philo->right_fork->last_user_id = philo->id;
	philo->left_fork->last_user_id = philo->id;
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
}

void	drop_forks(t_philo_data *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_protect);
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	philo->right_fork->used = 0;
	philo->left_fork->used = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
}

void	prepare_to_eat(t_philo_data *philo)
{
	while (forks_taken(philo)
			|| is_last_user(philo, philo->left_fork)
			|| is_last_user(philo, philo->right_fork))
		usleep(20); // number of philosophers
	take_forks(philo);
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
