/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hphilosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:14:39 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/29 00:44:55 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HPHILOSOPHERS_H
# define HPHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define FALSE 0
# define TRUE 1

# define WAIT_TIME 100

enum {
	BAD_ALLOC = 1,
	FAIL_MUTEX_INIT,
	BAD_PARAMS,
	BAD_JOIN,
	BAD_CREATE,
	BAD_DETACH,
	BAD_PHILOSOPHERS,
	ZERO_PHILOSOPHERS,
	TOTAL
};

enum {
	NB_PHILOSOPHERS,
	NB_FORKS = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NB_EATS,
};

typedef struct s_fork {
	int				used;
	unsigned int	last_user_id;
	pthread_mutex_t	fork_protect;
}				t_fork;

typedef struct s_philo_data {
	unsigned int			id;
	unsigned int			last_eat_time;
	int						number_eats;
	int						*terminate;
	int						*philo_eat_goal;
	int						*params;
	unsigned int			start_program;
	t_fork					*left_fork;
	t_fork					*right_fork;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			death_mutex;
}				t_philo_data;

int					my_atoi(char *str);
unsigned int		my_strlen(char *str);
void				philo_think(t_philo_data *philo);
void				philo_sleep(t_philo_data *philo);
void				philo_eat(t_philo_data *philo);
int					start(t_philo_data **philosophers, int *params);
t_philo_data		**make_philosophers(int *params, t_fork *forks,
						struct timeval start_of_program);
int					make_forks(int *params, t_fork **forks);
void				init_parameters(char **argv, int *params, int argc);
int					error(int errno);
void				mutex_print(char *action, t_philo_data *philo);
int					calculate_death(t_philo_data *philo);
void				print_time_stamp(unsigned int start_of_program);
unsigned int		get_milliseconds(unsigned int seconds,
						unsigned int microseconds);
void				ft_usleep(unsigned int time);
void				ft_putnbr(long long num);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				*death_watch(void *args);
int					calculate_death(t_philo_data *philo);
void				del_mem(void **mem_adress);
void				take_forks(t_philo_data *philo);
void				drop_forks(t_philo_data *philo);
int					forks_taken(t_philo_data *philo);
int					is_last_user(t_philo_data *philo, t_fork *fork);
int					try_take_forks(t_philo_data *philo);
void				destroy_mutexes(t_fork **forks, int index);
void				del_philosophers(t_philo_data ***philosophers,
						int nb_philosophers);

#endif
