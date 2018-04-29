/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:00:38 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:00:41 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double				ft_check_plane(t_plane *plane, t_ray *ray)
{
	double		a;
	double		b;

	b = scal(plane->norm, ray->dir);
	if (b == 0)
		return (-1);
	a = scal(plane->norm, ray->o) + plane->supp;
	return (-a / b);
}

void				new_plane_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	rt->inter->reflex = rt->plane->reflex;
	if (type == 0)
	{
		rt->inter->obj = PLN;
		rt->inter->angle->dir = rt->plane->norm;
		rt->inter->num = rt->plane->id;
		rt->inter->col->r = rt->plane->color->r;
		rt->inter->col->g = rt->plane->color->g;
		rt->inter->col->b = rt->plane->color->b;
		ft_texture_all(rt, rt->inter->point, rt->plane->texture);
	}
	if (type == 1)
		rt->inter->light = rt->plane->id;
}

void				check_plane_inter(t_rt *rt, int type)
{
	double		tmp;

	if (rt->start->pln != NULL)
	{
		rt->plane = rt->start->pln;
		while (rt->plane != NULL)
		{
			if (type == 0)
				tmp = ft_check_plane(rt->plane, rt->ray);
			if (type == 1)
				tmp = ft_check_plane(rt->plane, rt->light_ray);
			if (type == 2 && rt->inter->num == rt->plane->id &&
			rt->inter->light == rt->plane->id)
			{
				rt->light->shine = 0;
				rt->inter->angle->dir = rt->plane->norm;
			}
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_plane_dst(rt, type, tmp);
			rt->plane = rt->plane->next;
		}
	}
}
