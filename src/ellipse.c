/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:01:32 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:01:34 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double		ft_check_ellipse(t_ellipse *ellipse, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	
	ray->obj = ft_sub_vect(ray->o, ellipse->o);
	a = pow(ray->dir.x / ellipse->rad1.x, 2)+ pow(ray->dir.y / ellipse->rad2.y, 2) + pow(ray->dir.z / ellipse->rad3.z, 2);
	b = 2 * (ray->dir.x * ray->obj.x * pow(1 / ellipse->rad1.x, 2) + ray->dir.y * ray->obj.y * pow(1 / ellipse->rad2.y, 2) + ray->dir.z * ray->obj.z * pow(1 / ellipse->rad3.z, 2));
	c = pow(ray->obj.x / ellipse->rad1.x, 2) + pow(ray->obj.y / ellipse->rad2.y, 2) + pow(ray->obj.z / ellipse->rad3.z, 2) - 1;
	delta = b * b - (4 * a * c);
	if (ellipse->obj->pln == NULL)
        return (disc_eq(a, b, c, delta));
	return (ft_inter_plane_ini(ray, ellipse->obj, a, b, c));
}

void		new_ellipse_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
	{
		rt->inter->obj = ELL;
		rt->inter->mat->r = rt->ellipse->color->r * rt->light->amb;
		rt->inter->mat->g = rt->ellipse->color->g * rt->light->amb;
		rt->inter->mat->b = rt->ellipse->color->b * rt->light->amb;
		if (rt->ellipse->obj->cut == 1 && rt->ellipse->obj->pln != NULL)
		{
			rt->inter->mat->r = rt->ellipse->obj->pln->color->r * rt->light->amb;
			rt->inter->mat->g = rt->ellipse->obj->pln->color->g * rt->light->amb;
			rt->inter->mat->b = rt->ellipse->obj->pln->color->b * rt->light->amb;
		}
	}
	if (type == 1 && rt->inter->obj == ELL)
	{
		rt->light->shine = rt->ellipse->shine;
		rt->inter->angle->o = ft_sub_vect(rt->inter->point,
		rt->ellipse->o);
		rt->inter->angle->dir = ft_rotation(rt->inter->angle->dir, rt->ellipse->rot);
		if (rt->ellipse->obj->cut == 1)
			rt->inter->angle->dir = ft_mult_vect(-1, rt->ellipse->obj->pln->norm);	
		rt->inter->angle->dir = ft_normalize(rt->inter->angle->o);
		rt->inter->mat->r *= 2;
		rt->inter->mat->g *= 2;
		rt->inter->mat->b *= 2;
	}
}

void		check_ellipse_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->ell != NULL)
	{
		rt->ellipse = rt->start->ell;
		while (rt->ellipse != NULL)
		{
			rt->ellipse->obj->cut = 0;
			if (type == 0)
				tmp = ft_check_ellipse(rt->ellipse, rt->ray);
			else
				tmp = ft_check_ellipse(rt->ellipse, rt->light_ray);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_ellipse_dst(rt, type, tmp);
			rt->ellipse = rt->ellipse->next;
		}
	}
}
