/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_starts_with.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:50:47 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/21 13:50:48 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int				ft_starts_with(char *str, char *str2)
{
	int			i;

	i = 0;
	while (str2[i] != 0 && str[i] != 0)
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}
