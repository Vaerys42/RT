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

t_material		hex_rgb(int col)
{
	t_material		new;

	new.r = ((col >> 16) & 0xFF);
	new.g = ((col >> 8) & 0xFF);
	new.b = ((col) & 0xFF);
	return (new);
}

int				diff_color(int col1, int col2)
{
	t_material		new1;
	t_material		new2;

	new1 = hex_rgb(col1);
	new2 = hex_rgb(col2);
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

t_material	new_ray_alia(t_rt *rt, double x, double y)
{
	t_material		new;

	ft_ini_ray(rt, x, y);
	ft_ray(rt, x, y, 2);
	new = *(rt->inter->mat);
	return (new);
}

void		mix_color(t_rt *rt, double x, double y)
{
	t_material		new[6];

	new[0] = new_ray_alia(rt, x + 0.30, y + 0.30);
	new[1] = new_ray_alia(rt, x + 0.70, y + 0.30);
	new[2] = new_ray_alia(rt, x + 0.5, y + 0.5);
	new[3] = new_ray_alia(rt, x + 0.30, y + 0.70);
	new[4] = new_ray_alia(rt, x + 0.70, y + 0.70);
	new[5].r = (new[4].r + new[3].r + new[2].r + new[1].r + new[0].r) / 5;
	new[5].g = (new[4].g + new[3].g + new[2].g + new[1].g + new[0].g) / 5;
	new[5].g = (new[4].b + new[3].b + new[2].b + new[1].b + new[0].b) / 5;
	new[5].r = 255;
	new[5].g = 255;
	new[5].b = 255;
	put_pxl(rt->data, x, y, &new[5]);
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
				if (diff_color(rt->data->image_int[x + (WIN_LEN * y)], rt->data->image_int[x + (WIN_LEN * y) + 1]) == 1)
					mix_color(rt, x, y);
			}
		}
	}
}
