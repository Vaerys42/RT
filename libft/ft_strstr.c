/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:34:45 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/13 15:39:44 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int		ft_cmp(int i, const char *find_in, const char *to_find)
{
	int		j;
	int		k;

	j = 0;
	k = i;
	while (find_in[k] == to_find[j] && to_find[j] != '\0')
	{
		k++;
		j++;
	}
	if (to_find[j] == '\0')
		return (1);
	else
		return (0);
}

char			*ft_strstr(const char *find_in, const char *to_find)
{
	int		len;
	int		i;
	char	*fi;

	len = 0;
	i = 0;
	fi = (char*)find_in;
	if (to_find[0] == '\0')
		return (fi);
	while (find_in[i] != '\0')
	{
		if (find_in[i] == to_find[0])
		{
			if (ft_cmp(i, find_in, to_find) == 1)
				return (&fi[i]);
		}
		i++;
	}
	return (NULL);
}
