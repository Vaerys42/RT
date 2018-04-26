/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:46:53 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/25 17:46:54 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void			ft_check_expose(t_material *mat, double max)
{
	if (mat->r > max)
		mat->r = max;
	if (mat->b > max)
		mat->b = max;
	if (mat->g > max)
		mat->g = max;
}

void			move_color(t_material *c, double r, double g, double b)
{
	c->r = r;
	c->g = g;
	c->b = b;
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
