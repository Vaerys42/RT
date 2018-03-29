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
