/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 16:40:05 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/19 21:23:27 by ohachim          ###   ########.fr       */
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
	printf("Enqueed philo num: %d\n", philo->id);
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
	printf("dequeed philo num: %d\n", philo->id);
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size -= 1;
	philo->should_eat = 1;
	return (1); // Might removed, I only need to switch it's lights on
}

t_philo_queue	*create_queue(int capacity)
{
	t_philo_queue	*queue;

	if (!capacity || capacity < 0)
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

// two queues, one with pair philos, one with even ones