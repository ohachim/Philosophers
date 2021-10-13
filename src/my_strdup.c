/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:10:22 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/05 17:21:32 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

char	*my_strdup(char *str)
{
	int 	len;
	int		i;
	char	*dup;

	i = 0;
	len = my_strlen(str);
	dup = (char*)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return NULL;
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
