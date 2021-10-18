/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:40:05 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/16 17:49:57 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

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

int				enqueue(t_philo_queue* queue, t_philo_data *philo)
{
	if (is_full(queue))
		return -1;

	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->philo_array[queue->rear] = philo;
	queue->size += 1;
	philo->should_eat = 0;
	return (1);
}

int		dequeue(t_philo_queue* queue)
{
	t_philo_data	*philo;

	if (is_empty(queue))
		return (-1);
	philo = queue->philo_array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size -= 1;
	printf("philo to open is [%d]\n", philo->id);
	philo->should_eat = 1;
	return (1); // Might removed, I only need to switch it's lights on
}

t_philo_queue	*create_queue(int capacity)
{
	t_philo_queue	*queue;
	pthread_mutex_t		*enqueue;
	pthread_mutex_t		*dequeue;

	if (!capacity || capacity < 0)
		return (NULL);
	enqueue = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	dequeue = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(enqueue, NULL) || pthread_mutex_init(dequeue, NULL))
		return (NULL);
	queue = (t_philo_queue*)malloc(sizeof(t_philo_queue));
	if (!queue || !enqueue || !dequeue)
		return (NULL);
	queue->capacity = capacity;
	queue->size = 0;
	queue->front = 0;
	queue->rear = capacity - 1;
	queue->dequeue_lock = dequeue;
	queue->enqueue_lock = enqueue;
	queue->philo_array = (t_philo_data**)malloc(sizeof(t_philo_data*) * capacity);
	if (!queue->philo_array)
		return (NULL);
	return (queue);
}