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

	new1 = hex_rgb(col1);
	new2 = hex_rgb(col2);
	if (new1.r - new2.r > ANTIALIA || new1.g - new2.g > ANTIALIA
	|| new1.b - new2.b > ANTIALIA)
		return (1);
	if (new2.r - new1.r > ANTIALIA || new2.g - new1.g > ANTIALIA
	|| new2.b - new1.b > ANTIALIA)
		return (1);
	return (0);
}

t_material		new_ray_alia(t_rt *rt, double x, double y)
{
	t_material		new;

	ft_ini_ray(rt, x, y);
	ft_ray(rt, x, y, 2);
	new = *(rt->inter->mat);
	return (new);
}

void			mix_color(t_rt *rt, int x, int y)
{
	t_material		new[6];

	new[0] = new_ray_alia(rt, x + 0.30, y + 0.30);
	new[1] = new_ray_alia(rt, x + 0.70, y + 0.30);
	new[2] = new_ray_alia(rt, x + 0.5, y + 0.5);
	new[3] = new_ray_alia(rt, x + 0.30, y + 0.70);
	new[4] = new_ray_alia(rt, x + 0.70, y + 0.70);
	new[5].r = (new[4].r + new[3].r + new[2].r + new[1].r + new[0].r) / 5;
	new[5].g = (new[4].g + new[3].g + new[2].g + new[1].g + new[0].g) / 5;
	new[5].b = (new[4].b + new[3].b + new[2].b + new[1].b + new[0].b) / 5;
	put_pxl(rt->data, x, y, &new[5]);
}

void			aliasing(t_rt *rt)
{
	int			x;
	int			y;

	y = -1;
	if (rt->op->aa == 0)
		return ;
	while (++y < WIN_HEIGHT - 1)
	{
		x = -1;
		while (++x < WIN_LEN - 1)
		{
			if (diff_color(rt->data->image_int[x + (WIN_LEN * y)],
			rt->data->image_int[x + (WIN_LEN * y) + 1]) == 1)
				mix_color(rt, x, y);
			else if (diff_color(rt->data->image_int[x + (WIN_LEN * y)],
			rt->data->image_int[x + (WIN_LEN * (y + 1))]) == 1)
				mix_color(rt, x, y);
		}
	}
}
