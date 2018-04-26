/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 12:07:45 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/21 17:08:24 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

static int		ft_nbrlen(int i)
{
	int		len;

	len = 0;
	if (i < 0)
	{
		i = -i;
		len++;
	}
	while (i > 9)
	{
		i = i / 10;
		len++;
	}
	len++;
	return (len);
}

static char		*ft_min(void)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * 12)))
		ft_malloc_error();
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

static char		*ft_transfert(int i, char *new, int j, int len)
{
	int		neg;

	neg = 0;
	if (i < 0)
	{
		neg = 1;
		i = -i;
		len--;
	}
	while (len > 0)
	{
		new[j] = (i % 10) + 48;
		i = i / 10;
		j++;
		len--;
	}
	new[j] = (i % 10) + 48;
	if (neg == 0)
		new[j + 1] = '\0';
	else
	{
		new[j + 1] = '-';
		new[j + 2] = '\0';
	}
	return (ft_strrev(new));
}

char			*ft_itoa(int i)
{
	char	*new;
	int		j;
	int		len;

	j = 0;
	len = ft_nbrlen(i) - 1;
	if (i == -2147483648)
		return (ft_min());
	if (!(new = (char*)malloc(sizeof(char) * (ft_nbrlen(i) + 1))))
		ft_malloc_error();
	new = ft_transfert(i, new, j, len);
	return (new);
}
