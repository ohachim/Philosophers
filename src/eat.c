/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 03:59:07 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/18 04:52:34 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

int	forks_taken(t_philo_data *philo)
{
	int	boolean;

	pthread_mutex_lock(&philo->right_fork->fork_protect);
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	boolean = (philo->left_fork->used || philo->right_fork->used);
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
	return (boolean);
}

int	is_last_user(t_philo_data *philo, t_fork *fork)
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
		usleep(WAIT_TIME);
	take_forks(philo);
}
