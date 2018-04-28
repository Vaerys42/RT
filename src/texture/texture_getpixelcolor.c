/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_getpixelcolor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:45:33 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 16:42:10 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

Uint8				int_8to32(Uint32 p, Uint32 m, Uint32 s, Uint32 l)
{
	Uint32			tmp;
	Uint8			color;

	tmp = p & m;
	tmp = tmp >> s;
	tmp = tmp << l;
	color = (Uint8)tmp;
	return (color);
}

Uint32				ft_getpixel(SDL_Surface *surface, double i, double j)
{
	Uint32			pixel_32;
	Uint32			x;
	Uint32			y;
	Uint8			*pixel;

	SDL_LockSurface(surface);
	x = (Uint32)i;
	y = (Uint32)j;
	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	pixel_32 = *((Uint32*)pixel);
	SDL_UnlockSurface(surface);
	return (pixel_32);
}

t_coo				ft_new_coo(double u, double v, t_texture *t, SDL_Surface *s)
{
	t_coo			point;
	double			scale_x;
	double			scale_y;
	double			offset_x;
	double			offset_y;

	point = ft_texel(u, v, s);
	scale_x = t->scale.x;
	scale_y = t->scale.y;
	point = ft_scale_texture(s, point, scale_x, scale_y);
	offset_x = t->offset.x * s->w;
	offset_y = t->offset.y * s->h;
	point = ft_shift_texture(s, point, offset_x, offset_y);
	return (point);
}

t_material			ft_getpixelcolor(SDL_Surface *surface, double i, double j)
{
	t_material		color;
	SDL_PixelFormat	*f;
	Uint32			pixel;

	f = surface->format;
	pixel = ft_getpixel(surface, i, j);
	color.r = (double)int_8to32(pixel, f->Rmask, f->Rshift, f->Rloss);
	color.g = (double)int_8to32(pixel, f->Gmask, f->Gshift, f->Gloss);
	color.b = (double)int_8to32(pixel, f->Bmask, f->Bshift, f->Bloss);
	return (color);
}
