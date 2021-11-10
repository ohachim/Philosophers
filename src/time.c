/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:42:31 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 14:27:06 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

static unsigned int	get_time(void)
{
	struct timeval	tv;
	long			end;

	gettimeofday(&tv, NULL);
	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	return (end);
}

unsigned int    get_milliseconds(unsigned int seconds, unsigned int microseconds) // should be unsigned?
{
    return((seconds * 1000) + (microseconds / 1000));
}

void	print_time_stamp(struct timeval start_of_program)
{
	struct timeval current_time;
	unsigned int start;
	unsigned int end;

	gettimeofday(&current_time, NULL);
	start = get_milliseconds(start_of_program.tv_sec, start_of_program.tv_usec);
	end = get_milliseconds(current_time.tv_sec, current_time.tv_usec);
	ft_putchar('[');
	ft_putnbr(end - start);
	ft_putchar(']');
	ft_putchar('\t');
}

unsigned int	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (get_milliseconds(current_time.tv_sec, current_time.tv_usec));
}

void	ft_usleep(unsigned int time) // time in micro seconds
{
	unsigned int start;

	time = time / 1000; // convert to milliseconds
	start = get_current_time(); // in milliseconds
	while (start + time > get_current_time())
		usleep(10);
}
