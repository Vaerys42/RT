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

void		ft_check_expose(t_rt *rt)
{
	double	max;

	max = 1.0;
	if (rt->inter->mat->r > max)
		max = rt->inter->mat->r;
	if (rt->inter->mat->b > max)
		max = rt->inter->mat->b;
	if (rt->inter->mat->g > max)
		max = rt->inter->mat->g;
	rt->inter->mat->r = rt->inter->mat->r / max;
	rt->inter->mat->g = rt->inter->mat->g / max;
	rt->inter->mat->b = rt->inter->mat->b / max;
}

void		ft_brillance(t_rt *rt)
{
	t_coo		spec;

	spec = ft_mult_vect(2 * scal(rt->ray->dir, rt->inter->angle->dir), 
	rt->inter->angle->dir);
	spec = ft_normalize(ft_sub_vect(spec, rt->ray->dir));
	if (-scal(spec, ft_mult_vect(-1, rt->light_ray->dir)) < 0.01)
		return ;
	rt->inter->mat->r += rt->light->color->r * rt->light->shine *
	pow(-scal(spec, ft_mult_vect(-1, rt->light_ray->dir)), 5);
	rt->inter->mat->g += rt->light->color->r * rt->light->shine *
	pow(-scal(spec, ft_mult_vect(-1, rt->light_ray->dir)), 5);
	rt->inter->mat->b += rt->light->color->r * rt->light->shine *
	pow(-scal(spec, ft_mult_vect(-1, rt->light_ray->dir)), 5);
}

void		ft_get_point(t_rt *rt)
{
	rt->inter->point = ft_mult_vect(rt->inter->dst, rt->ray->dir);
	rt->inter->point = ft_add_vect(rt->cam->pos, rt->inter->point);
}

void		ft_light_diffuse(t_rt *rt)
{
	double		angle;

	angle = -scal(rt->light_ray->dir, rt->inter->angle->dir);
	angle = (angle < 0.1) ? 0.1 : angle;
	if (rt->inter->mat->r > 0)
		rt->inter->mat->r += rt->light->color->r * angle * rt->light->power;
	if (rt->inter->mat->g > 0)
		rt->inter->mat->g += rt->light->color->g * angle * rt->light->power;
	if (rt->inter->mat->b > 0)
		rt->inter->mat->b += rt->light->color->b * angle * rt->light->power;	
	ft_check_expose(rt);
}

void		ft_get_light(t_rt *rt)
{
	rt->light = rt->start->lgh;
	while (rt->light)
	{
		rt->inter->dst = 99999;
		rt->light_ray->o = rt->light->o;
		rt->light_ray->dir = ft_normalize(ft_sub_vect(rt->inter->point,
		rt->light->o));
		rt->light->shine = 0;
		check_sphere_inter(rt, 1);
		check_cone_inter(rt, 1);
		check_cylinder_inter(rt, 1);
		check_cube_inter(rt, 1);
		check_plane_inter(rt, 1);
		rt->light = rt->light->next;
	}
	rt->light = rt->start->lgh;
	while (rt->light)
	{
		ft_light_diffuse(rt);
		ft_brillance(rt);
		rt->light = rt->light->next;
	}
}

void		ft_check_object(t_rt *rt)
{
	int		i;

	i = 0;
	rt->inter->dst = 99999;
	rt->inter->obj = 0;
	rt->inter->angle->dir = rt->ray->dir;
	rt->inter->mat->r = 0;
	rt->inter->mat->g = 0;
	rt->inter->mat->b = 0;
	rt->light = rt->start->lgh;
	check_sphere_inter(rt, 0);
	check_cone_inter(rt, 0);
	check_cylinder_inter(rt, 0);
	check_cube_inter(rt, 0);
	check_plane_inter(rt, 0);
	if (rt->inter->dst <= 0.01)
		rt->inter->dst = 0;
	if (rt->inter->dst != 0)
	{
		ft_get_point(rt);
		ft_get_light(rt);
	}
	return ;
}
