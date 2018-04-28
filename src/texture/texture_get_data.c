/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:59:34 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/28 18:00:42 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

char			*get_path(char **str)
{
	char		*path;

	path = NULL;
	tab_len(str);
	path = ft_strtrim(str[1]);
	ft_check_img_path(path);
	return (path);
}

t_coo			get_scale(char **str, int err)
{
	t_coo		new;

	if (tab_len(str) != 3)
		ft_bad_arg(err);
	new.x = ft_atof(str[1]);
	new.y = ft_atof(str[2]);
	if (new.x <= 0 || new.y <= 0)
	{
		ft_putstr("Please use valid scale in config file. Usage => scale: x y\
		\n-----------------------------------------------------------------\
		\nTo stretch texture vertically   : 0 < x <= 1\
		\nTo squeeze texture vertically   :     x >= 1\
		\nTo stretch texture horizontally : 0 < y <= 1\
		\nTo squeeze texture horizontally :     y >= 1\
		\n-----------------------------------------------------------------\n");
		exit(-1);
	}
	return (new);
}

t_coo			get_offset(char **str, int err)
{
	t_coo		new;

	if (tab_len(str) != 3)
		ft_bad_arg(err);
	new.x = ft_atof(str[1]);
	new.y = ft_atof(str[2]);
	if (new.x < 0 || new.y < 0 || new.x > 1 || new.y > 1)
	{
		ft_putstr("Please use valid offset in config file. Usage => offset: x y\
		\n-----------------------------------------------------------------\
		\nx and y must be contained in double interval [0, 1].\
		\n-----------------------------------------------------------------\n");
		exit(-1);
	}
	return (new);
}

int				get_texture_type(char **str)
{
	int			a;

	if (tab_len(str) != 2)
		ft_bad_arg(4);
	a = (int)ft_atof(str[1]);
	if (a < 1 || a > 11)
	{
		ft_putstr("Please use valid texture id in config file.\
		\n-----------------------------------------------------------------\
		\n1     Uploaded_texture\
		\n2->12 Color pertubation :\
		\n      2 Checker\
		\n      3 Stripes\
		\n      4 Rainbow\
		\n      5 Woodgrains\
		\n      6 Wavy\
		\n      7 Perlin Simple\
		\n      8 Perlin Wood\
		\n      9 Perlin Marble\
		\n     10 Squares\
		\n     11	Sparkle\
		\n-----------------------------------------------------------------\n");
		exit(-1);
	}
	return (a);
}
