/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_resources.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:18:21 by ohachim           #+#    #+#             */
/*   Updated: 2021/12/08 16:47:29 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	destroy_mutexes(t_fork **forks, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&(*forks)[i].fork_protect);
		++i;
	}
}

void	del_forks(t_fork **forks, int nb_forks)
{
	destroy_mutexes(forks, nb_forks);
	del_mem((void **)forks);
}

void	del_philosophers(t_philo_data ***philosophers, int nb_philosophers)
{
	int	i;

	i = 0;
	if (nb_philosophers && *philosophers)
	{
		if ((*philosophers)[0] && (*philosophers)[0]->print_mutex)
			pthread_mutex_destroy((*philosophers)[0]->print_mutex);
		if (philosophers[0])
		{
			del_mem((void **)&((*philosophers)[0]->terminate));
			del_mem((void **)&((*philosophers)[0]->philo_eat_goal));
			del_mem((void **)&(*philosophers)[0]->print_mutex);
		}
		while ((*philosophers)[i] && i < nb_philosophers)
		{
			pthread_mutex_destroy(&(*philosophers)[i]->death_mutex);
			del_mem((void **)&(*philosophers)[i]);
			++i;
		}
	}
	free(*philosophers);
	*philosophers = NULL;
}
