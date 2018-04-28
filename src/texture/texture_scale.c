/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_scale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 16:56:18 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 16:57:28 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_coo		ft_local_coo(t_coo hit, t_coo origin, t_coo rot)
{
	hit = ft_sub_vect(hit, origin);
	hit = ft_inv_rot(hit, rot);
	return (hit);
}

t_coo		ft_texel(double u, double v, SDL_Surface *surface)
{
	t_coo	texel_2d;

	texel_2d.x = u * surface->w - 0.5;
	texel_2d.y = v * surface->h - 0.5;
	return (texel_2d);
}

t_coo		ft_uv(t_coo point_2d, int obj, SDL_Surface *surface)
{
	t_coo	new;

	new.x = point_2d.x;
	if (obj == SPH || obj == PLN)
		new.y = point_2d.y;
	if (obj == CYL || obj == CON)
		new.y = surface->h - point_2d.y;
	return (new);
}

t_coo		ft_shift_texture(SDL_Surface *s, t_coo p, double a, double b)
{
	t_coo	point;
	double	offset_x;
	double	offset_y;
	double	i;
	double	j;

	offset_x = a;
	offset_y = b;
	i = p.x;
	j = p.y;
	point.x = 0;
	point.y = s->h * 0.5;
	if (i < s->w && j < s->h)
	{
		if (i > s->w - offset_x)
			i = i - s->w;
		if (j > s->h - offset_y)
			j = j - s->h;
		point.x = i + offset_x;
		point.y = j + offset_y;
	}
	return (point);
}

t_coo		ft_scale_texture(SDL_Surface *s, t_coo p, double a, double b)
{
	t_coo	point;
	double	i;
	double	j;

	i = p.x;
	j = p.y;
	while (i * a > s->w)
		i = i - s->w / a;
	while (j * b > s->h)
		j = j - s->h / b;
	point.x = i * a;
	point.y = j * b;
	if (point.x < 0 || point.y < 0)
	{
		point.x = 0;
		point.y = s->h * 0.5;
	}
	if (point.x >= s->w || point.y >= s->h)
	{
		point.x = 0;
		point.y = 0;
	}
	return (point);
}
