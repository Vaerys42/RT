/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 19:15:40 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/04 19:15:41 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void			sepia(t_rt *rt)
{
	int			x;
	int			y;
	t_material	old;
	t_material	new;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_LEN)
		{
			old = hex_rgb(rt->data->image_int[x + (WIN_LEN * y)]);
			new.r = old.r * 0.393 + old.g * 0.619 + old.b * 0.189;
			new.g = old.r * 0.349 + old.g * 0.536 + old.b * 0.168;
			new.b = old.r * 0.272 + old.g * 0.384 + old.b * 0.131;
			ft_check_expose(&new, 255);
			put_pxl(rt->data, x, y, &new);
		}
	}
}

void			bl_wh(t_rt *rt)
{
	int			x;
	int			y;
	t_material	old;
	t_material	new;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_LEN)
		{
			old = hex_rgb(rt->data->image_base[x + (WIN_LEN * y)]);
			new.r = old.r * 0.114 + old.g * 0.587 + old.b * 0.2989;
			new.g = old.r * 0.114 + old.g * 0.587 + old.b * 0.2989;
			new.b = old.r * 0.114 + old.g * 0.587 + old.b * 0.2989;
			put_pxl(rt->data, x, y, &new);
		}
	}
}
