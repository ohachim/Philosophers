/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:21:10 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/18 05:14:40 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	init_parameters(char **argv, int *params, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		params[i] = my_atoi(argv[i + 1]);
		++i;
	}
	if (i == NB_EATS)
		params[i] = -1;
}

int	make_forks(int *params, t_fork **forks)
{
	int	i;

	i = 0;
	*forks = (t_fork *)malloc(sizeof(t_fork) * params[NB_FORKS]);
	if (!(*forks))
		return (BAD_ALLOC);
	while (i < params[NB_FORKS])
	{
		if (pthread_mutex_init(&((*forks)[i].fork_protect), NULL))
		{
			free(params);
			free(*forks);
			return (FAIL_MUTEX_INIT);
		}
		(*forks)[i].id = i;
		(*forks)[i].used = 0;
		++i;
	}
	return (0);
}

t_philo_data	*init_philosopher(int *params, t_fork *forks, int index,
					struct timeval start_of_program)
{
	t_philo_data	*philosopher;

	philosopher = (t_philo_data *)malloc(sizeof(t_philo_data)
			* params[NB_PHILOSOPHERS]);
	if (!philosopher)
		return (NULL);
	philosopher->id = index + 1;
	philosopher->number_eats = 0;
	philosopher->params = params;
	philosopher->should_eat = 0;
	philosopher->right_fork = &forks[index];
	philosopher->left_fork = &forks[(index + 1) % params[NB_FORKS]];
	philosopher->start_of_program = start_of_program;
	return (philosopher);
}

t_philo_data	**make_philosophers(int *params, t_fork *forks,
		struct timeval start_of_program)
{
	t_philo_data		**philosophers;
	pthread_mutex_t		*print_mutex;
	int					i;

	i = 0;
	philosophers = (t_philo_data **)malloc(sizeof(t_philo_data *)
			* params[NB_PHILOSOPHERS]);
	print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!philosophers || !print_mutex || pthread_mutex_init(print_mutex, NULL))
		return (NULL);
	while (i < params[NB_PHILOSOPHERS])
	{
		philosophers[i] = init_philosopher(params, forks, i, start_of_program);
		if (!philosophers[i]
			|| pthread_mutex_init(&philosophers[i]->death_mutex, NULL))
			return (NULL);
		philosophers[i]->print_mutex = print_mutex;
		++i;
	}
	return (philosophers);
}
