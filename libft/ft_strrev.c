/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 13:30:13 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/27 13:30:14 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

char	*ft_strrev(char *str)
{
	char	*new;
	int		i;
	int		j;

	i = ft_strlen(str);
	j = 0;
	if (!(new = (char*)malloc(sizeof(char) * (i + 1))))
		ft_malloc_error();
	while (j < (int)ft_strlen(str))
	{
		new[j] = str[i - 1];
		i--;
		j++;
	}
	new[j] = '\0';
	return (new);
}
