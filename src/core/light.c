/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 18:18:21 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/25 18:18:22 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_apply_light(t_rt *rt)
{
	rt->inter->mat->r += rt->inter->col->r * rt->amb;
	rt->inter->mat->g += rt->inter->col->g * rt->amb;
	rt->inter->mat->b += rt->inter->col->b * rt->amb;
}

void		ft_light_diffspec(t_rt *rt)
{
	double		diff;
	t_coo		refl;
	double		spec;

	rt->light_ray->dir = ft_sub_vect(rt->light->o, rt->inter->point);
	rt->light_ray->dir = ft_normalize(rt->light_ray->dir);
	rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	diff = scal(rt->light_ray->dir, rt->inter->angle->dir);
	diff = (diff < EPS) ? EPS : diff;
	rt->light_ray->dir = ft_mult_vect(-1, rt->light_ray->dir);
	refl = ft_add_vect(rt->light_ray->dir, ft_mult_vect(diff,
	rt->inter->angle->dir));
	refl = ft_normalize(refl);
	spec = scal(refl, ft_sub_vect(refl, rt->light_ray->dir));
	rt->inter->mat->r += rt->light->power * rt->inter->lgh->r * diff
	+ rt->light->shine * pow(spec, 10);
	rt->inter->mat->g += rt->light->power * rt->inter->lgh->g * diff
	+ rt->light->shine * pow(spec, 10);
	rt->inter->mat->b += rt->light->power * rt->inter->lgh->b * diff
	+ rt->light->shine * pow(spec, 10);
}

void		ft_spot(t_rt *rt)
{
	double		angle;

	angle = 0;
	if (ft_norme(rt->light->dir) > 0 && ft_norme(rt->light->norm) == 0)
	{
		angle = acos(scal(rt->light_ray->dir, rt->light->dir));
		if (angle > rt->light->angle * M_PI / 180)
			move_color(rt->inter->lgh, 0, 0, 0);
	}
}

void		ft_rampe(t_rt *rt)
{
	double		angle;
	t_coo		inter;
	double		k;

	angle = 0;
	if (ft_norme(rt->light->norm) > 0)
	{
		inter = ft_det_vect(rt->light->norm, rt->light->dir);
		rt->light_ray->dir = ft_sub_vect(rt->inter->point, rt->light->o);
		k = ft_norme(rt->light_ray->dir) * scal(ft_normalize(
		rt->light_ray->dir), ft_normalize(inter)) / ft_norme(inter);
		rt->light_ray->o.x = rt->light->o.x + k * inter.x;
		rt->light_ray->o.y = rt->light->o.y + k * inter.y;
		rt->light_ray->o.z = rt->light->o.z + k * inter.z;
		rt->light_ray->dir = ft_sub_vect(rt->inter->point, rt->light_ray->o);
		rt->light_ray->dir = ft_normalize(rt->light_ray->dir);
		angle = acos(scal(rt->light_ray->dir, rt->light->dir));
		if (angle > rt->light->angle * M_PI / 180)
			move_color(rt->inter->lgh, 0, 0, 0);
	}
}

void		ft_get_light(t_rt *rt)
{
	move_color(rt->inter->mat, 0, 0, 0);
	rt->light = rt->start->lgh;
	while (rt->light)
	{
		rt->inter->dst = MAX;
		rt->inter->light = -1;
		rt->light->dir = ft_normalize(rt->light->dir);
		rt->inter->angle->dir = rt->ray->dir;
		rt->light_ray->o = rt->light->o;
		rt->light_ray->dir = ft_normalize(
		ft_sub_vect(rt->inter->point, rt->light->o));
		move_color(rt->inter->lgh, rt->light->color->r,
		rt->light->color->g, rt->light->color->b);
		rt->light->shine = 0;
		ft_spot(rt);
		ft_rampe(rt);
		check_forms(rt, 1);
		check_forms(rt, 2);
		ft_light_diffspec(rt);
		rt->light = rt->light->next;
	}
	ft_apply_light(rt);
	ft_check_expose(rt->inter->mat, 1.0);
}
