/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 18:47:45 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/02 18:47:47 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_bad_arg(int i)
{
	if (i == 0)
		ft_putstr("bad number of arguments\n");
	else if (i == 2)
		ft_putstr("Coordinate error\n");
	else if (i == 3)
		ft_putstr("Color error\n");
	else if (i == 4)
		ft_putstr("Radius or angle error\n");
	else if (i == 5)
		ft_putstr("Bad informations\n");
	else if (i == 6)
		ft_putstr("Normal vector error\n");
	else if (i == 7)
		ft_putstr("Dir vector error\n");
	else if (i == 8)
		ft_putstr("Scale error\n");
	else if (i == 9)
		ft_putstr("Offset error\n");
	else if (i == 10)
		ft_putstr("Path error\n");
	else if (i == 11)
		ft_putstr("Ambiant light error\n");
	else
		ft_putstr("File error\n");
	exit(-1);
}

void		ft_malloc_error(void)
{
	ft_putstr("malloc error\n");
	exit(-1);
}

void		ft_exit(void)
{
	ft_putstr("error\n");
	printf("%s\n", SDL_GetError());
	exit(-1);
}

void		ttf_exit(void)
{
	ft_putstr("TTF Error\n");
	exit(-1);
}
