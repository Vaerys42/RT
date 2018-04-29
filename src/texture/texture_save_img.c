/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_upload.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:45:33 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/29 18:47:06 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"
#include <sys/stat.h>
#include <dirent.h>

int					ft_dir_exist(char *dir_name)
{
	DIR				*dir;

	if ((dir = opendir(dir_name)) != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int					ft_file_exist(char *file_name)
{
	int				fd;

	if ((fd = open(file_name, O_RDONLY)) != -1)
	{
		close(fd);
		free(file_name);
		return (1);
	}
	return (0);
}

char				*ft_concat(char *s1, char *s2)
{
	char			*new;
	int				n;

	n = ft_strlen(s1) + ft_strlen(s2) + 1;
	if ((new = (char *)malloc(sizeof(char) * n)) == NULL)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	return (new);
}

char				*ft_name(void)
{
	char			*file_name;
	int				a;
	char			*tmp;

	a = 0;
	tmp = ft_strcat(ft_itoa(a), ".bmp");
	file_name = ft_concat("screenshots/", tmp);
	if (tmp)
		free(tmp);
	while (ft_file_exist(file_name) == 1)
	{
		a += 1;
		tmp = ft_strcat(ft_itoa(a), ".bmp");
		file_name = ft_concat("screenshots/", tmp);
		if (tmp)
			free(tmp);
	}
	return (file_name);
}

int					ft_save_img(t_rt *rt)
{
	SDL_Surface		*s;
	Uint32			f;
	SDL_Renderer	*renderer;
	char			*file_name;

	if (ft_dir_exist("screenshots") != 1)
		mkdir("screenshots", S_IRWXU);
	file_name = ft_name();
	f = SDL_PIXELFORMAT_ARGB8888;
	renderer = rt->data->sdl_renderer;
	if (renderer)
	{
		s = SDL_CreateRGBSurfaceWithFormat(0, WIN_LEN, WIN_HEIGHT, 32, f);
		SDL_RenderReadPixels(renderer, NULL, f, s->pixels, s->pitch);
		if (SDL_SaveBMP(s, file_name) != 0)
			ft_putendl("Error : screenshot couldn't be saved.");
		SDL_FreeSurface(s);
	}
	if (file_name)
		free(file_name);
	return (0);
}
