/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:38:05 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/09 14:34:09 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;

	i = -1;
	if (!(new = (char*)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		ft_malloc_error();
	while (src[++i] != '\0')
		new[i] = src[i];
	new[i] = '\0';
	return (new);
}
