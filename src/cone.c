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

#include "../rt.h"

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
	b = 2 * (scal(ray->dir, ray->obj) - k * scal(ray->obj, cone->dir) * scal(ray->dir, cone->dir));
	c = scal(ray->obj, ray->obj) - k * pow(scal(cone->dir, ray->obj), 2);
	det = sqrt(fabs(b * b - (4 * a * c)));
	if (b * b - (4 * a * c) < -EPS)
		return (0);
	if (cone->pln == NULL)
		return (disc_eq((-b - det) / (2 * a), (-b + det) / (2 * a)));
	return (ft_inter_plane_ini(ray, cone->pln, (-b - det) / (2 * a), (-b + det) / (2 * a)));
}

void		cam_cone_inter(t_rt *rt)
{
	rt->inter->obj = CON;
	rt->inter->num = rt->cone->id;
	rt->inter->col->r = rt->cone->color->r;
	rt->inter->col->g = rt->cone->color->g;
	rt->inter->col->b = rt->cone->color->b;
	if (rt->cone->pln != NULL && rt->cone->pln->cut == 1)
	{
		rt->inter->col->r = rt->cone->pln->color->r;
		rt->inter->col->g = rt->cone->pln->color->g;
		rt->inter->col->b = rt->cone->pln->color->b;
	}
}

void		light_cone_inter(t_rt *rt)
{
	t_coo		point;
	t_coo		a;
	double		op;

	rt->light->shine = rt->cone->shine;
	point = ft_inv_rot(rt->cone->o, rt->cone->rot);
	op = ft_norme(ft_sub_vect(rt->inter->point, rt->cone->o));
	a = ft_new_vect(rt->cone->o.x, point.y + op / cos(rt->cone->angle / 2), rt->cone->o.z);
	a = ft_rotation(a, rt->cone->rot);
	rt->inter->angle->dir = ft_sub_vect(rt->inter->point, a);
	if (rt->cone->pln != NULL && rt->cone->pln->cut == 1)
		rt->inter->angle->dir = rt->cone->pln->norm;
}

void		new_cone_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		cam_cone_inter(rt);
	if (type == 1 && rt->inter->num == rt->cone->id)
		light_cone_inter(rt);
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
			else
				tmp = ft_check_cone(rt->cone, rt->light_ray);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_cone_dst(rt, type, tmp);
			rt->cone = rt->cone->next;
		}
	}
}
