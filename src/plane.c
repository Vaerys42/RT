/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:00:38 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:00:41 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double				ft_check_plane(t_plane *plane, t_ray *ray)
{
	double		a;
	double		b;

	b = scal(plane->norm, ray->dir);
	if (b == 0)
		return (-1);
	a = scal(plane->norm, ray->o) + plane->supp;
	return (-a / b);
}

void				new_plane_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
	{
		rt->inter->obj = PLN;
		rt->inter->num = rt->plane->id;
		rt->inter->mat->r = rt->plane->color->r * rt->light->amb;
		rt->inter->mat->g = rt->plane->color->g * rt->light->amb;
		rt->inter->mat->b = rt->plane->color->b * rt->light->amb;
		return ;
	}
	if (type == 1 && rt->inter->obj == PLN && rt->inter->num == rt->plane->id)
	{
		rt->light->shine = 0;
		rt->inter->angle->dir = rt->plane->norm;
		rt->inter->mat->r *= 2;
		rt->inter->mat->g *= 2;
		rt->inter->mat->b *= 2;
	}
}

void				check_plane_inter(t_rt *rt, int type)
{
	double		tmp;

	if (rt->start->pln != NULL)
	{
		rt->plane = rt->start->pln;
		while (rt->plane != NULL)
		{
			if (type == 0)
				tmp = ft_check_plane(rt->plane, rt->ray);
			else
				tmp = ft_check_plane(rt->plane, rt->light_ray);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_plane_dst(rt, type, tmp);
			rt->plane = rt->plane->next;
		}
	}
}
