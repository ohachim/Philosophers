/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:22:44 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/24 14:29:28 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

int	error(int errno)
{
	printf("Error: ");
	if (errno == BAD_ALLOC)
		printf("Bad allocation.\n");
	else if (errno == FAIL_MUTEX_INIT)
		printf("Mutex init failed.\n");
	else if (errno == BAD_PARAMS)
		printf("Wrong parameteres format.\n");
	else if (errno == BAD_DETACH)
		printf("Detach gone wrong.\n");
	else if (errno == BAD_CREATE)
		printf("Thread Create gone wrong.\n");
	else if (errno == BAD_JOIN)
		printf("Join gone wrong.\n");
	else if (errno == BAD_PHILOSOPHERS)
		printf("Philosopher intialization failed.\n");
	else if (errno == ZERO_PHILOSOPHERS)
		printf("Zero philosophers.\n");
	return (EXIT_FAILURE);
}
