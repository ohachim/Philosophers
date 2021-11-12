/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_watcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:59:23 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 17:14:42 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"


static int	divide_by_2(int num)
{
	if (!(num % 2))
		return (num / 2);
	return ((num / 2) + 1);
}

static void	swap(int a, int b, t_philo_queue *queue)
{
	t_philo_data	*temp;

	if (a == b)
		return;
	temp = queue->philo_array[a];
	queue->philo_array[a] = queue->philo_array[b];
	queue->philo_array[b] = temp;
}

static int	forks_used(t_philo_data* philo)
{
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

static void	swap_next_philo(t_philo_queue* queue)
{
	int j;

	j = (queue->front + 1) % queue->capacity;
	while (1)
	{
		swap(queue->front, j, queue);
		if (!forks_used(queue->philo_array[queue->front]))
			break;
		j = (j + 1) % queue->capacity;// should reboot at front, and should be modulo size not capacity
	}
}

void	*queue_watcher(void *args)
{
	int				nb_phil_half;
	t_philo_queue	*queue;

	queue = (t_philo_queue*)args;
	nb_phil_half = divide_by_2(queue->capacity);
	while (!g_terminate)
	{
		if (queue->size == nb_phil_half + (queue->capacity / 2))
		{
			// pthread_mutex_lock(&queue->lock);
			while (queue->size > nb_phil_half)// variable that tells us how much/when to dequeue
			{
				if (!forks_used(front(queue)))
					dequeue(queue);
				else
					swap_next_philo(queue);
			}
			// pthread_mutex_unlock(&queue->lock);
		}
		usleep(50);
	}
	return (NULL);
}
