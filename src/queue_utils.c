/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:05:25 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 17:06:04 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

int	is_full(t_philo_queue *queue)
{
	if (queue->size == queue->capacity)
		return (1);
	return (0);
}

int	is_empty(t_philo_queue *queue)
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
