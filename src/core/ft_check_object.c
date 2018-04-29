/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 00:31:27 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 18:38:18 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_get_point(t_rt *rt)
{
	rt->inter->point = ft_mult_vect(rt->inter->dst, rt->ray->dir);
	rt->inter->point = ft_add_vect(rt->ray->o, rt->inter->point);
}

void		check_forms(t_rt *rt, int type)
{
	check_plane_inter(rt, type);
	check_sphere_inter(rt, type);
	check_cone_inter(rt, type);
	check_cylinder_inter(rt, type);
	check_cube_inter(rt, type);
	check_ellipse_inter(rt, type);
	check_parabol_inter(rt, type);
	check_tore_inter(rt, type);
}

void		ft_check_object(t_rt *rt)
{
	rt->inter->dst = MAX;
	rt->inter->obj = 0;
	rt->inter->angle->dir = rt->ray->dir;
	rt->inter->num = 0;
	move_color(rt->inter->col, 0, 0, 0);
	move_color(rt->inter->mat, 0, 0, 0);
	rt->light = rt->start->lgh;
	rt->inter->reflex = 0;
	check_forms(rt, 0);
	if (rt->inter->reflex > 0 && rt->lock == 0)
		ft_reflexion_ray(rt);
	else
	{
		if (rt->inter->dst <= 0.01)
			rt->inter->dst = 0;
		if (rt->inter->dst != MAX)
		{
			ft_get_point(rt);
			ft_get_light(rt);
		}
	}
	return ;
}
