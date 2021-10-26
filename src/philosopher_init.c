/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:21:10 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/26 16:53:44 by ohachim          ###   ########.fr       */
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
		params[i] = -1; // default NB_EATS value;
	params[TIME_TO_EAT] *= 1000;
	params[TIME_TO_SLEEP] *= 1000;
}

int	make_forks(int *params, t_fork **forks)
{
	int	i;

	i = 0;
	*forks = (t_fork*)malloc(sizeof(t_fork) * params[NB_FORKS]);
	if (!(*forks))
		return (BAD_ALLOC);
	while (i < params[NB_FORKS])
	{
		if (pthread_mutex_init(&((*forks)[i].fork_protect), NULL))
		{
			free(params); // questionable
			free(*forks);
			return (FAIL_MUTEX_INIT);// TODO: CHANGE
		}
		(*forks)[i].id = i;
		(*forks)[i].used = 0;
		++i;
	}
	return (0);
}

t_philo_data	**make_philosophers(int *params, t_fork *forks, struct timeval start_of_program)
{
	t_philo_data		**philosophers;
	pthread_mutex_t		*print_mutex;

	t_philo_queue		*queue;
	int					i;

	printf("starting init\n");
	i = 0;
	queue = create_queue(params[NB_PHILOSOPHERS]);
	philosophers = (t_philo_data**)malloc(sizeof(t_philo_data*)
											* params[NB_PHILOSOPHERS]);
	if (!philosophers)
		return (NULL);
	print_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(print_mutex, NULL))
		return (NULL);

	printf("%p, the adress of queue\n", queue);
	while (i < params[NB_PHILOSOPHERS])
	{
		philosophers[i] = (t_philo_data*)malloc(sizeof(t_philo_data) * params[NB_PHILOSOPHERS]);
		philosophers[i]->id = i + 1;
		philosophers[i]->number_eats = 0;// How many times it has eaten, 0 at start
		philosophers[i]->left_fork = &forks[i];
		philosophers[i]->params = params;
		philosophers[i]->print_mutex = print_mutex;
		philosophers[i]->start_of_program = start_of_program;
		philosophers[i]->should_eat = 0;
		philosophers[i]->queue = queue;
		enqueue(queue, philosophers[i]); // some high quality "spaghetti code" right here
		if (pthread_mutex_init(&philosophers[i]->death_mutex, NULL))
			return (NULL);
		if (i == params[NB_PHILOSOPHERS] - 1) // If this is the last philosopher, his right fork should be the 0th fork
			philosophers[i]->right_fork = &forks[0];
		else
			philosophers[i]->right_fork = &forks[(i + 1) % params[NB_FORKS]];
		++i;
	}
	printf("philo addreses in philosophers_init: \n");
	for (int i = 0; i < params[NB_PHILOSOPHERS]; i++)
	{
		printf("[%p]", philosophers[i]);
	}
	printf("\n");
	for (int i = 0; i < params[NB_PHILOSOPHERS]; i++)
	{
		printf("queue: [%p]", queue->philo_array[i]);
	}
	printf("\n");
	return (philosophers);
}
