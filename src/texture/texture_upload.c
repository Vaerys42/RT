/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_upload.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:45:33 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 17:11:50 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void			ft_ini_texture(t_texture *texture)
{
	texture->type = 0;
	texture->scale.x = 1;
	texture->scale.y = 1;
	texture->offset.x = 0;
	texture->offset.y = 0;
	texture->path = NULL;
	texture->surface = NULL;
}

int				ft_check_img_path(char *img_path)
{
	if (img_path == NULL)
	{
		ft_putendl("Error : no img_path. Couldn't upload the texture.");
		return (-1);
	}
	return (0);
}

int				ft_check_upload(SDL_Surface *surface, char *img_path)
{
	if (!(surface))
	{
		ft_putstr("Error : SDL couldn't upload texture from path : ");
		ft_putendl(img_path);
		ft_putstr("Objects with this texture ");
		ft_putstr("are rendered with their default color.\n");
		return (-1);
	}
	return (0);
}

SDL_Surface		*ft_upload_texture(char *path)
{
	SDL_Surface	*surface;

	surface = NULL;
	if (ft_check_img_path(path) == 0)
	{
		surface = IMG_Load(path);
		if (ft_check_upload(surface, path) == -1)
			surface = NULL;
		else
		{
			ft_putstr("Texture succesfully uploaded from path : ");
			ft_putendl(path);
		}
	}
	return (surface);
}
