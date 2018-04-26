/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 17:13:16 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/20 17:40:59 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "includes/libft.h"

char	*ft_strnstr(const char *meule_de_foin, const char *aiguille, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	char				*find_in;
	char				*to_find;

	i = 0;
	find_in = (char*)meule_de_foin;
	to_find = (char*)aiguille;
	if (ft_strlen(aiguille) > ft_strlen(meule_de_foin))
		return (NULL);
	if (to_find[0] == '\0')
		return (find_in);
	while (i <= len)
	{
		if (find_in[i] == to_find[0])
		{
			j = 0;
			while (find_in[i + j] == to_find[j] && to_find[j] != '\0')
				j++;
			if (to_find[j] == '\0' && (i + j) <= len)
				return (&find_in[i]);
		}
		i++;
	}
	return (NULL);
}
