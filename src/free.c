/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:39:51 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/17 11:39:51 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		free_sphere(t_rt *rt)
{
	t_sphere		*tmp;

	rt->sphere = rt->start->sph;
	while (rt->sphere)
	{
		tmp = rt->sphere;
		rt->sphere = rt->sphere->next;
		if (tmp->pln)
		{
			free(tmp->pln->color);
			free(tmp->pln);
		}
		free(tmp->color);
		free(tmp);
	}
}

void		free_cylinder(t_rt *rt)
{
	t_cylinder		*tmp;

	rt->cylinder = rt->start->cyl;
	while (rt->cylinder)
	{
		tmp = rt->cylinder;
		rt->cylinder = rt->cylinder->next;
		if (tmp->pln)
		{
			free(tmp->pln->color);
			free(tmp->pln);
		}
		free(tmp->color);
		free(tmp);
	}
}

void		free_cone(t_rt *rt)
{
	t_cone		*tmp;

	rt->cone = rt->start->con;
	while (rt->cone)
	{
		tmp = rt->cone;
		rt->cone = rt->cone->next;
		if (tmp->pln)
		{
			free(tmp->pln->color);
			free(tmp->pln);
		}
		free(tmp->color);
		free(tmp);
	}
}

void		free_plane(t_rt *rt)
{
	t_plane		*tmp;

	rt->plane = rt->start->pln;
	while (rt->plane)
	{
		tmp = rt->plane;
		rt->plane = rt->plane->next;
		free(tmp->color);
		free(tmp);
	}
}

void		free_ellipse(t_rt *rt)
{
	t_ellipse		*tmp;

	rt->ellipse = rt->start->ell;
	while (rt->ellipse)
	{
		tmp = rt->ellipse;
		rt->ellipse = rt->ellipse->next;
		if (tmp->pln)
		{
			free(tmp->pln->color);
			free(tmp->pln);
		}
		free(tmp->color);
		free(tmp);
	}
}

void		free_cube(t_rt *rt)
{
	t_cube		*tmp;

	rt->cube = rt->start->cub;
	while (rt->cube)
	{
		tmp = rt->cube;
		rt->cube = rt->cube->next;
		free(tmp->color);
		free(tmp);
	}
}

void		free_light(t_rt *rt)
{
	t_light		*tmp;

	rt->light = rt->start->lgh;
	while (rt->light)
	{
		tmp = rt->light;
		rt->light = rt->light->next;
		free(tmp->color);
		free(tmp);
	}
}

void		free_parser(t_rt *rt)
{
	if (rt->start->pln)
		free_plane(rt);
	if (rt->start->sph)
		free_sphere(rt);
	if (rt->start->cyl)
		free_cylinder(rt);
	if (rt->start->con)
		free_cone(rt);
	if (rt->start->ell)
		free_ellipse(rt);
	if (rt->start->cub)
		free_cube(rt);
	if (rt->start->lgh)
		free_light(rt);
	free(rt->cam);
	free(rt->start);
	free(rt->view);
}
