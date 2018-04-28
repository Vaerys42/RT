/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:28:29 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 17:38:32 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int					ft_texture_texture(t_rt *rt, t_coo hit, t_texture *t)
{
	t_coo			point_2d;
	double			u;
	double			v;
	t_material		color;

	if (t->surface == NULL)
		return (-1);
	if (rt->inter->obj == SPH)
		point_2d = ft_mapping_sphere(hit);
	else if (rt->inter->obj == CYL)
		point_2d = ft_mapping_cylinder(hit);
	else if (rt->inter->obj == CON)
		point_2d = ft_mapping_cone(hit);
	else if (rt->inter->obj == PLN)
		point_2d = ft_mapping_plane(hit, rt->plane->o, rt->plane->norm);
	else
		return (-1);
	point_2d = ft_uv(point_2d, rt->inter->obj, t->surface);
	u = ft_new_coo(point_2d.x, point_2d.y, t, t->surface).x;
	v = ft_new_coo(point_2d.x, point_2d.y, t, t->surface).y;
	color = ft_getpixelcolor(t->surface, u, v);
	rt->inter->col->r = color.r / 255;
	rt->inter->col->g = color.g / 255;
	rt->inter->col->b = color.b / 255;
	return (0);
}

int					ft_texture_color(t_rt *rt, t_coo hit, int flag)
{
	double			n;

	if (flag == 2 && ft_texture_checker(0.5, hit) == 1)
		rt->inter->col = ft_mult_color(2, rt->inter->col);
	if (flag == 3 && ft_texture_stripe(0.125, hit, 0) == 1)
		rt->inter->col = ft_mult_color(2, rt->inter->col);
	if (flag == 4)
	{
		rt->inter->col->r += ft_texture_color_rainbow(hit.x * hit.y);
		rt->inter->col->g += ft_texture_color_rainbow(hit.y * hit.z);
		rt->inter->col->b += ft_texture_color_rainbow(hit.z * hit.x);
	}
	if (flag == 5 && ft_texture_woodgrain(hit) == 1)
		rt->inter->col = ft_mult_color(2, rt->inter->col);
	if (flag == 6)
	{
		n = ft_texture_waves(hit);
		rt->inter->col->r *= fabs(n);
		rt->inter->col->g *= fabs(n);
		rt->inter->col->b *= fabs(n);
	}
	return (0);
}

int					ft_texture_color_new(t_rt *rt, t_coo hit, int flag)
{
	if (flag == 10 && ft_texture_square(hit, rt) == 1)
	{
		rt->inter->col->r = 0;
		rt->inter->col->g = 0;
		rt->inter->col->b = 0;
	}
	if (flag == 11 && ft_texture_sparkle() == 1)
	{
		rt->inter->col->r = 1;
		rt->inter->col->g = 1;
		rt->inter->col->b = 1;
	}
	return (0);
}

int					ft_color_perlin(t_rt *rt, t_coo hit, int flag)
{
	double			n;

	if (flag == 7)
		n = ft_texture_perlin(hit);
	if (flag == 8)
		n = ft_texture_marble(hit);
	if (flag == 9)
		n = ft_texture_wood(hit);
	rt->inter->col->r *= fabs(n);
	rt->inter->col->g *= fabs(n);
	rt->inter->col->b *= fabs(n);
	return (0);
}

int					ft_texture_all(t_rt *rt, t_coo hit, t_texture *t)
{
	int				flag;

	flag = t->type;
	if (flag == 1)
		return (ft_texture_texture(rt, hit, t));
	if (flag >= 2 && flag <= 6)
		return (ft_texture_color(rt, hit, flag));
	if (flag >= 7 && flag <= 9)
		return (ft_color_perlin(rt, hit, flag));
	if (flag >= 10 && flag <= 11)
		return (ft_texture_color_new(rt, hit, flag));
	return (0);
}
