/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hphilosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:14:39 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/18 05:12:40 by ohachim          ###   ########.fr       */
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
# define WAIT_TIME_DEATH 10

enum {
	BAD_ALLOC = 1,
	FAIL_MUTEX_INIT,
	BAD_PARAMETERS,
	BAD_JOIN,
	BAD_CREATE,
	BAD_DETACH,
	BAD_PHILOSOPHERS
};

enum {
	NB_PHILOSOPHERS,
	NB_FORKS = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NB_EATS,
};

int						g_philo_eat_goal;
int						g_terminate;

typedef struct s_fork {
	unsigned int	id;
	int				used;
	short			last_user_id;
	pthread_mutex_t	fork_protect;
}				t_fork;

typedef struct s_philo_data {
	unsigned int			id;
	int						number_eats;
	int						dead;
	struct timeval			start_of_program;
	unsigned int			last_eat_time;
	int						should_eat;
	char					hand;
	t_fork					*left_fork;
	t_fork					*right_fork;
	int						*params;
	pthread_mutex_t			*print_mutex;
	pthread_mutex_t			death_mutex;
	struct s_philo_queue	*queue;
}				t_philo_data;
int					my_atoi(char *str);
unsigned int		my_strlen(char *str); // currently not in use
void				philo_think(t_philo_data *philo);
void				philo_sleep(t_philo_data *philo);
void				philo_eat(t_philo_data *philo);
int					start(t_philo_data **philosophers, int *params);
void				*routine(void *args);
t_philo_data		**make_philosophers(int *params, t_fork *forks,
						struct timeval start_of_program);
int					make_forks(int *params, t_fork **forks);
void				init_parameters(char **argv, int *params, int argc);
int					error(int errno);
void				mutex_print(char *action, t_philo_data *philo, int lock);
int					calculate_death(t_philo_data *philo);
void				print_time_stamp(struct timeval start_of_program);
unsigned int		get_milliseconds(unsigned int seconds,
						unsigned int microseconds);
void				ft_usleep(unsigned int time);
void				ft_putnbr(long long num);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				*death_watch(void *args);
int					calculate_death(t_philo_data *philo);
void				del_mem(void **mem_adress);
void				prepare_to_eat(t_philo_data *philo);
void				take_forks(t_philo_data *philo);
void				drop_forks(t_philo_data *philo);
int					forks_taken(t_philo_data *philo);
int					is_last_user(t_philo_data *philo, t_fork *fork);
#endif
