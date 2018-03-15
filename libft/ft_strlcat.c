/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:38:56 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/21 13:08:25 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		len;

	i = 0;
	while (dest[i] != '\0' && i < size)
		i++;
	len = i;
	while (i < (size - 1) && src[i - len] != '\0')
	{
		dest[i] = src[i - len];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	if (i > size)
		return (ft_strlen(src) + size);
	return (len + ft_strlen(src));
}
