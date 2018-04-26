/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:22:58 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/09 13:41:43 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*new;
	int				i;

	i = 0;
	if (size > 4294967295 || size == 0)
		return (0);
	if (!(new = (unsigned char*)malloc(sizeof(char) * (size + 1))))
		ft_malloc_error();
	while (new[i] != '\0')
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
