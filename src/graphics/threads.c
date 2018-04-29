/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knzeng-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 20:23:27 by knzeng-e          #+#    #+#             */
/*   Updated: 2018/04/29 21:47:42 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		*thread_render_1(void *rt)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_LEN / 2)
	{
		j = 0;
		while (j < WIN_HEIGHT / 2)
		{
			ft_ini_ray(rt, i, j);
			ft_ray(rt, i, j, 1);
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
	return (0);
}

void		*thread_render_2(void *rt)
{
	int		i;
	int		j;

	i = WIN_LEN / 2;
	while (i < WIN_LEN)
	{
		j = 0;
		while (j < WIN_HEIGHT / 2)
		{
			ft_ini_ray(rt, i, j);
			ft_ray(rt, i, j, 1);
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
	return (0);
}

void		*thread_render_3(void *rt)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_LEN / 2)
	{
		j = WIN_HEIGHT / 2;
		while (j < WIN_HEIGHT)
		{
			ft_ini_ray(rt, i, j);
			ft_ray(rt, i, j, 1);
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
	return (0);
}

void		*thread_render_4(void *rt)
{
	int		i;
	int		j;

	i = WIN_LEN / 2;
	while (i < WIN_LEN)
	{
		j = WIN_HEIGHT / 2;
		while (j < WIN_HEIGHT)
		{
			ft_ini_ray(rt, i, j);
			ft_ray(rt, i, j, 1);
			j++;
		}
		i++;
	}
	pthread_exit(NULL);
	return (0);
}
