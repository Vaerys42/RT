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

#include "../rt.h"

void		rt_infos(t_rt *rt)
{
	SDL_Color	text_color;
	SDL_Surface	*info_box;

	text_color = (SDL_Color){0, 0, 0, 0};
	info_box = TTF_RenderText_Blended(rt->data->font, "Raytracer", text_color);
	//if (!(info_box = SDL_CreateRGBSurface(0, 50, 50, 4, 0, 0, 0, 0)))
		//ft_exit(); 
}
