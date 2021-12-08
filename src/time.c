/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:42:31 by ohachim           #+#    #+#             */
/*   Updated: 2021/12/08 16:37:50 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

unsigned int	get_milliseconds(unsigned int seconds,
		unsigned int microseconds)
{
	return ((seconds * 1000) + (microseconds / 1000));
}

void	print_time_stamp(unsigned int start_of_program)
{
	struct timeval	current_time;
	unsigned int	end;

	gettimeofday(&current_time, NULL);
	end = get_milliseconds(current_time.tv_sec, current_time.tv_usec);
	ft_putchar('[');
	ft_putnbr(end - start_of_program);
	ft_putchar(']');
	ft_putchar('\t');
}

static unsigned int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (get_milliseconds(current_time.tv_sec, current_time.tv_usec));
}

void	ft_usleep(unsigned int time)
{
	unsigned int	start;

	start = get_current_time();
	while (start + time > get_current_time())
		usleep(10);
}
