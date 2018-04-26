/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:00:38 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 21:05:31 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double				ft_check_cube(t_cube *cube, t_ray *ray)
{
	double		d;
	double		a;
	double		b;
	double		t;

	ray->obj = ft_sub_vect(ray->o, cube->a);
	d = -scal(ft_det_vect(cube->u, cube->v), ray->dir);
	a = -(scal(ft_det_vect(ray->obj, cube->v), ray->dir)) / d;
	b = -(scal(ft_det_vect(cube->u, ray->obj), ray->dir)) / d;
	t = scal(ft_det_vect(cube->u, cube->v), ray->obj) / d;
	if (a > 0 && b > 0 && a <= 1 && b <= 1)
		return (t);
	return (0);
}

void				new_cube_dst(t_rt *rt, int type, double tmp, int i)
{
	rt->inter->dst = tmp;
	if (type == 0)
	{
		rt->inter->obj = CUB;
		rt->inter->num = rt->cube->id;
		rt->inter->col->r = rt->cube->color->r;
		rt->inter->col->g = rt->cube->color->g;
		rt->inter->col->b = rt->cube->color->b;
		return ;
	}
	if (type == 1 && rt->inter->num == rt->cube->id && i == rt->cube->id)
	{
		rt->light->shine = rt->cube->shine;
		ft_norm_cube(rt, i);
	}
}

void				check_cube_inter(t_rt *rt, int type)
{
	double		tmp;
	int			i;

	rt->cube = rt->start->cub;
	while (rt->cube != NULL)
	{
		i = 0;
		while (i <= 6)
		{
			ft_angle_cube(rt->cube, i);
			ft_face_cube(rt->cube, i);
			if (type == 0)
				tmp = ft_check_cube(rt->cube, rt->ray);
			else
				tmp = ft_check_cube(rt->cube, rt->light_ray);
			if (tmp > 0.01 && tmp < rt->inter->dst)
			{
				if (type == 0)
					rt->cube->id = i;
				new_cube_dst(rt, type, tmp, i);
			}
			i++;
		}
		rt->cube = rt->cube->next;
	}
}
