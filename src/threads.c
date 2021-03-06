/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:18:53 by ohachim           #+#    #+#             */
/*   Updated: 2021/12/02 19:35:14 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

static void	*routine(void *args)
{
	t_philo_data		*philo;
	struct timeval		last_eat_time;
	pthread_t			watcher;

	philo = (t_philo_data *)args;
	gettimeofday(&last_eat_time, NULL);
	philo->last_eat_time = get_milliseconds(last_eat_time.tv_sec,
			last_eat_time.tv_usec);
	if (pthread_create(&watcher, NULL, death_watch, philo))
		*(philo->terminate) = WATCHER_CREATE_FAIL;
	while (!*(philo->terminate))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static int	free_threads(pthread_t **threads, int num_threads,
				int *terminate, int errno)
{
	int	i;
	int	ret;

	i = 0;
	if (errno != TOTAL)
		*terminate = 1;
	ret = errno;
	while (i < num_threads)
	{
		if (pthread_join((*threads)[i], NULL))
			ret = BAD_JOIN;
		i++;
	}
	del_mem((void **)threads);
	if (*terminate == WATCHER_CREATE_FAIL)
		return (BAD_CREATE);
	return (ret);
}

void	setup_philo_threads(t_philo_data **philosophers,
		pthread_t **philo_threads, int *params)
{
	int	*terminate;
	int	*philo_eat_goal;
	int	i;

	i = -1;
	terminate = malloc(sizeof(*terminate));
	philo_eat_goal = malloc(sizeof(*philo_eat_goal));
	*philo_threads = malloc(sizeof(**philo_threads)
			* params[NB_PHILOSOPHERS]);
	if (!terminate || !philo_eat_goal || !philo_threads)
	{
		del_mem((void **)&terminate);
		del_mem((void **)&philo_eat_goal);
		del_mem((void **)philo_threads);
		return ;
	}
	*terminate = 0;
	*philo_eat_goal = 0;
	while (++i < params[NB_PHILOSOPHERS])
	{
		philosophers[i]->terminate = terminate;
		philosophers[i]->philo_eat_goal = philo_eat_goal;
	}
}

int	start(t_philo_data **philosophers, int *params)
{
	pthread_t	*philo_threads;
	int			i;

	i = 0;
	setup_philo_threads(philosophers, &philo_threads, params);
	if (!philo_threads)
		return (BAD_ALLOC);
	while (i < params[NB_PHILOSOPHERS])
	{
		if (pthread_create(&philo_threads[i], NULL,
				routine, (void*)philosophers[i]))
			return (free_threads(&philo_threads, i,
					philosophers[0]->terminate, BAD_CREATE));
		++i;
	}
	return (free_threads(&philo_threads, i, philosophers[0]->terminate, TOTAL));
}
