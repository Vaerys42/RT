/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 18:59:34 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 18:59:37 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_material	*check_color(t_material *color, char **str)
{
	if (color)
		free(color);
	return (get_color(str));
}

int			tab_len(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

t_coo		get_coo(char **str, int err)
{
	t_coo			new;

	if (tab_len(str) != 4)
		ft_bad_arg(err);
	new.x = ft_atof(str[1]);
	new.y = ft_atof(str[2]);
	new.z = ft_atof(str[3]);
	return (new);
}

t_material	*get_color(char **str)
{
	t_material		*color;

	if (tab_len(str) != 4)
		ft_bad_arg(3);
	if (!(color = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	color->r = ft_atof(str[1]);
	color->g = ft_atof(str[2]);
	color->b = ft_atof(str[3]);
	if (color->r < 0 || color->g < 0 || color->b < 0)
	{
		ft_putstr("Please use valid colors.\n");
		exit(-1);
	}
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
	return (color);
}

double		get_radius(char **str)
{
	double		radius;

	if (tab_len(str) != 2)
		ft_bad_arg(4);
	radius = ft_atof(str[1]);
	if (radius < 0)
	{
		ft_putstr("Please use valid radius or shine\n");
		exit(-1);
	}
	return (radius);
}
