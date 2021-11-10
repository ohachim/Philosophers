/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:07:21 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 17:42:32 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	del_philosophers(t_philo_data ***philosophers, int nb_philosophers)
{
	int	i;

	i = 0;
	pthread_mutex_destroy((*philosophers)[0]->print_mutex);
	del_mem((void **)&(*philosophers)[0]->print_mutex);
	while (i < nb_philosophers)
	{
		pthread_mutex_destroy(&(*philosophers)[i]->death_mutex);
		del_mem((void **)&(*philosophers)[i]);
		++i;
	}
	free(*philosophers);
	*philosophers = NULL;
}

void	clear_data(int **params, t_fork **forks, t_philo_data ***philosophers)
{
	if (*philosophers)
		del_philosophers(philosophers, (*params)[NB_PHILOSOPHERS]);
	if (*params)
		del_mem((void **)params);
	if (*forks)
		del_mem((void **)forks);
}

int	clear_and_exit(int **params, t_fork **forks, t_philo_data ***philosophers,
				int errno)
{
	clear_data(params, forks, philosophers);
	return (error(errno));
}

void	ft_init_data(int *errno, t_fork **forks, t_philo_data ***philosophers)
{
	*errno = 0;
	g_terminate = 0;
	g_philo_eat_goal = 0;
	*forks = NULL;
	*philosophers = NULL;
}

int	main(int argc, char **argv)
{
	int					*params;
	t_fork				*forks;
	t_philo_data		**philosophers;
	struct timeval		start_of_program;
	int					errno;

	ft_init_data(&errno, &forks, &philosophers);
	gettimeofday(&start_of_program, NULL);
	if (argc != 5 && argc != 6)
		return (error(BAD_PARAMETERS));
	params = (int *)malloc(sizeof(int) * argc - 1);
	if (!params)
		return (error(BAD_ALLOC));
	init_parameters(argv, params, argc);
	errno = make_forks(params, &forks);
	if (errno)
		return (clear_and_exit(&params, &forks, &philosophers, errno));
	philosophers = make_philosophers(params, forks, start_of_program);
	if (!philosophers) // Free the forks
		return (clear_and_exit(&params, &forks, &philosophers, errno));
	errno = start(philosophers, params);
	if (errno)
		return (clear_and_exit(&params, &forks, &philosophers, errno));
	return (EXIT_SUCCESS);
}
