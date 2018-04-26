/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 18:35:34 by kboucaud          #+#    #+#             */
/*   Updated: 2017/02/05 18:35:34 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/libft.h"

char	*ft_strndup(char *str, int size, int start)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = (char*)malloc(sizeof(char) * (size + 1))))
		ft_malloc_error();
	while (i < size)
	{
		new[i] = str[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
