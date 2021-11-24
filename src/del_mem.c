/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:38:58 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/24 11:39:29 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	del_mem(void **mem_adress)
{
	if (*mem_adress)
	{
		free(*mem_adress);
		*mem_adress = NULL;
	}
}