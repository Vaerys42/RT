/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:53:17 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/07 17:58:28 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*new;
	unsigned char	*start;

	i = 0;
	start = (unsigned char*)src;
	new = dest;
	while (i < n)
	{
		new[i] = start[i];
		i++;
	}
	return (new);
}
