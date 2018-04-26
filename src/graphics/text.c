/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:51:43 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/18 18:51:44 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

Uint8		ft_uint8_to_32(Uint32 pixel, Uint32 mask, Uint32 shift, Uint32 loss)
{
	Uint32		tmp;
	Uint8		color;

	tmp = pixel & mask;
	tmp = tmp >> shift;
	tmp = tmp << loss;
	color = (Uint8)tmp;
	return (color);
}

Uint32		ft_getpixel(SDL_Surface *surface, double i, double j)
{
	Uint32	pixel_32;
	Uint8	*pixel;
	Uint32	x;
	Uint32	y;

	SDL_LockSurface(surface);
	x = (Uint32)i;
	y = (Uint32)j;
	pixel = (Uint8*)surface->pixels;
	pixel += (y * surface->pitch) + (x * sizeof(Uint32));
	pixel_32 = *((Uint32*)pixel);
	SDL_UnlockSurface(surface);
	return (pixel_32);
}

t_material	ft_getpixelcolor(SDL_Surface *surface, double i, double j)
{
	t_material				color;
	SDL_PixelFormat			*format;
	Uint32					pixel;

	format = surface->format;
	pixel = ft_getpixel(surface, i, j);
	color.r = (double)ft_uint8_to_32(pixel, format->Rmask,
	format->Rshift, format->Rloss);
	color.g = (double)ft_uint8_to_32(pixel, format->Gmask,
	format->Gshift, format->Gloss);
	color.b = (double)ft_uint8_to_32(pixel, format->Bmask,
	format->Bshift, format->Bloss);
	return (color);
}

void		ttf_exit(void)
{
	printf("%s\n", TTF_GetError());
	exit(-1);
}

void		rt_infos(t_rt *rt)
{
	SDL_Surface	*info_box;
	TTF_Font	*font;
	t_material	tmp;
	int			x;
	int			y;

	if (TTF_Init() == -1)
		ttf_exit();
	if ((font = TTF_OpenFont("file/police.ttf", 12)) == NULL)
		ttf_exit();
	info_box = TTF_RenderText_Shaded(font, "Raytracer RT", (SDL_Color){255, 255, 255, 255}, (SDL_Color){255, 0, 0, 255});
	y = -1;
	while (++y < info_box->h)
	{
		x = -1;
		while (++x < info_box->w)
		{
			tmp = ft_getpixelcolor(info_box, x, y);
			put_pxl(rt->data, x, y, &tmp);
			put_pxl_base(rt->data, x, y, &tmp);
		}
	}
	SDL_FreeSurface(info_box);
	TTF_CloseFont(font);
	TTF_Quit();
}
