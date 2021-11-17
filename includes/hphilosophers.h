/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hphilosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 14:14:39 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/17 23:20:47 by ohachim          ###   ########.fr       */
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

int						g_philo_eat_goal; // member variable of philo
int						g_terminate; // member variable of philo

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
typedef struct s_philo_queue {
	int					size;
	int					front;
	int					rear;
	pthread_mutex_t		lock;
	unsigned int		capacity;
	t_philo_data		**philo_array;
}				t_philo_queue;

int					my_atoi(char *str);
unsigned int		my_strlen(char *str); // currently not in use
char				*my_strdup(char *str); // currently not in use.
void				philo_think(t_philo_data *philo);
void				philo_sleep(t_philo_data *philo);
void				philo_eat(t_philo_data *philo);
int					start(t_philo_data **philosophers, int *params);
void				*routine(void *args);
void				*watch_philos(void *args);
t_philo_data		**make_philosophers(int *params, t_fork *forks,
						struct timeval start_of_program);
int					make_forks(int *params, t_fork **forks);
void				init_parameters(char **argv, int *params, int argc);
int					error(int errno);
void				mutex_print(char *action, t_philo_data *philo, int lock);
int					calculate_death(t_philo_data *philo);
void				print_time_stamp(struct timeval start_of_program);
t_philo_queue		*create_queue(int capacity);
int					dequeue(t_philo_queue *queue);
int					enqueue(t_philo_queue *queue, t_philo_data *philo);
int					is_full(t_philo_queue *queue);
int					is_empty(t_philo_queue *queue);
t_philo_data		*front(t_philo_queue *queue);
t_philo_data		*rear(t_philo_queue *queue);
unsigned int		get_milliseconds(unsigned int seconds,
						unsigned int microseconds);
void				ft_usleep(unsigned int time);
void				ft_putnbr(long long num);
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				*death_watch(void *args);
int					calculate_death(t_philo_data *philo);
void				*queue_watcher(void *args);
void				del_mem(void **mem_adress);
#endif
