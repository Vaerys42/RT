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

#include "../rt.h"

double		ft_inter_plane(t_ray *ray, t_cylinder *cylinder, double t1, double t2)
{
	double		dc;
	double		dw;
	double		t;
	
	dc = scal(ray->dir, cylinder->pln->norm);
	dw = scal(ft_sub_vect(ray->o, cylinder->pln->o), cylinder->pln->norm);
	if (dc == 0 && dw > 0)
		return (0);
	t = - dw / dc;
	if (dc >= 0)
	{
		if ( t > t1 && t < t2)
			t2 = t;
		if (t < t1)
			return (0);
	}
	else
	{
		if (t > t1 && t < t2)
			{
				cylinder->cut = 1;
				t1 = t;
			}
		if (t > t2)
			return (0);
	}
	if ( t1 > t2)
		return (0);
	return (t1);
}

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
	if (b * b - (4 * a * c) < - EPS)
		return (0);
	/*if (cylinder->pln == NULL)
		{
			if (t1 > t2 && t2 > 0)
				return (t2);
			return (t1);
		}*/
	return (ft_inter_plane(ray, cylinder, t1, t2));
}

void		new_cylinder_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
	{
		rt->inter->obj = CYL;
		rt->inter->mat->r = rt->cylinder->color->r * rt->light->amb;
		rt->inter->mat->g = rt->cylinder->color->g * rt->light->amb;
		rt->inter->mat->b = rt->cylinder->color->b * rt->light->amb;
		if (rt->cylinder->cut == 1 && rt->cylinder->pln != NULL)
		{
			rt->inter->mat->r = rt->cylinder->pln->color->r * rt->light->amb;
			rt->inter->mat->g = rt->cylinder->pln->color->g * rt->light->amb;
			rt->inter->mat->b = rt->cylinder->pln->color->b * rt->light->amb;
		}
	}
	if (type == 1 && rt->inter->obj == CYL)
	{
		rt->light->shine = rt->cylinder->shine;
		rt->inter->angle->dir.x = rt->inter->point.x -
		rt->cylinder->o.x;
		rt->inter->angle->dir.y = rt->inter->point.y;
		rt->inter->angle->dir.z = rt->inter->point.z -
		rt->cylinder->o.z;
		rt->inter->angle->dir = ft_rotation(rt->inter->angle->dir, rt->cylinder->rot);
		if (rt->cylinder->cut == 1)
			rt->inter->angle->dir = ft_mult_vect(-1, rt->cylinder->pln->norm);	
		rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
		rt->inter->mat->r *= 2;
		rt->inter->mat->g *= 2;
		rt->inter->mat->b *= 2;
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
			rt->cylinder->cut = 0;
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
