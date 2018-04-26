/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:50:39 by kboucaud          #+#    #+#             */
/*   Updated: 2017/03/02 14:50:44 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_strnjoin(char *s1, char *s2, int size)
{
	char	*new;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	if (!(new = (char*)malloc(sizeof(char) * (i + size + 1))))
		ft_malloc_error();
	j = -1;
	while (s1[++j] != 0)
		new[j] = s1[j];
	i = -1;
	while (++i < size)
		new[j + i] = s2[i];
	new[j + i] = 0;
	free(s1);
	return (new);
}
