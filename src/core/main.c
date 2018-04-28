/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:33 by kboucaud          #+#    #+#             */
/*   Updated: 2017/10/21 01:09:43 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_create(t_rt *rt)
{
	if (!(rt->data = (t_data*)malloc(sizeof(t_data))))
		ft_malloc_error();
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0)
		ft_exit();
	if (!(rt->data->sdl_window = SDL_CreateWindow("RT - SDL",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_LEN, WIN_HEIGHT, 0)))
		ft_exit();
	if (!(rt->data->sdl_renderer = SDL_CreateRenderer(rt->data->sdl_window,
	-1, 0)))
		ft_exit();
	if (!(rt->data->sdl_texture = SDL_CreateTexture(rt->data->sdl_renderer,
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
	WIN_LEN, WIN_HEIGHT)))
		ft_exit();
	if (!(rt->data->image_int = (unsigned int*)malloc(WIN_HEIGHT
	* WIN_LEN * sizeof(unsigned int))))
		ft_exit();
	if (!(rt->data->image_base = (unsigned int*)malloc(WIN_HEIGHT
	* WIN_LEN * sizeof(unsigned int))))
		ft_exit();
	if (IMG_Init(IMG_INIT_PNG) == -1)
		ft_exit();
}

void		window(t_rt *rt)
{
	SDL_UpdateTexture(rt->data->sdl_texture, NULL, rt->data->image_int,
	WIN_LEN * sizeof(unsigned int));
	SDL_RenderCopy(rt->data->sdl_renderer, rt->data->sdl_texture, NULL, NULL);
	SDL_RenderPresent(rt->data->sdl_renderer);
}

void		treat_event(t_rt *rt, SDL_Event ev)
{
	if (ev.type == SDL_WINDOWEVENT && ev.window.event == SDL_WINDOWEVENT_CLOSE)
		ft_exit_cross(rt);
	else if (ev.type == SDL_KEYDOWN && ev.key.repeat == 0)
		my_key_press(rt, ev.key.keysym);
	else if (ev.type == DOWN && ev.button.button == SDL_BUTTON_LEFT)
		get_obj(rt, ev.button.x, ev.button.y);
	else if (ev.type == DOWN && ev.button.button == SDL_BUTTON_RIGHT)
		rt->op->cam_move = 1;
	else if (ev.type == UP && ev.button.button == SDL_BUTTON_LEFT)
		rt->op->maintain = 0;
	else if (ev.type == UP && ev.button.button == SDL_BUTTON_RIGHT)
		rt->op->cam_move = 0;
	else if ((ev.type == SDL_MOUSEWHEEL || ev.type == MOTION)
	&& rt->op->maintain == 1)
		move_object(rt, ev);
	else if (ev.type == MOTION && rt->op->cam_move == 1)
		move_camera(rt, ev);
	window(rt);
}

void		get_event(t_rt *rt)
{
	SDL_Event		ev;

	while (1)
	{
		if (SDL_WaitEvent(&ev) == 1)
			treat_event(rt, ev);
	}
}

int			main(int argc, char **argv)
{
	t_rt		*rt;

	if (argc != 2)
		ft_bad_arg(0);
	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		ft_malloc_error();
	parser(rt, argv[1]);
	ft_ini(rt);
	ft_raytracing(rt);
	rt_infos(rt);
	get_event(rt);
	return (0);
}
