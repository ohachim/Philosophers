/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:07:21 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 16:05:41 by ohachim          ###   ########.fr       */
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


void	del_mem(void **mem_adress)
{
	free(*mem_adress);
	*mem_adress = NULL;
}

void	del_philosophers(t_philo_data ***philosophers, int nb_philosophers)
{
	int	i;

	i = 0;
	pthread_mutex_destroy((*philosophers)[0]->print_mutex);
	del_mem((void**)&(*philosophers)[0]->print_mutex);
	while (i < nb_philosophers)
	{
		pthread_mutex_destroy(&(*philosophers)[i]->death_mutex);
		del_mem((void**)&(*philosophers)[i]);
		++i;
	}
	free(*philosophers);
	*philosophers = NULL;
}

void	clear_data(int **params, t_fork **forks, t_philo_data ***philosophers)
{
	del_philosophers(philosophers, (*params)[NB_PHILOSOPHERS]);
	del_mem((void**)params);
	del_mem((void**)forks);
}

int	main(int argc, char **argv)
{
	int					*params;
	t_fork				*forks;
	t_philo_data		**philosophers; // could have been a one dimention array?????????
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
	errno = start(philosophers, params); // TODO: CREATE A QUEUE HERE, AND SEND IT TO START
	if (errno)
		return (error(errno));
	clear_data(&params, &forks, &philosophers);
	return (EXIT_SUCCESS);
}
	/*TODO: destroy *forks
	* free forks
	* destroy *print_mutex
	* free print_mutex
	* destroy death mutex
	* free philosophers
	*/
//0x7fde11402c38 0x7fde11402c80
//0x7fde11402c80 0x7fde11402cc8
//0x7fde11402cc8 0x7fde11402d10
//0x7fde11402d10 0x7fde11402d58
//0x7fde11402c38 0x7fde11402d58