/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 22:33:18 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/25 22:33:19 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		move_sphere(t_rt *rt, SDL_Event ev)
{
	rt->sphere = rt->start->sph;
	while (rt->sphere->id != rt->op->id)
		rt->sphere = rt->sphere->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->sphere->o.x += (float)ev.motion.xrel / 100;
		rt->sphere->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->sphere->o.z += (float)ev.wheel.y / 100;
	if (rt->sphere->pln != NULL)
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			rt->sphere->pln->o.x += (float)ev.motion.xrel / 100;
			rt->sphere->pln->o.y += -(float)ev.motion.yrel / 100;
		}
		else if (ev.type == SDL_MOUSEWHEEL)
			rt->sphere->pln->o.z += (float)ev.wheel.y / 100;
	}
}

void		move_plane(t_rt *rt, SDL_Event ev)
{
	rt->plane = rt->start->pln;
	while (rt->plane->id != rt->op->id)
		rt->plane = rt->plane->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->plane->o.x += (float)ev.motion.xrel / 100;
		rt->plane->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->plane->o.z += (float)ev.wheel.y / 100;
}

void		move_cyl(t_rt *rt, SDL_Event ev)
{
	rt->cylinder = rt->start->cyl;
	while (rt->cylinder->id != rt->op->id)
		rt->cylinder = rt->cylinder->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->cylinder->o.x += (float)ev.motion.xrel / 100;
		rt->cylinder->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->cylinder->o.z += (float)ev.wheel.y / 100;
	if (rt->cylinder->pln != NULL)
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			rt->cylinder->pln->o.x += (float)ev.motion.xrel / 100;
			rt->cylinder->pln->o.y += -(float)ev.motion.yrel / 100;
		}
		else if (ev.type == SDL_MOUSEWHEEL)
			rt->cylinder->pln->o.z += (float)ev.wheel.y / 100;
	}
}

void		move_cone(t_rt *rt, SDL_Event ev)
{
	rt->cone = rt->start->con;
	while (rt->cone->id != rt->op->id)
		rt->cone = rt->cone->next;
	if (ev.type == SDL_MOUSEMOTION)
	{
		rt->cone->o.x += (float)ev.motion.xrel / 100;
		rt->cone->o.y += -(float)ev.motion.yrel / 100;
	}
	else if (ev.type == SDL_MOUSEWHEEL)
		rt->cone->o.z += (float)ev.wheel.y / 100;
	if (rt->cone->pln != NULL)
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			rt->cone->pln->o.x += (float)ev.motion.xrel / 100;
			rt->cone->pln->o.y += -(float)ev.motion.yrel / 100;
		}
		else if (ev.type == SDL_MOUSEWHEEL)
			rt->cone->pln->o.z += (float)ev.wheel.y / 100;
	}
}
