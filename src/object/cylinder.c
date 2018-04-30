/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:20:13 by kboucaud          #+#    #+#             */
/*   Updated: 2018/02/09 20:20:14 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double		ft_check_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;

	ray->obj = ft_sub_vect(ray->o, cylinder->o);
	a = scal(ray->dir, ray->dir) - pow(scal(ray->dir, cylinder->dir), 2);
	b = 2 * (scal(ray->dir, ray->obj) - (scal(ray->dir, cylinder->dir) *
	scal(ray->obj, cylinder->dir)));
	c = scal(ray->obj, ray->obj) - pow(scal(ray->obj, cylinder->dir), 2) -
	pow(cylinder->radius, 2);
	t1 = (-b - sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	t2 = (-b + sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	if (b * b - (4 * a * c) < -EPS)
		return (0);
	if (cylinder->pln == NULL)
		return (disc_eq(t1, t2));
	return (ft_inter_plane_ini(ray, cylinder->pln, t1, t2));
}

void		cam_cylinder_inter(t_rt *rt)
{
	t_coo		hit;

	rt->inter->obj = CYL;
	rt->inter->num = rt->cylinder->id;
	rt->inter->col->r = rt->cylinder->color->r;
	rt->inter->col->g = rt->cylinder->color->g;
	rt->inter->col->b = rt->cylinder->color->b;
	ft_get_point(rt);
	norm_cylinder(rt);
	hit = ft_local_coo(rt->inter->point, rt->cylinder->o, rt->cylinder->rot);
	ft_texture_all(rt, hit, rt->cylinder->texture);
	if (rt->cylinder->pln != NULL && rt->cylinder->pln->cut == 1)
	{
		rt->inter->col->r = rt->cylinder->pln->color->r;
		rt->inter->col->g = rt->cylinder->pln->color->g;
		rt->inter->col->b = rt->cylinder->pln->color->b;
	}
}

void		light_cylinder_inter(t_rt *rt)
{
	rt->light->shine = rt->cylinder->shine;
	norm_cylinder(rt);
}

void		new_cylinder_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	rt->inter->reflex = rt->cylinder->reflex;
	if (type == 0)
		cam_cylinder_inter(rt);
	if (type == 1)
		rt->inter->light = rt->cylinder->id;
}

void		check_cylinder_inter(t_rt *rt, int type)
{
	double tmp;

	if (rt->start->cyl != NULL)
	{
		rt->cylinder = rt->start->cyl;
		while (rt->cylinder != NULL)
		{
			if (rt->cylinder->pln != NULL)
				rt->cylinder->pln->cut = 0;
			if (type == 0)
				tmp = ft_check_cylinder(rt->cylinder, rt->ray);
			if (type == 1)
				tmp = ft_check_cylinder(rt->cylinder, rt->light_ray);
			if (type == 2 && rt->inter->num == rt->cylinder->id &&
			rt->inter->light == rt->cylinder->id)
				light_cylinder_inter(rt);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_cylinder_dst(rt, type, tmp);
			rt->cylinder = rt->cylinder->next;
		}
	}
}
