/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachim <ohachim@1337.student.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:03:57 by ohachim           #+#    #+#             */
/*   Updated: 2021/11/10 10:58:00 by ohachim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hphilosophers.h"

void	ft_putnbr(long long num)
{
	int	ch;
	int	len;
	int	dup;

	len = 1;
	dup = num;
	if (num < 0)
	{
		ft_putchar('-');
		num *= -1;
	}
	while (dup)
	{
		dup = dup / 10;
		len *= 10;
	}
	if (!(len / 10))
		ft_putchar('0');
	while (len / 10)
	{
		ch = num / (len / 10);
		ft_putchar((ch % 10) + '0');
		len /= 10;
	}
}
