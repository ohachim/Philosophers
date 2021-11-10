/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:22:44 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 17:21:02 by ohachim          ###   ########.fr       */
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
	else if (errno == BAD_PARAMETERS)
		printf("Wrong parameteres format.\n");
	else if (errno == BAD_DETACH)
		printf("Detach gone wrong");
	else if (errno == BAD_CREATE)
		printf("Thread Create gone wrong");
	else if (errno == BAD_JOIN)
		printf("Join gone wrong");
	return (EXIT_FAILURE);
}
