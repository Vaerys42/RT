/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 17:43:49 by kboucaud          #+#    #+#             */
/*   Updated: 2016/11/21 10:59:55 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdlib.h>

static int		ft_end(const char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n') && i != 0)
		i--;
	return (i);
}

static int		ft_start(const char *str)
{
	int		begin;

	begin = 0;
	while (str[begin] == ' ' || str[begin] == '\t' || str[begin] == '\n')
		begin++;
	return (begin);
}

static char		*ft_naze(void)
{
	char	*new;

	if (!(new = (char*)malloc(sizeof(char))))
		ft_malloc_error();
	new[0] = '\0';
	return (new);
}

static int		ft_len(int begin, int i, int j)
{
	while ((begin + j) != (i + 1))
		j++;
	return (j);
}

char			*ft_strtrim(const char *s)
{
	char	*str;
	int		i;
	int		j;
	int		begin;
	char	*new;

	if (s == NULL)
		return (NULL);
	str = (char*)s;
	j = 0;
	i = ft_end(s);
	if (i == 0)
		return (ft_naze());
	begin = ft_start(s);
	j = ft_len(begin, i, j);
	if (!(new = (char*)malloc(sizeof(char) * (j + 1))))
		ft_malloc_error();
	j = 0;
	while ((begin + j) != (i + 1))
	{
		new[j] = str[begin + j];
		j++;
	}
	new[j] = '\0';
	return (new);
}
