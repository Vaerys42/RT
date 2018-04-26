/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:22:58 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/09 14:23:01 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double		ft_check_ellipse(t_ellipse *ellipse, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;

	ray->obj = ft_sub_vect(ray->o, ellipse->o);
	a = pow(ray->dir.x / ellipse->rad1.x, 2) + pow(ray->dir.y
	/ ellipse->rad2.y, 2) + pow(ray->dir.z / ellipse->rad3.z, 2);
	b = 2 * (ray->dir.x * ray->obj.x * pow(1 / ellipse->rad1.x, 2)
	+ ray->dir.y * ray->obj.y * pow(1 / ellipse->rad2.y, 2) +
	ray->dir.z * ray->obj.z * pow(1 / ellipse->rad3.z, 2));
	c = pow(ray->obj.x / ellipse->rad1.x, 2) + pow(ray->obj.y /
	ellipse->rad2.y, 2) + pow(ray->obj.z / ellipse->rad3.z, 2) - 1;
	t1 = (-b - sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	t2 = (-b + sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	if (b * b - (4 * a * c) < -EPS)
		return (0);
	if (ellipse->pln == NULL)
		return (disc_eq(t1, t2));
	return (ft_inter_plane_ini(ray, ellipse->pln, t1, t2));
}

void		cam_ellipse_inter(t_rt *rt)
{
	rt->inter->obj = ELL;
	rt->inter->num = rt->ellipse->id;
	rt->inter->col->r = rt->ellipse->color->r;
	rt->inter->col->g = rt->ellipse->color->g;
	rt->inter->col->b = rt->ellipse->color->b;
	if (rt->ellipse->pln != NULL && rt->ellipse->pln->cut == 1)
	{
		rt->inter->col->r = rt->ellipse->pln->color->r;
		rt->inter->col->g = rt->ellipse->pln->color->g;
		rt->inter->col->b = rt->ellipse->pln->color->b;
	}
}

void		light_ellipse_inter(t_rt *rt)
{
	rt->light->shine = rt->ellipse->shine;
	rt->inter->angle->dir = ft_sub_vect(rt->inter->point,
	rt->ellipse->o);
	if (rt->ellipse->pln != NULL && rt->ellipse->pln->cut == 1)
		rt->inter->angle->dir = rt->ellipse->pln->norm;
}

void		new_ellipse_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		cam_ellipse_inter(rt);
	if (type == 1)
		rt->inter->light = rt->ellipse->id;
}

void		check_ellipse_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->ell != NULL)
	{
		rt->ellipse = rt->start->ell;
		while (rt->ellipse != NULL)
		{
			if (rt->ellipse->pln != NULL)
				rt->ellipse->pln->cut = 0;
			if (type == 0)
				tmp = ft_check_ellipse(rt->ellipse, rt->ray);
			if (type == 1)
				tmp = ft_check_ellipse(rt->ellipse, rt->light_ray);
			if (type == 2 && rt->inter->num == rt->ellipse->id &&
			rt->inter->light == rt->ellipse->id)
				light_ellipse_inter(rt);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_ellipse_dst(rt, type, tmp);
			rt->ellipse = rt->ellipse->next;
		}
	}
}
