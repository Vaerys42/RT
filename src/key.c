/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 12:49:06 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/25 12:49:09 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

int			my_key_press(int key, t_rt *rt)
{
	if (key == 53)
	{
		mlx_destroy_window(rt->data->mlx, rt->data->mlx_window);
		exit(1);
	}
	return (0);
}

int			ft_exit_cross(t_rt *rt)
{
	mlx_destroy_image(rt->data->mlx, rt->data->mlx_image);
	exit(EXIT_SUCCESS);
	return (0);
}
