/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_upload.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:45:33 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/29 11:58:11 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"
#include <sys/stat.h>
#include <dirent.h>

int					ft_dir_exist(char *dir_name)
{
	DIR			*dir;

	if ((dir = opendir(dir_name)) != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int					ft_file_exist(char *file_name)
{
	int			fd;

	if ((fd = open(file_name, O_RDONLY)) != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}


char			*ft_concat(char *s1, char *s2)
{
    char	*new;
		int		n;

		n = ft_strlen(s1) + ft_strlen(s2) + 1;
    if ((new = (char *)malloc(sizeof(char) * n)) == NULL)
			return (NULL);
    ft_strcpy(new, s1);
    ft_strcat(new, s2);
    return (new);
}

int					ft_save_img(t_rt *rt)
{
	SDL_Surface		*s;
	Uint32			f;
	SDL_Renderer	*renderer;
	char			*file_name;
	int				a;

	if (ft_dir_exist("screenshots") != 1)
		mkdir("screenshots", S_IRWXU);
	a = 45;
	char *b;
	b = ft_itoa(a);

	// file_name = ft_concat(ft_itoa_new(a), ".bmp");
	// file_name = ft_strcat(b, ".bmp");
	// while (ft_file_exist(file_name) == 1)
	// {
	// 	a += 1;
	// 	file_name = ft_strcat(ft_itoa_new(a), ".bmp");
	// }
	// file_name = "screenshots/0.bmp";

	// char *new;
	// new = ft_concat("screenshots/", file_name);
	// ft_putendl(new);
	file_name = "0.bmp";
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
	return (0);
}
