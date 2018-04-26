/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:47:18 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/20 15:18:33 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		x;
	unsigned char		*new;
	unsigned char		*ori;

	i = 0;
	new = (unsigned char*)dest;
	ori = (unsigned char*)src;
	x = (unsigned char)c;
	while (i < n)
	{
		new[i] = ori[i];
		if (ori[i] == x)
			return (&new[i + 1]);
		i++;
	}
	return (NULL);
}
