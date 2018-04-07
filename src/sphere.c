/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:01:32 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:01:34 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double		ft_check_sphere(t_sphere *sphere, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;

	ray->obj = ft_sub_vect(ray->o, sphere->o);
	a = scal(ray->dir, ray->dir);
	b = 2 * (scal(ray->dir, ray->obj));
	c = scal(ray->obj, ray->obj) - pow(sphere->radius, 2);
	delta = b * b - (4 * a * c);
	if (sphere->obj->pln == NULL)
        return (disc_eq(a, b, c, delta));
	return (ft_inter_plane_ini(ray, sphere->obj, a, b, c));
}

void		new_sphere_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
	{
		rt->inter->obj = SPH;
		rt->inter->mat->r = rt->sphere->color->r * rt->light->amb;
		rt->inter->mat->g = rt->sphere->color->g * rt->light->amb;
		rt->inter->mat->b = rt->sphere->color->b * rt->light->amb;
		if (rt->sphere->obj->cut == 1 && rt->sphere->obj->pln != NULL)
		{
			rt->inter->mat->r = rt->sphere->obj->pln->color->r * rt->light->amb;
			rt->inter->mat->g = rt->sphere->obj->pln->color->g * rt->light->amb;
			rt->inter->mat->b = rt->sphere->obj->pln->color->b * rt->light->amb;
		}
	}
	if (type == 1 && rt->inter->obj == SPH)
	{
		rt->light->shine = rt->sphere->shine;
		rt->inter->angle->o = ft_sub_vect(rt->inter->point,
		rt->sphere->o);
		rt->inter->angle->dir = ft_rotation(rt->inter->angle->dir, rt->sphere->rot);
		if (rt->sphere->obj->cut == 1)
			rt->inter->angle->dir = ft_mult_vect(-1, rt->sphere->obj->pln->norm);	
		rt->inter->angle->dir = ft_normalize(rt->inter->angle->o);
		rt->inter->mat->r *= 2;
		rt->inter->mat->g *= 2;
		rt->inter->mat->b *= 2;
	}
}

void		check_sphere_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->sph != NULL)
	{
		rt->sphere = rt->start->sph;
		while (rt->sphere != NULL)
		{
			rt->sphere->obj->cut = 0;
			if (type == 0)
				tmp = ft_check_sphere(rt->sphere, rt->ray);
			else
				tmp = ft_check_sphere(rt->sphere, rt->light_ray);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_sphere_dst(rt, type, tmp);
			rt->sphere = rt->sphere->next;
		}
	}
}
