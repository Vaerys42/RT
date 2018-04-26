/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:34:52 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/13 11:00:00 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char				*part;
	unsigned int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(part = (char*)malloc(sizeof(char) * (len + 1))))
		ft_malloc_error();
	while (i < len)
	{
		part[i] = s[start + i];
		i++;
	}
	part[i] = '\0';
	return (part);
}
