/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parabol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:22:58 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/09 14:23:01 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double		ft_check_parabol(t_parabol *parabol, t_ray *ray)
{
	double		a;
	double		b;
	double		c;
	double		t1;
	double		t2;

	ray->obj = ft_sub_vect(ray->o, parabol->o);
	a = scal(ray->dir, ray->dir) - pow(scal(ray->dir, parabol->dir), 2);
	b = 2 * (scal(ray->dir, ray->obj) - scal(ray->dir, parabol->dir) *
	(scal(ray->obj, parabol->dir) + 2 * parabol->rad1));
	c = scal(ray->obj, ray->obj) - scal(ray->obj, parabol->dir) *
	(scal(ray->obj, parabol->dir) + 4 * parabol->rad1);
	t1 = (-b - sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	t2 = (-b + sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	if (b * b - (4 * a * c) < -EPS)
		return (0);
	if (parabol->pln == NULL)
		return (disc_eq(t1, t2));
	return (ft_inter_plane_ini(ray, parabol->pln, t1, t2));
}

void		cam_parabol_inter(t_rt *rt)
{
	rt->inter->obj = PAR;
	rt->inter->num = rt->parabol->id;
	rt->inter->col->r = rt->parabol->color->r;
	rt->inter->col->g = rt->parabol->color->g;
	rt->inter->col->b = rt->parabol->color->b;
	if (rt->parabol->pln != NULL && rt->parabol->pln->cut == 1)
	{
		rt->inter->col->r = rt->parabol->pln->color->r;
		rt->inter->col->g = rt->parabol->pln->color->g;
		rt->inter->col->b = rt->parabol->pln->color->b;
	}
}

void		light_parabol_inter(t_rt *rt)
{
	t_coo	obj;

	obj = ft_sub_vect(rt->inter->point, rt->parabol->o);
	rt->inter->angle->dir.x = 2 * obj.x / pow(rt->parabol->rad1, 2);
	rt->inter->angle->dir.y = 0;
	rt->inter->angle->dir.z = 2 * obj.z / pow(rt->parabol->rad2, 2);
	rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	if (rt->parabol->pln != NULL && rt->parabol->pln->cut == 1)
		rt->inter->angle->dir = rt->parabol->pln->norm;
}

void		new_parabol_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		cam_parabol_inter(rt);
	if (type == 1)
		rt->inter->light = rt->parabol->id;
}

void		check_parabol_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->par != NULL)
	{
		rt->parabol = rt->start->par;
		while (rt->parabol != NULL)
		{
			if (rt->parabol->pln != NULL)
				rt->parabol->pln->cut = 0;
			if (type == 0)
				tmp = ft_check_parabol(rt->parabol, rt->ray);
			if (type == 1)
				tmp = ft_check_parabol(rt->parabol, rt->light_ray);
			if (type == 2 && rt->inter->num == rt->parabol->id
			&& rt->inter->light == rt->parabol->id)
				light_parabol_inter(rt);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_parabol_dst(rt, type, tmp);
			rt->parabol = rt->parabol->next;
		}
	}
}
