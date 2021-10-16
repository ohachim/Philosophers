/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:07:21 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/16 16:51:37 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

//array of func for eating sleeping waiting thinking?
//any philosopher dies, simulation stops
//after sleep u think
//number of philosophers, time to die, time to eat, time to sleep, number of times each philosophers should eat
    //number of philosopher = number of philosophers but also number of forks
    //time to die = in milliseconds, if philosopher doesn't start eating [time to die] after a meal/beginning of game, it dies
    //time to eat = the time it takes a philosopher to eat, his forks are bloked at the time
    //time to sleep = time the philosopher will spend sleeping
    //number of times each philosopher should eat = optional, simulation stops after all philosophers eat at least [the number of times each philosopher should eat], if not specified, simulation stops when a philosopher dies

//time to die, should be calculated at the beginning of the program or after the philosopher eats?

int	main(int argc, char **argv)
{
	int					*params;
	t_fork				*forks;
	t_philo_data	*philosophers;
	struct timeval		start_of_program;
	int					errno;

	g_philo_eat_goal = 0;
	errno = 0;
	gettimeofday(&start_of_program, NULL);
	if (argc != 5 && argc != 6)
		return (error(BAD_PARAMETERS));
	params = (int*)malloc(sizeof(int) * argc - 1);
	if (!params)
		return (error(BAD_ALLOC));
	init_parameters(argv, params, argc);
	errno = make_forks(params, &forks);
	if (errno)
		return (error(errno));
	philosophers = make_philosophers(params, forks, start_of_program);
	if (!philosophers) // Free the forks
		return (error(BAD_ALLOC));
	errno = start(philosophers, params);
	if (errno)
		return (error(errno));
	return (EXIT_SUCCESS);
	/*TODO: destroy *forks
	* free forks
	* destroy *print_mutex
	* free print_mutex
	* destroy death mutex
	* free philosophers
	*/
}
//0x7fde11402c38 0x7fde11402c80
//0x7fde11402c80 0x7fde11402cc8
//0x7fde11402cc8 0x7fde11402d10
//0x7fde11402d10 0x7fde11402d58
//0x7fde11402c38 0x7fde11402d58