/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 22:05:23 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 22:05:24 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_cone_info(t_cone *cone)
{
	if (cone->color == NULL)
		ft_putstr("Needs color for cone (0 to 1). Ex : color: 1 0 1\n");
	else if (cone->angle < 0)
		ft_putstr("Needs angle for cone. Ex angle: 30\n");
	else if (cone->shine < 0)
		ft_putstr("Needs shine for cone. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

void		ft_ellipse_info(t_ellipse *ellipse)
{
	if (ellipse->color == NULL)
		ft_putstr("Needs color for ellipse (0 to 1). Ex : color: 1 0 1\n");
	else if (ellipse->shine < 0)
		ft_putstr("Needs shine for ellipse. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

void		ft_sphere_info(t_sphere *sphere)
{
	if (sphere->color == NULL)
		ft_putstr("Needs color for sphere (0 to 1). Ex : color: 1 0 1\n");
	else if (sphere->radius == -1)
		ft_putstr("Needs radius for sphere. Ex radius: 3\n");
	else if (sphere->shine < 0)
		ft_putstr("Needs shine for sphere. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

void		ft_tore_info(t_tore *tore)
{
	if (tore->color == NULL)
		ft_putstr("Needs color for tore (0 to 1). Ex : color: 1 0 1\n");
	else if (tore->radiusa == -1)
		ft_putstr("Needs radius for tore. Ex radius: 3\n");
	else if (tore->radiusb == -1)
		ft_putstr("Needs radius for tore. Ex radius: 3\n");
	else if (tore->shine < 0)
		ft_putstr("Needs shine for tore. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

void		ft_parabol_info(t_parabol *parabol)
{
	if (parabol->color == NULL)
		ft_putstr("Needs color for parabol (0 to 1). Ex : color: 1 0 1\n");
	else if (parabol->rad1 == -1)
		ft_putstr("Needs radius for parabol. Ex radius: 3\n");
	else if (parabol->shine < 0)
		ft_putstr("Needs shine for parabol. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}
