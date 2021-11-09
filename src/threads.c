/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:18:53 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/09 15:05:31 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"



int		calculate_death(t_philo_data *philo)
{
	struct timeval current_time;
	long i;
	
	pthread_mutex_lock(&philo->death_mutex);
	gettimeofday(&current_time, NULL);
	i = get_milliseconds(current_time.tv_sec, current_time.tv_usec) -
	get_milliseconds(philo->last_eat_time.tv_sec, philo->last_eat_time.tv_usec);
	if (i > philo->params[TIME_TO_DIE])
	{
		philo->dead = 1; // check what's needed.
		print_time_stamp(philo->start_of_program);
		printf(" diffrence %ld, philo id %d\n", i, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return 0;
}

void	*death_watch(void *args)
{
	t_philo_data *philo;
	philo = (t_philo_data*)args;

	while (1)
	{
		if (calculate_death(philo)
			|| g_philo_eat_goal == philo->params[NB_PHILOSOPHERS])
		{
			exit(0); // for now;
		}
		usleep(200);
	}
	return NULL;
}
static void	take_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork,
					t_philo_data *philo)
{
	// mutex_print("wating for first fork", philo);
	// pthread_mutex_lock(first_fork);
	mutex_print("has taken the first fork", philo);
	// mutex_print("wating for second fork", philo);
	// pthread_mutex_lock(second_fork);
	mutex_print("has taken the second fork", philo);
}

static void	drop_forks(pthread_mutex_t *first_fork, pthread_mutex_t *second_fork,
					t_philo_data *philo)
{
	// pthread_mutex_unlock(first_fork);
	// mutex_print("has dropped the first fork", philo);
	// pthread_mutex_unlock(second_fork);
	// mutex_print("has dropped the second fork", philo);
}

int		forks_used(t_philo_data* philo)
{
	// printf("checked philo->id forks: %d", philo->id);
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	pthread_mutex_lock(&philo->right_fork->fork_protect);
	if (philo->left_fork->used || philo->right_fork->used)
	{
		pthread_mutex_unlock(&philo->left_fork->fork_protect);
		pthread_mutex_unlock(&philo->right_fork->fork_protect);
		return (1);
	}
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	return (0);
}

void	*routine(void *args)
{
	t_philo_data		*philo;
	pthread_t			watcher;
	t_fork				*first_fork; // TODO: no need
	t_fork				*second_fork; // TODO: no need

	philo = (t_philo_data*)args;
	first_fork = philo->right_fork;
	second_fork = philo->left_fork;

	gettimeofday(&philo->last_eat_time, NULL);

	if (pthread_create(&watcher, NULL, death_watch, philo))
		return (NULL); // TODO: INSTANTANIOUS START
	while (1)
	{
		while (!philo->should_eat) // LOCK A MUTEX INSTEAD? probably not, shoudl unlock and in same thread it was locked
			usleep(200);
		take_forks(&first_fork->fork_protect, &second_fork->fork_protect, philo); // might make fork protect dynamiclly allocated
		philo_eat(philo);
		pthread_mutex_lock(&philo->queue->lock);
		enqueue(philo->queue, philo);
		pthread_mutex_unlock(&philo->queue->lock);
		drop_forks(&first_fork->fork_protect, &second_fork->fork_protect, philo);
		philo_sleep(philo);
		philo_think(philo);
		// TODO: WHEN TO EXIT
	}
	return (NULL);
}

// //TODO: to remove rear
void	print_queue(t_philo_queue *queue)
{
	int i;
	int written;

	i = queue->front;
	written = 0;
	while (written < queue->size)
	{
		// printf("[%d]", queue->philo_array[i]->id);
		i = (i + 1) % queue->capacity;
		++written;
	}
	// printf(" [queue size: %d, queue front: %d, queue rear: %d].\n", queue->size, queue->front, queue->rear);
}

void	swap_next_philo(t_philo_queue* queue) // too much power?
{
	int j;

	j = (queue->front + 1) % queue->capacity;
	// this loop should be able to loop through all the queue
	while (1)
	{
		// printf("before swap: ");
		// print_queue(queue);
		swap(queue->front, j, queue);
		// printf("indexes swapped are: %d %d==> after swap: ", queue->front, j);
		// print_queue(queue);
		if (!forks_used(queue->philo_array[queue->front]))
			break;
		j = (j + 1) % queue->capacity;
	}
}

int		divide_by_2(int num)
{
	if (!(num % 2))
		return (num / 2);
	return ((num / 2) + 1);
}

void	*queue_watcher(void *args)
{
	int	nb_phil_half;
	t_philo_queue *queue = (t_philo_queue*)args;

	nb_phil_half = divide_by_2(queue->capacity);
	while (1)
	{
		if (queue->size == nb_phil_half + (queue->capacity / 2))
		{
			pthread_mutex_lock(&queue->lock);
			print_queue(queue);
			while (queue->size > nb_phil_half)
			{
				if (!forks_used(front(queue)))
				{
					printf("dequeue id %d \n", front(queue)->id);
					dequeue(queue);
				}
				else
					swap_next_philo(queue);
			}
			pthread_mutex_unlock(&queue->lock);
		}
		usleep(200);
	}
	return (NULL);
}

int	start(t_philo_data **philosophers, int *params)
{
	pthread_t 		philo_threads[params[NB_PHILOSOPHERS]];
	pthread_t		queue_thread;
	t_philo_queue	*queue;
	int			i;

	i = 0;
	g_terminate = 0;
	queue = philosophers[0]->queue;
	if (pthread_create(&queue_thread, NULL, queue_watcher, (void*)queue))
		return (BAD_CREATE);
	while (i < params[NB_PHILOSOPHERS])
	{
		if (pthread_create(&philo_threads[i], NULL, routine, (void*)philosophers[i]))
			return (BAD_CREATE);
		if (pthread_detach(philo_threads[i]))
			return (BAD_DETACH);
		++i;
	}
	pthread_join(queue_thread, NULL);
	return (0);
}
