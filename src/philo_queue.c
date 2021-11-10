/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:40:05 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 16:14:25 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	print_queue(t_philo_queue *queue)
{
	int i;
	int written;

	i = queue->front;
	written = 0;
	while (written < queue->size)
	{
		printf("[%d]", queue->philo_array[i]->id);
		i = (i + 1) % queue->capacity;
		++written;
	}
	printf(" [queue size: %d, queue front: %d, queue rear: %d].\n", queue->size, queue->front, queue->rear);
}

int				is_full(t_philo_queue *queue)
{
	if (queue->size == queue->capacity)
		return (1);
	return (0);
}

int				is_empty(t_philo_queue *queue)
{
	if (!queue->size)
		return (1);
	return (0);
}

t_philo_data	*front(t_philo_queue *queue)
{
	if (is_empty(queue))
		return (NULL);
	return (queue->philo_array[queue->front]);
	
}

t_philo_data	*rear(t_philo_queue* queue)
{
	if (is_empty(queue))
		return (NULL);
	return (queue->philo_array[queue->rear]);
}

void			swap(int a, int b, t_philo_queue *queue)
{
	t_philo_data	*temp;

	if (a == b)
		return;
	temp = queue->philo_array[a];
	queue->philo_array[a] = queue->philo_array[b];
	queue->philo_array[b] = temp;
}

int				enqueue(t_philo_queue* queue, t_philo_data *philo)
{
	if (is_full(queue))
		return -1;
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	philo->left_fork->used = 0;
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
	pthread_mutex_lock(&philo->right_fork->fork_protect);
	philo->right_fork->used = 0;
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	philo->should_eat = 0;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->philo_array[queue->rear] = philo;
	queue->size += 1;
	return (1);
}

int		dequeue(t_philo_queue* queue)
{
	t_philo_data	*philo;

	if (is_empty(queue))
		return (-1);
	philo = queue->philo_array[queue->front];
	mutex_print("has taken a fork", philo, FALSE);
	pthread_mutex_lock(&philo->left_fork->fork_protect);
	mutex_print("has taken a fork", philo, FALSE);
	pthread_mutex_lock(&philo->right_fork->fork_protect);
	philo->left_fork->used = 1;
	philo->right_fork->used = 1;
	pthread_mutex_unlock(&philo->left_fork->fork_protect);
	pthread_mutex_unlock(&philo->right_fork->fork_protect);
	philo->should_eat = 1;
	queue->size -= 1;
	queue->front = (queue->front + 1) % queue->capacity;
	return (1); // Might remove, I only need to switch it's lights on
}

t_philo_queue	*create_queue(int capacity)
{
	t_philo_queue	*queue;

	if (capacity <= 0)
		return (NULL);
	queue = (t_philo_queue*)malloc(sizeof(t_philo_queue));
	if (!queue)
		return (NULL);
	queue->capacity = capacity;
	queue->size = 0;
	queue->front = 0;
	queue->rear = capacity - 1;
	if (pthread_mutex_init(&queue->lock, NULL) || pthread_mutex_init(&queue->lock, NULL))
		return (NULL);
	queue->philo_array = (t_philo_data**)malloc(sizeof(t_philo_data*) * capacity);
	if (!queue->philo_array)
		return (NULL);
	return (queue);
}

