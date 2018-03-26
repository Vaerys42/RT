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

double		disc_eq(double a, double b, double delta)
{
	double	ta;
	double	tb;

	ta = (-b - sqrt(fabs(delta))) / (2 * a);
	tb = (-b + sqrt(fabs(delta))) / (2 * a);
	if (ta > tb && tb > 0)
		return (tb);
	return (ta);
}

double		ft_check_cone(t_cone *cone, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		k;
	double		delta;

	k = pow(tan(cone->angle / 2), 2) + 1;
	ray->obj = ft_sub_vect(ray->o, cone->o);
	a = scal(ray->dir, ray->dir) - k * pow(scal(ray->dir, cone->dir), 2);
	b = (scal(ray->dir, ray->obj) - k * (scal(ray->dir, cone->dir) *
	scal(ray->obj, cone->dir))) * 2;
	c = scal(ray->obj, ray->obj) - k * pow(scal(ray->obj, cone->dir), 2);
	delta = b * b - (4 * a * c);
	if (a == 0)
		return (-c / b);
	else if (delta < - EPS)
		return (0);
	return (disc_eq(a, b, delta));
}

void		new_cone_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
	{
		rt->inter->obj = CON;
		rt->inter->mat->r = rt->cone->color->r * rt->light->amb;
		rt->inter->mat->g = rt->cone->color->g * rt->light->amb;
		rt->inter->mat->b = rt->cone->color->b * rt->light->amb;
	}
	if (type == 1 && rt->inter->obj == CON)
	{
		rt->light->shine = rt->cone->shine;
		rt->inter->angle->dir.x = rt->inter->point.x - rt->cone->o.x;
		rt->inter->angle->dir.y = rt->inter->point.y;
		rt->inter->angle->dir.z = rt->inter->point.z - rt->cone->o.z;
		rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
		rt->inter->mat->r *= 2;
		rt->inter->mat->g *= 2;
		rt->inter->mat->b *= 2;
	}
}

void		check_cone_inter(t_rt *rt, int type)
{
	double tmp;

	if (rt->start->con != NULL)
	{
		rt->cone = rt->start->con;
		while (rt->cone != NULL)
		{
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
