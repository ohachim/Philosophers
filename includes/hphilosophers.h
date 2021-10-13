/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hphilosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:14:39 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/13 11:21:17 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPHILOSOPHERS_H
# define HPHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

enum {
	BAD_ALLOC = 1,
	FAIL_MUTEX_INIT,
	BAD_PARAMETERS,
	BAD_JOIN,
	BAD_CREATE,
	BAD_DETACH
};

enum {
	NB_PHILOSOPHERS,
	NB_FORKS = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NB_EATS,
};

int		g_philo_eat_goal;
int		g_terminate;

typedef struct 		s_fork { // needs to be freed
	unsigned int	id; // TODO: not needed?
	pthread_mutex_t fork_protect; // needs to be destroyed
} 					t_fork;

typedef struct		s_philosopher_data { // needs to be freed
	unsigned int	id;
	int				number_eats;
	int				dead;
	struct timeval	start_of_program;
	struct timeval	last_eat_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				*params;
	pthread_mutex_t *print_mutex; // needs to be destroyed
	pthread_mutex_t death_mutex; // needs to be destroyed
}					t_philosopher_data;

int					my_atoi(char *str);
unsigned int		my_strlen(char *str); // currently not in use
char				*my_strdup(char *str); // currently not in use.
void				philo_think(t_philosopher_data *philo);
void				philo_sleep(t_philosopher_data *philo);
void				philo_eat(t_philosopher_data *philo);
int					start(t_philosopher_data *philosophers, int *params);
void				*routine(void *args);
void				*watch_philos(void *args);
t_philosopher_data	*make_philosophers(int *params, t_fork *forks, struct timeval start_of_program);
int					make_forks(int *params, t_fork **forks);
void				init_parameters(char **argv, int *params, int argc);
int					error(int errno);
void				mutex_print(char *action, t_philosopher_data *philo);
int					calculate_death(t_philosopher_data *philo);
void				print_time_stamp( struct timeval start_of_program );

#endif
