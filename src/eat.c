/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 03:59:07 by ohachim           #+#    #+#             */
/*   Updated: 2021/12/08 16:41:01 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

static int	forks_taken(t_philo_data *philo)
{
	return (philo->left_fork->used || philo->right_fork->used);
}

static int	is_last_user(t_philo_data *philo, t_fork *fork)
{
	return (philo->id == fork->last_user_id);
}

void	take_forks(t_philo_data *philo)
{
	mutex_print("has taken a fork", philo);
	philo->right_fork->used = 1;
	mutex_print("has taken a fork", philo);
	philo->left_fork->used = 1;
}

void	drop_forks(t_philo_data *philo)
{
	philo->right_fork->last_user_id = philo->id;
	philo->left_fork->last_user_id = philo->id;
	philo->right_fork->used = 0;
	philo->left_fork->used = 0;
}

int	try_take_forks(t_philo_data *philo)
{
	int	boolean;

	boolean = 0;
	if (!*(philo->terminate) && philo->right_fork != philo->left_fork)
	{
		pthread_mutex_lock(&philo->right_fork->fork_protect);
		pthread_mutex_lock(&philo->left_fork->fork_protect);
		boolean = (!forks_taken(philo) && !is_last_user(philo, philo->left_fork)
				&& !is_last_user(philo, philo->right_fork));
		if (boolean)
			take_forks(philo);
		pthread_mutex_unlock(&philo->right_fork->fork_protect);
		pthread_mutex_unlock(&philo->left_fork->fork_protect);
	}
	return (!boolean);
}
