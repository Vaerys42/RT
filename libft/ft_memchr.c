/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:16:52 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/09 17:31:43 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*new;

	i = 0;
	new = (unsigned char*)s;
	while (i < n)
	{
		if (new[i] == (unsigned char)c)
			return (&new[i]);
		i++;
	}
	return (NULL);
}
