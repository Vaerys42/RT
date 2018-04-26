/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 12:49:06 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/25 12:49:09 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		switch_file(t_rt *rt, int key)
{
	free_parser(rt);
	ft_putstr("Switching file...\n");
	if (key == 49)
		parser(rt, "file/1.rt");
	else if (key == 50)
		parser(rt, "file/2.rt");
	else if (key == 51)
		parser(rt, "file/3.rt");
	else if (key == 52)
		parser(rt, "file/4.rt");
	else if (key == 53)
		parser(rt, "file/5.rt");
	else if (key == 54)
		parser(rt, "file/6.rt");
	else if (key == 55)
		parser(rt, "file/7.rt");
	else if (key == 56)
		parser(rt, "file/8.rt");
	else if (key == 57)
		parser(rt, "file/9.rt");
	ft_ini_cam(rt);
	ft_reset(rt);
	make_rot(rt);
	ft_raytracing(rt);
}

void		quit_sdl(t_rt *rt)
{
	SDL_DestroyTexture(rt->data->sdl_texture);
	SDL_DestroyRenderer(rt->data->sdl_renderer);
	SDL_DestroyWindow(rt->data->sdl_window);
	SDL_Quit();
}

int			my_key_press(t_rt *rt, SDL_Keysym key)
{
	cpy_image(rt->data->image_int, rt->data->image_base);
	if (key.sym == SDLK_ESCAPE)
	{
		quit_sdl(rt);
		exit(1);
	}
	else if (key.sym == SDLK_s)
	{
		rt->op->blwh = 0;
		rt->op->sepia = !rt->op->sepia;
	}
	else if (key.sym == SDLK_b)
	{
		rt->op->blwh = !rt->op->blwh;
		rt->op->sepia = 0;
	}
	else if (key.sym == SDLK_a)
		aliasing(rt);
	else if (key.sym >= SDLK_1 && key.sym <= SDLK_9)
		switch_file(rt, key.sym);
	if (rt->op->blwh)
		bl_wh(rt);
	if (rt->op->sepia)
		sepia(rt);
	return (0);
}

int			ft_exit_cross(t_rt *rt)
{
	quit_sdl(rt);
	exit(EXIT_SUCCESS);
	return (0);
}
