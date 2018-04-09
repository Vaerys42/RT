/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 00:31:27 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 18:38:18 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		ft_check_expose(t_material *mat, double max)
{
	if (mat->r > max)
		mat->r = max;
	if (mat->b > max)
		mat->b = max;
	if (mat->g > max)
		mat->g = max;
}

void		ft_brillance(t_rt *rt)
{
	t_coo		spec;
	double		angle;

	rt->light = rt->start->lgh;
	while (rt->light)
	{
		rt->light_ray->dir = ft_normalize(ft_sub_vect(rt->inter->point,
		rt->light->o));
		angle = -scal(rt->light_ray->dir, rt->inter->angle->dir);
		angle = (angle < 0.01) ? 0.01 : angle;
		spec = ft_normalize(ft_add_vect(rt->light_ray->dir,
		ft_mult_vect(angle, rt->inter->angle->dir)));
		rt->inter->mat->r += rt->light->shine *
		pow(scal(spec, ft_sub_vect(spec, rt->light_ray->dir)), 2);
		rt->inter->mat->g += rt->light->shine *
		pow(scal(spec, ft_sub_vect(spec, rt->light_ray->dir)), 2);
		rt->inter->mat->b += rt->light->shine *
		pow(scal(spec, ft_sub_vect(spec, rt->light_ray->dir)), 2);
		rt->light = rt->light->next;
	}
}

void		ft_get_point(t_rt *rt)
{
	rt->inter->point = ft_mult_vect(rt->inter->dst, rt->ray->dir);
	rt->inter->point = ft_add_vect(rt->cam->pos, rt->inter->point);
}

void		ft_light_diffuse(t_rt *rt)
{
	double		angle;

	rt->light = rt->start->lgh;
	while (rt->light)
	{
		rt->light_ray->dir = ft_normalize(ft_sub_vect(rt->inter->point,
		rt->light->o));
		angle = -scal(rt->light_ray->dir, rt->inter->angle->dir);
		angle = (angle < 0.01) ? 0.01 : angle;
		rt->inter->mat->r += rt->light->color->r * angle * rt->light->power;
		rt->inter->mat->g += rt->light->color->g * angle * rt->light->power;
		rt->inter->mat->b += rt->light->color->b * angle * rt->light->power;
		ft_check_expose(rt->inter->mat, 1.0);
		rt->light = rt->light->next;
	}
}

void		check_forms(t_rt *rt, int type)
{
	check_sphere_inter(rt, type);
	check_cone_inter(rt, type);
	check_cylinder_inter(rt, type);
	check_cube_inter(rt, type);
	check_ellipse_inter(rt, type);
	check_plane_inter(rt, type);
}

void		ft_get_light(t_rt *rt)
{
	rt->light = rt->start->lgh;
	while (rt->light)
	{
		rt->inter->dst = MAX;
		rt->light_ray->o = rt->light->o;
		rt->light_ray->dir = ft_normalize(ft_sub_vect(rt->inter->point,
		rt->light->o));
		rt->light->shine = 0;
		check_forms(rt, 1);
		rt->light = rt->light->next;
	}
	ft_light_diffuse(rt);
	ft_brillance(rt);
}

void		ft_check_object(t_rt *rt)
{
	rt->inter->dst = MAX;
	rt->inter->obj = 0;
	rt->inter->angle->dir = rt->ray->dir;
	rt->inter->mat->r = 0;
	rt->inter->mat->g = 0;
	rt->inter->mat->b = 0;
	rt->light = rt->start->lgh;
	check_forms(rt, 0);
	if (rt->inter->dst <= 0.01)
		rt->inter->dst = 0;
	if (rt->inter->dst != 0)
	{
		ft_get_point(rt);
		ft_get_light(rt);
	}
	return ;
}
