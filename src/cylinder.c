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

#include "../rtv1.h"

double		ft_check_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;

	ray->obj = ft_sub_vect(ray->o, cylinder->o);
	a = scal(ray->dir, ray->dir) - pow(scal(ray->dir, cylinder->dir), 2);
	b = 2 * (scal(ray->dir, ray->obj) - (scal(ray->dir, cylinder->dir) *
	scal(ray->obj, cylinder->dir)));
	c = scal(ray->obj, ray->obj) - pow(scal(ray->obj, cylinder->dir), 2) -
	pow(cylinder->radius, 2);
	delta = b * b - (4 * a * c);
	if (delta < -0.0001)
		return (0);
	return (disc_eq(a, b, delta));
}

void		new_cylinder_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		rt->inter->obj = CYL;
	if (type == 1 && rt->inter->obj == CYL)
	{
		rt->inter->mat->r += rt->cylinder->color->r;
		rt->inter->mat->g += rt->cylinder->color->g;
		rt->inter->mat->b += rt->cylinder->color->b;
		rt->light->shine = rt->cylinder->shine;
		rt->inter->angle->dir.x = rt->inter->point.x -
		rt->cylinder->o.x;
		rt->inter->angle->dir.y = rt->inter->point.y;
		rt->inter->angle->dir.z = rt->inter->point.z -
		rt->cylinder->o.z;
		rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	}
}

void		check_cylinder_inter(t_rt *rt, int type)
{
	double tmp;

	if (rt->start->cyl != NULL)
	{
		rt->cylinder = rt->start->cyl;
		while (rt->cylinder != NULL)
		{
			if (type == 0)
				tmp = ft_check_cylinder(rt->cylinder, rt->ray);
			else
				tmp = ft_check_cylinder(rt->cylinder, rt->light_ray);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_cylinder_dst(rt, type, tmp);
			rt->cylinder = rt->cylinder->next;
		}
	}
}
