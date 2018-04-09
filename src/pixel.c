/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 16:13:41 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/06 16:13:44 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void			cpy_image(unsigned int *tab1, unsigned int *tab2)
{
	int		i;

	i = 0;
	while (i < WIN_LEN * WIN_HEIGHT)
	{
		tab1[i] = tab2[i];
		i++;
	}
}

void			put_pxl(t_data *data, int x, int y, t_material *color)
{
	if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	data->image_int[x + (WIN_LEN * y)] = col_hexa(color->r, color->g, color->b);
}

void			put_pxl_base(t_data *data, int x, int y, t_material *color)
{
	if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	data->image_base[x + (WIN_LEN * y)] =
	col_hexa(color->r, color->g, color->b);
}

unsigned int	col_hexa(int r, int g, int b)
{
	return ((((r << 8) + g) << 8) + b);
}

t_material		hex_rgb(int col)
{
	t_material		new;

	new.r = ((col >> 16) & 0xFF);
	new.g = ((col >> 8) & 0xFF);
	new.b = ((col) & 0xFF);
	return (new);
}
