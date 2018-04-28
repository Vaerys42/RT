/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_upload.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:45:33 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 16:53:48 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int					ft_save_img(t_rt *rt)
{
	SDL_Surface		*surface;
	Uint32			f;
	SDL_Renderer	*renderer;
	int				pitch;

	f = SDL_PIXELFORMAT_ARGB8888;
	renderer = rt->data->sdl_renderer;
	if (renderer)
	{
		surface = SDL_CreateRGBSurfaceWithFormat(0, WIN_LEN, WIN_HEIGHT, 32, f);
		pitch = surface->pitch;
		SDL_RenderReadPixels(renderer, NULL, f, surface->pixels, pitch);
		SDL_SaveBMP(surface, "screenshot.bmp");
		SDL_FreeSurface(surface);
	}
	return (0);
}
