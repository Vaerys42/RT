/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 14:46:20 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/02 21:07:09 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_line(char *str)
{
	int		i;

	i = 0;
	while (str[i] != 0 && str[i] != '\n')
		i++;
	return (i);
}

char	*ft_short(char *str, int len)
{
	char	*new;
	int		i;

	new = ft_strnew(BUFF_SIZE + 1);
	i = 0;
	while (len + i < BUFF_SIZE)
	{
		new[i] = str[len + i];
		i++;
	}
	free(str);
	return (new);
}

int		ft_next(char **tmp, char **line, int fd)
{
	while (ft_line(tmp[0]) == (int)ft_strlen(tmp[0]) && ft_strlen(tmp[0]) != 0)
	{
		*line = ft_strjoin_free(*line, tmp[0], 1);
		ft_bzero(tmp[0], BUFF_SIZE + 1);
		if (read(fd, tmp[0], BUFF_SIZE) == -1)
			return (-1);
	}
	if (ft_strlen(tmp[0]) != 0)
	{
		*line = ft_strnjoin(*line, tmp[0], ft_line(tmp[0]));
		tmp[0] = ft_short(tmp[0], ft_line(tmp[0]) + 1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char		*tmp = NULL;

	if (tmp == NULL)
	{
		tmp = ft_strnew(BUFF_SIZE + 1);
		if (tmp == NULL || (read(fd, tmp, BUFF_SIZE) == -1) || line == NULL)
		{
			if (tmp != NULL)
				free(tmp);
			return (-1);
		}
	}
	if (ft_strlen(tmp) == 0 && read(fd, tmp, BUFF_SIZE) == 0)
	{
		(void)tmp;
		return (0);
	}
	*line = ft_strnew(BUFF_SIZE + 1);
	if (ft_next(&tmp, line, fd) == -1)
		return (-1);
	return (1);
}
