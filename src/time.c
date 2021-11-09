/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 20:42:31 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/08 21:18:33 by ohachim          ###   ########.fr       */
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

void	print_time_stamp( struct timeval start_of_program)
{
	struct timeval current_time;
	unsigned int start;
	unsigned int end;

	gettimeofday(&current_time, NULL);
	start = get_milliseconds(start_of_program.tv_sec, start_of_program.tv_usec);
	end = get_milliseconds(current_time.tv_sec, current_time.tv_usec);
	printf("[%u]\t", end - start);
}
