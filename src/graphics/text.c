/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:51:43 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/30 21:38:18 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		set_info_window(t_rt *rt, int x, int y)
{
	if (!(rt->data->info_window = SDL_CreateWindow("Info RT",
	300, 300, x, y, 0)))
		ft_exit();
	if (!(rt->data->info_surface = SDL_GetWindowSurface(rt->data->info_window)))
		ft_exit();
}

void		apply_surface(SDL_Surface *src, SDL_Surface *dest, int x, int y)
{
	SDL_Rect	area;

	area.x = x;
	area.y = y;
	area.w = src->w;
	area.h = src->h;
	SDL_BlitSurface(src, NULL, dest, &area);
}

void		print_line(t_rt *rt, char *str, int x, int y)
{
	SDL_Surface	*info_box;

	info_box = TTF_RenderText_Blended(rt->data->font, str,
	(SDL_Color){0, 0, 0, 255});
	apply_surface(info_box, rt->data->info_surface, x, y);
	SDL_FreeSurface(info_box);
}

void		rt_infos(t_rt *rt)
{
	SDL_Surface		*background;

	if (TTF_Init() == -1)
		ttf_exit();
	if ((rt->data->font = TTF_OpenFont("file/police.ttf", 15)) == NULL)
		ttf_exit();
	background = IMG_Load("file/background.png");
	if (!background)
		exit(-1);
	set_info_window(rt, 400, 400);
	apply_surface(background, rt->data->info_surface, 0, 0);
	print_line(rt, "Raytracer", 160, 10);
	print_line(rt, "Control List :", 5, 50);
	print_line(rt, "Moving object : Left Click and move the mouse", 5, 80);
	print_line(rt, "Rotate camera : Right Click and move the mouse", 5, 100);
	print_line(rt, "Reflexion depth : PageUp - PageDown", 5, 120);
	print_line(rt, "Sepia Filter : S", 5, 140);
	print_line(rt, "Black and White Filter : B", 5, 160);
	print_line(rt, "Switch between files : 1 - 9", 5, 180);
	print_line(rt, "Screenshot / Video : P / V", 5, 200);
	SDL_UpdateWindowSurface(rt->data->info_window);
	TTF_CloseFont(rt->data->font);
	TTF_Quit();
	SDL_FreeSurface(background);
}
