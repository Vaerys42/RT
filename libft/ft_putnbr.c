/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:21:53 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/09 11:34:07 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void			ft_putnbr(int c)
{
	if (c > 2147483647 || c < -2147483648)
		return ;
	if (c == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (c < 0)
	{
		ft_putchar('-');
		c = -c;
	}
	if (c > 9)
	{
		ft_putnbr(c / 10);
		ft_putnbr(c % 10);
	}
	if (c < 10)
		ft_putchar(c + 48);
}
