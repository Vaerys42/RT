/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 20:11:08 by kboucaud          #+#    #+#             */
/*   Updated: 2018/02/09 20:11:09 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double		ft_check_cone(t_cone *cone, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		k;
	double		det;

	k = pow(tan(cone->angle), 2) + 1;
	ray->obj = ft_sub_vect(ray->o, cone->o);
	a = scal(ray->dir, ray->dir) - k * pow(scal(ray->dir, cone->dir), 2);
	b = 2 * (scal(ray->dir, ray->obj) - k * scal(ray->obj,
	cone->dir) * scal(ray->dir, cone->dir));
	c = scal(ray->obj, ray->obj) - k * pow(scal(cone->dir, ray->obj), 2);
	det = sqrt(fabs(b * b - (4 * a * c)));
	if (b * b - (4 * a * c) < -EPS)
		return (0);
	if (cone->pln == NULL)
		return (disc_eq((-b - det) / (2 * a), (-b + det) / (2 * a)));
	return (ft_inter_plane_ini(ray, cone->pln, (-b - det) / (2 * a),
	(-b + det) / (2 * a)));
}

void		cam_cone_inter(t_rt *rt)
{
	t_coo		hit;

	rt->inter->obj = CON;
	rt->inter->num = rt->cone->id;
	rt->inter->col->r = rt->cone->color->r;
	rt->inter->col->g = rt->cone->color->g;
	rt->inter->col->b = rt->cone->color->b;
	ft_get_point(rt);
	get_norm_cone(rt);
	hit = ft_local_coo(rt->inter->point, rt->cone->o, rt->cone->rot);
	ft_texture_all(rt, hit, rt->cone->texture);
	if (rt->cone->pln != NULL && rt->cone->pln->cut == 1)
	{
		rt->inter->col->r = rt->cone->pln->color->r;
		rt->inter->col->g = rt->cone->pln->color->g;
		rt->inter->col->b = rt->cone->pln->color->b;
	}
}

void		light_cone_inter(t_rt *rt)
{
	rt->light->shine = rt->cone->shine;
	get_norm_cone(rt);
}

void		new_cone_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	rt->inter->reflex = rt->cone->reflex;
	if (type == 0)
		cam_cone_inter(rt);
	if (type == 1)
		rt->inter->light = rt->cone->id;
}

void		check_cone_inter(t_rt *rt, int type)
{
	double tmp;

	if (rt->start->con != NULL)
	{
		rt->cone = rt->start->con;
		while (rt->cone != NULL)
		{
			if (rt->cone->pln != NULL)
				rt->cone->pln->cut = 0;
			if (type == 0)
				tmp = ft_check_cone(rt->cone, rt->ray);
			if (type == 1)
				tmp = ft_check_cone(rt->cone, rt->light_ray);
			if (type == 2 && rt->inter->num == rt->cone->id &&
			rt->inter->light == rt->cone->id)
				light_cone_inter(rt);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_cone_dst(rt, type, tmp);
			rt->cone = rt->cone->next;
		}
	}
}
