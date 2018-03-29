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

#include "../rt.h"

int			my_key_press(t_rt *rt, SDL_Keysym key)
{
	if (key.sym == SDLK_ESCAPE)
	{
		SDL_DestroyTexture(rt->data->sdl_texture);
		SDL_DestroyRenderer(rt->data->sdl_renderer);
		SDL_DestroyWindow(rt->data->sdl_window);
		SDL_Quit();
		exit(1);
	}
	return (0);
}

int			ft_exit_cross(t_rt *rt)
{
	SDL_DestroyTexture(rt->data->sdl_texture);
	SDL_DestroyRenderer(rt->data->sdl_renderer);
	SDL_DestroyWindow(rt->data->sdl_window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
	return (0);
}
