/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:01:32 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 18:08:26 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		cam_tore_inter(t_rt *rt)
{
	rt->inter->obj = TOR;
	rt->inter->num = rt->tore->id;
	rt->inter->col->r = rt->tore->color->r;
	rt->inter->col->g = rt->tore->color->g;
	rt->inter->col->b = rt->tore->color->b;
	if (rt->tore->pln != NULL && rt->tore->pln->cut == 1)
	{
		rt->inter->col->r = rt->tore->pln->color->r;
		rt->inter->col->g = rt->tore->pln->color->g;
		rt->inter->col->b = rt->tore->pln->color->b;
	}
}

void		light_tore_inter(t_rt *rt)
{
	t_coo	obj;

	rt->light->shine = rt->tore->shine;
	obj = ft_sub_vect(rt->inter->point, rt->tore->o);
	rt->ray->obj = ft_sub_vect(rt->ray->o, rt->tore->o);
	rt->inter->angle->dir.x = 4 * obj.x * (scal(obj, obj) +
			pow(rt->tore->radiusb, 2) - pow(rt->tore->radiusa, 2)) - 8 *
		pow(rt->tore->radiusb, 2) * obj.x;
	rt->inter->angle->dir.y = 4 * obj.y * (scal(obj, obj) +
			pow(rt->tore->radiusb, 2) - pow(rt->tore->radiusa, 2)) - 8 *
		pow(rt->tore->radiusb, 2) * obj.y;
	rt->inter->angle->dir.z = 4 * obj.z * (scal(obj, obj) +
			pow(rt->tore->radiusb, 2) - pow(rt->tore->radiusa, 2));
	if (rt->tore->pln != NULL && rt->tore->pln->cut == 1)
		rt->inter->angle->dir = rt->tore->pln->norm;
}

void		new_tore_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		cam_tore_inter(rt);
	if (type == 1)
		rt->inter->light = rt->tore->id;
}

void		check_tore_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->tor != NULL)
	{
		rt->tore = rt->start->tor;
		while (rt->tore != NULL)
		{
			if (rt->tore->pln != NULL)
				rt->tore->pln->cut = 0;
			if (type == 0)
				tmp = ft_check_tore(rt, rt->ray);
			if (type == 1)
				tmp = ft_check_tore(rt, rt->light_ray);
			if (type == 2 && rt->inter->num == rt->tore->id &&
			rt->inter->light == rt->tore->id)
				light_tore_inter(rt);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_tore_dst(rt, type, tmp);
			rt->tore = rt->tore->next;
		}
	}
}
