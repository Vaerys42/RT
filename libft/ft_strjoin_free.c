/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 14:54:22 by kboucaud          #+#    #+#             */
/*   Updated: 2017/05/10 14:54:24 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char		*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*new;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	if (!(new = (char*)malloc(sizeof(char) * (i + ft_strlen(s2) + 1))))
		ft_malloc_error();
	j = 0;
	while (s1[j] != '\0')
	{
		new[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
		new[j++] = s2[i++];
	new[j] = '\0';
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode >= 2)
		free(s2);
	return (new);
}
