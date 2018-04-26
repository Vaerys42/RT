/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 22:42:10 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/25 22:42:11 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		tore_para_rot(t_rt *rt)
{
	rt->tore = rt->start->tor;
	while (rt->tore != NULL)
	{
		rt->tore->dir = ft_rotation(rt->tore->dir,
		rt->tore->rot);
		if (rt->tore->pln != NULL)
			rt->tore->pln->norm = ft_rotation(rt->tore->pln->norm,
			rt->tore->rot);
		rt->tore = rt->tore->next;
	}
	rt->parabol = rt->start->par;
	while (rt->parabol != NULL)
	{
		rt->parabol->dir = ft_rotation(rt->parabol->dir,
		rt->parabol->rot);
		if (rt->parabol->pln != NULL)
			rt->parabol->pln->norm = ft_rotation(rt->parabol->pln->norm,
			rt->parabol->rot);
		rt->parabol = rt->parabol->next;
	}
}

void		cyl_cone_rot(t_rt *rt)
{
	rt->cylinder = rt->start->cyl;
	while (rt->cylinder != NULL)
	{
		rt->cylinder->dir = ft_rotation(rt->cylinder->dir,
		rt->cylinder->rot);
		if (rt->cylinder->pln != NULL)
			rt->cylinder->pln->norm = ft_rotation(rt->cylinder->pln->norm,
			rt->cylinder->rot);
		rt->cylinder = rt->cylinder->next;
	}
	rt->cone = rt->start->con;
	while (rt->cone != NULL)
	{
		rt->cone->dir = ft_rotation(rt->cone->dir, rt->cone->rot);
		if (rt->cone->pln != NULL)
			rt->cone->pln->norm = ft_rotation(rt->cone->pln->norm,
			rt->cone->rot);
		rt->cone = rt->cone->next;
	}
}

void		sphere_ellipse_rot(t_rt *rt)
{
	rt->sphere = rt->start->sph;
	while (rt->sphere != NULL)
	{
		if (rt->sphere->pln != NULL)
		{
			rt->sphere->pln->norm = ft_add_vect(rt->sphere->pln->norm,
			rt->sphere->dir);
			rt->sphere->pln->norm = ft_rotation(rt->sphere->pln->norm,
			rt->sphere->rot);
		}
		rt->sphere = rt->sphere->next;
	}
	rt->ellipse = rt->start->ell;
	while (rt->ellipse != NULL)
	{
		rt->ellipse->rad1 = ft_rotation(rt->ellipse->rad1, rt->ellipse->rot);
		rt->ellipse->rad2 = ft_rotation(rt->ellipse->rad2, rt->ellipse->rot);
		rt->ellipse->rad3 = ft_rotation(rt->ellipse->rad3, rt->ellipse->rot);
		if (rt->ellipse->pln != NULL)
			rt->ellipse->pln->norm = ft_rotation(rt->ellipse->pln->norm,
			rt->ellipse->rot);
		rt->ellipse = rt->ellipse->next;
	}
}
