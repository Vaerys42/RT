/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliasing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 22:26:16 by kboucaud          #+#    #+#             */
/*   Updated: 2018/03/23 22:26:19 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int				diff_color(int col1, int col2)
{
	t_material		new1;
	t_material		new2;

	new1.r = ((col1 >> 16) & 0xFF) / 255.0;
	new1.g = ((col1 >> 8) & 0xFF) / 255.0;
	new1.b = ((col1) & 0xFF) / 255.0;
	new2.r = ((col2 >> 16) & 0xFF) / 255.0;
	new2.g = ((col2 >> 8) & 0xFF) / 255.0;
	new2.b = ((col2) & 0xFF) / 255.0;
	if (new1.r - new2.r > 100 || new1.g - new2.g > 100 || new1.b - new2.b > 100)
		return (1);
	if (new2.r - new1.r > 100 || new2.g - new1.g > 100 || new2.b - new1.b > 100)
		return (1);
	return (0);
}

unsigned int	col_hexa(int r, int g, int b)
{
	return ((((r << 8) + g) << 8) + b);
}

void		put_pxl(t_data *data, int x, int y, t_material *color)
{
	if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	data->image_int[x + (WIN_LEN * y)] = col_hexa(color->r, color->g, color->b);
}

void		new_ray(t_rt *rt, double x, double y)
{
	int		scale;

	scale = (1 / ANTIALIA) * 2;
}

void		aliasing(t_rt *rt)
{
	int			x;
	int			y;

	y = -1;
	rt->rand = 0;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_LEN)
		{
			if (y != 0 && x != WIN_LEN - 1)
			{
				if (diff_color(rt->data->image_int[x + (WIN_LEN * y)], rt->data->image_int[x + (WIN_LEN * y)] == 1))
					new_ray(rt, x, y);
			}
		}
	}
}
