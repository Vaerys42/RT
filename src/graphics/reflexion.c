/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 22:34:55 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/30 21:19:23 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_coo	ft_reflexion(t_rt *rt)
{
	t_coo	newray;
	double	dotp;

	rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	rt->ray->dir = ft_normalize(rt->ray->dir);
	dotp = scal(rt->ray->dir, rt->inter->angle->dir);
	newray.x = rt->ray->dir.x - 2 * dotp * rt->inter->angle->dir.x;
	newray.y = rt->ray->dir.y - 2 * dotp * rt->inter->angle->dir.y;
	newray.z = rt->ray->dir.z - 2 * dotp * rt->inter->angle->dir.z;
	newray = ft_normalize(newray);
	return (newray);
}

void	reflexion_transparency(t_rt *rt)
{
	t_material color;

	color.r = rt->inter->mat->r;
	color.g = rt->inter->mat->g;
	color.b = rt->inter->mat->b;
	rt->lock = 1;
	rt->inter->mat->r = 0;
	rt->inter->mat->b = 0;
	rt->inter->mat->g = 0;
	rt->ray->o = rt->cam->pos;
	rt->ray->dir = rt->tmp;
	ft_check_object(rt);
	rt->inter->mat->r = (float)rt->reflex * color.r +
	(1 - (float)rt->reflex) * rt->inter->mat->r;
	rt->inter->mat->g = (float)rt->reflex * color.g +
	(1 - (float)rt->reflex) * rt->inter->mat->g;
	rt->inter->mat->b = (float)rt->reflex * color.b +
	(1 - (float)rt->reflex) * rt->inter->mat->b;
	ft_check_expose(rt->inter->mat, 1.0);
}

void	reflexion_depth(t_rt *rt)
{
	while (rt->inter->reflex > 0 && rt->depth < rt->maxdepth)
	{
		if (rt->inter->dst <= 0.01)
			rt->inter->dst = 0;
		if (rt->inter->dst != MAX)
		{
			ft_get_point(rt);
			rt->depth++;
			rt->ray->dir = ft_reflexion(rt);
			rt->ray->o = rt->inter->point;
			rt->inter->dst = MAX;
			rt->inter->reflex = 0;
			check_forms(rt, 0);
		}
	}
}

void	ft_reflexion_ray(t_rt *rt)
{
	rt->reflex = rt->inter->reflex;
	reflexion_depth(rt);
	if (rt->inter->dst <= 0.01)
		rt->inter->dst = 0;
	if (rt->inter->dst != MAX)
	{
		ft_get_point(rt);
		rt->ray->o = rt->cam->pos;
		rt->ray->dir = rt->inter->point;
		rt->ray->dir = ft_normalize(rt->ray->dir);
		rt->light = rt->start->lgh;
		if (rt->inter->reflex <= 0)
			ft_get_light(rt);
	}
	reflexion_transparency(rt);
}
