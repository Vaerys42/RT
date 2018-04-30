/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 17:22:51 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/25 17:22:52 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

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
		free(tmp->texture->path);
		SDL_FreeSurface(tmp->texture->surface);
		free(tmp->texture);
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
		free(tmp->texture->path);
		SDL_FreeSurface(tmp->texture->surface);
		free(tmp->texture);
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
		free(tmp->texture->path);
		SDL_FreeSurface(tmp->texture->surface);
		free(tmp->texture);
		free(tmp);
	}
}

void		free_parabol(t_rt *rt)
{
	t_parabol		*tmp;

	rt->parabol = rt->start->par;
	while (rt->parabol)
	{
		tmp = rt->parabol;
		rt->parabol = rt->parabol->next;
		if (tmp->pln)
		{
			free(tmp->pln->color);
			free(tmp->pln);
		}
		free(tmp->color);
		free(tmp);
	}
}

void		free_tore(t_rt *rt)
{
	t_tore		*tmp;

	rt->tore = rt->start->tor;
	while (rt->tore)
	{
		tmp = rt->tore;
		rt->tore = rt->tore->next;
		if (tmp->pln)
		{
			free(tmp->pln->color);
			free(tmp->pln);
		}
		free(tmp->color);
		free(tmp);
	}
}
