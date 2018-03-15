/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:30:59 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/20 16:49:47 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	str = (char*)s;
	i = (ft_strlen(str));
	while (i + 1 > 0)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i--;
	}
	return (NULL);
}
