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

void		ft_brillance(t_rt *rt)
{
	t_coo		spec;

	spec = ft_normalize(ft_add_vect(rt->light_ray->dir, ft_mult_vect(-1 *
	scal(rt->light_ray->dir, rt->inter->angle->dir), rt->inter->angle->dir)));
	if (-scal(rt->light_ray->dir, rt->inter->angle->dir) < 0.01)
		return ;
	rt->inter->mat->r += rt->light->color->r * rt->light->shine *
	pow(scal(spec, ft_sub_vect(spec, rt->light_ray->dir)), 5);
	rt->inter->mat->g += rt->light->color->r * rt->light->shine *
	pow(scal(spec, ft_sub_vect(spec, rt->light_ray->dir)), 5);
	rt->inter->mat->b += rt->light->color->r * rt->light->shine *
	pow(scal(spec, ft_sub_vect(spec, rt->light_ray->dir)), 5);
}

void		ft_get_point(t_rt *rt)
{
	rt->inter->point = ft_mult_vect(rt->inter->dst, rt->ray->dir);
	rt->inter->point = ft_add_vect(rt->cam->pos, rt->inter->point);
}

void		ft_light_diffuse(t_rt *rt)
{
	double		angle;
	double		f;

	f = ft_dst(rt->light_ray->o, rt->inter->point);
	f = 1 / (1 + 1 * f + 1 * pow(f, 2));
	angle = -scal(rt->light_ray->dir, rt->inter->angle->dir);
	angle = (angle < 0.1) ? 0.1 : angle;
	rt->inter->mat->r += f * rt->light->color->r * angle * rt->light->power;
	rt->inter->mat->g += f * rt->light->color->g * angle * rt->light->power;
	rt->inter->mat->b += f * rt->light->color->b * angle * rt->light->power;
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
		check_sphere_inter(rt, 1);
		check_cone_inter(rt, 1);
		check_cylinder_inter(rt, 1);
		check_cube_inter(rt, 1);
		check_plane_inter(rt, 1);
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
