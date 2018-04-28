/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:45:33 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 17:30:58 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_material		*ft_mult_color(int n, t_material *color)
{
	color->r *= n;
	color->g *= n;
	color->b *= n;
	return (color);
}

int				ft_texture_stripe(double width, t_coo hit, int x_or_y)
{
	double		axis;

	if (x_or_y == 1)
		axis = hit.x;
	else
		axis = hit.y;
	if (sin(2 * M_PI * axis / width) > 0)
		return (0);
	else
		return (1);
}

int				ft_texture_woodgrain(t_coo hit)
{
	double		r;
	double		theta;
	double		h;
	double		grain;

	hit.z += 4;
	r = sqrt(hit.x * hit.x + hit.y * hit.y + hit.z * hit.z);
	if (hit.x == 0)
		theta = M_PI / 2.0;
	else
		theta = atan(hit.z / hit.x);
	h = hit.y;
	r = r + (2 * sin(20 * theta + h / 100));
	grain = (int)(r) % 2;
	return (grain);
}

int				ft_texture_color_rainbow(double x)
{
	return ((1 - round((2 * (x - floor(x)) - 1))));
}
