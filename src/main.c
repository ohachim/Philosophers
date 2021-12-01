/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:07:21 by ohachim           #+#    #+#             */
/*   Updated: 2021/12/01 23:17:09 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	clear_data(int **params, t_fork **forks, t_philo_data ***philosophers)
{
	if (*philosophers)
		del_philosophers(philosophers, (*params)[NB_PHILOSOPHERS]);
	if (*forks)
		del_mem((void **)forks);
	if (*params)
		del_mem((void **)params);
}

int	clear_and_exit(int **params, t_fork **forks, t_philo_data ***philosophers,
				int errno)
{
	clear_data(params, forks, philosophers);
	if (errno != TOTAL)
		return (error(errno));
	return (EXIT_SUCCESS);
}

void	ft_init_data(int *errno, t_fork **forks, t_philo_data ***philosophers)
{
	*errno = 0;
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
		return (error(BAD_PARAMS));
	params = malloc(sizeof(*params) * argc);
	if (!params)
		return (error(BAD_ALLOC));
	init_parameters(argv, params, argc);
	if (!params[NB_PHILOSOPHERS] || !params[NB_EATS]
		|| params[NB_PHILOSOPHERS] == 1)
		return (clear_and_exit(&params, &forks, &philosophers, BAD_PARAMS));
	errno = make_forks(params, &forks);
	if (errno)
		return (clear_and_exit(&params, &forks, &philosophers, errno));
	philosophers = make_philosophers(params, forks, start_of_program);
	if (!philosophers)
		return (clear_and_exit(&params, &forks, &philosophers,
				BAD_PHILOSOPHERS));
	errno = start(philosophers, params);
	return (clear_and_exit(&params, &forks, &philosophers, errno));
}
