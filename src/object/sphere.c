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

#include "../../rt.h"

double		ft_check_sphere(t_sphere *sphere, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;

	ray->obj = ft_sub_vect(ray->o, sphere->o);
	a = scal(ray->dir, ray->dir);
	b = 2 * (scal(ray->dir, ray->obj));
	c = scal(ray->obj, ray->obj) - pow(sphere->radius, 2);
	t1 = (-b - sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	t2 = (-b + sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	if (b * b - (4 * a * c) < -EPS)
		return (0);
	if (sphere->pln == NULL)
		return (disc_eq(t1, t2));
	return (ft_inter_plane_ini(ray, sphere->pln, t1, t2));
}

void		cam_sphere_inter(t_rt *rt)
{
	t_coo			hit;

	rt->inter->obj = SPH;
	rt->inter->num = rt->sphere->id;
	rt->inter->col->r = rt->sphere->color->r;
	rt->inter->col->g = rt->sphere->color->g;
	rt->inter->col->b = rt->sphere->color->b;
	ft_get_point(rt);
	hit = ft_local_coo(rt->inter->point, rt->sphere->o, rt->sphere->rot);
	ft_texture_all(rt, hit, rt->sphere->texture);
	if (rt->sphere->pln != NULL && rt->sphere->pln->cut == 1)
	{
		rt->inter->col->r = rt->sphere->pln->color->r;
		rt->inter->col->g = rt->sphere->pln->color->g;
		rt->inter->col->b = rt->sphere->pln->color->b;
	}
	rt->inter->angle->o = ft_sub_vect(rt->inter->point, rt->sphere->o);
	rt->inter->angle->dir = ft_rotation(rt->inter->angle->dir, rt->sphere->rot);
	if (rt->sphere->pln != NULL && rt->sphere->pln->cut == 1)
		rt->inter->angle->dir = rt->sphere->pln->norm;
	rt->inter->angle->dir = ft_normalize(rt->inter->angle->o);
}

void		light_sphere_inter(t_rt *rt)
{
	rt->light->shine = rt->sphere->shine;
	rt->inter->angle->o = ft_sub_vect(rt->inter->point,
	rt->sphere->o);
	rt->inter->angle->dir = ft_rotation(rt->inter->angle->dir, rt->sphere->rot);
	if (rt->sphere->pln != NULL && rt->sphere->pln->cut == 1)
		rt->inter->angle->dir = rt->sphere->pln->norm;
	rt->inter->angle->dir = ft_normalize(rt->inter->angle->o);
}

void		new_sphere_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	rt->inter->reflex = rt->sphere->reflex;
	if (type == 0)
		cam_sphere_inter(rt);
	if (type == 1)
		rt->inter->light = rt->sphere->id;
}

void		check_sphere_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->sph != NULL)
	{
		rt->sphere = rt->start->sph;
		while (rt->sphere != NULL)
		{
			if (rt->sphere->pln != NULL)
				rt->sphere->pln->cut = 0;
			if (type == 0)
				tmp = ft_check_sphere(rt->sphere, rt->ray);
			if (type == 1)
				tmp = ft_check_sphere(rt->sphere, rt->light_ray);
			if (type == 2 && rt->inter->num == rt->sphere->id
			&& rt->inter->light == rt->sphere->id)
				light_sphere_inter(rt);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_sphere_dst(rt, type, tmp);
			rt->sphere = rt->sphere->next;
		}
	}
}
