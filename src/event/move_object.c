/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:40:59 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/10 13:41:00 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		get_obj(t_rt *rt, int x, int y)
{
	rt->op->maintain = 1;
	ft_ini_ray(rt, x, y);
	rt->light = rt->start->lgh;
	rt->inter->obj = 0;
	rt->inter->dst = MAX;
	check_forms(rt, 0);
	rt->op->obj = rt->inter->obj;
	rt->op->id = rt->inter->num;
}

void		move_object(t_rt *rt, SDL_Event ev)
{
	if (rt->op->obj == SPH)
		move_sphere(rt, ev);
	else if (rt->op->obj == CON)
		move_cone(rt, ev);
	else if (rt->op->obj == CYL)
		move_cyl(rt, ev);
	else if (rt->op->obj == PLN)
		move_plane(rt, ev);
	ft_reset(rt);
	ft_raytracing(rt);
}
