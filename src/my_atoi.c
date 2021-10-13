/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 12:49:40 by ohachim           #+#    #+#             */
/*   Updated: 2021/10/05 14:09:40 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INT_MAX +2147483647
#define INT_MIN -2147483648

int	my_atoi(char *str)
{
	int	base;
	int	sign;

	base = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = 1 - 2 * (*str == '-');
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (base > INT_MAX / 10 || (base == INT_MAX / 10 && ((*str - '0') > 7)))
		{
			if (sign == -1)
				return (INT_MIN);
			return (INT_MAX);
		}
		base = base * 10 + (*str - '0');
		str++;
	}
	return (base * sign);
}
