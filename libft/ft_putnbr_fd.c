/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 14:34:07 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/09 11:34:14 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	ft_putfile(char c, int fd)
{
	write(fd, &c, 1);
}

void		ft_putnbr_fd(int c, int fd)
{
	if (c > 2147483647 || c < -2147483648)
		return ;
	if (c == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (c < 0)
	{
		ft_putfile('-', fd);
		c = -c;
	}
	if (c > 9)
	{
		ft_putnbr_fd(c / 10, fd);
		ft_putnbr_fd(c % 10, fd);
	}
	if (c < 10)
		ft_putfile(c + 48, fd);
}
