/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:00:38 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/09 14:44:30 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void				ft_angle_cube(t_cube *cube, int i)
{
	t_coo		dirx;
	t_coo		diry;
	t_coo		dirz;

	dirx = ft_rotation(ft_new_vect(1, 0, 0), cube->rot);
	diry = ft_rotation(ft_new_vect(0, 1, 0), cube->rot);
	dirz = ft_rotation(ft_new_vect(0, 0, 1), cube->rot);
	if (i == 4 || i == 5 || i == 6)
	{
		cube->a = ft_add_vect(cube->o, ft_mult_vect(-cube->radius, dirx));
		cube->a = ft_add_vect(cube->a, ft_mult_vect(cube->radius, diry));
		cube->a = ft_add_vect(cube->a, ft_mult_vect(-cube->radius, dirz));
	}
	if (i == 1 || i == 2 || i == 3)
	{
		cube->a = ft_add_vect(cube->o, ft_mult_vect(cube->radius, dirx));
		cube->a = ft_add_vect(cube->a, ft_mult_vect(-cube->radius, diry));
		cube->a = ft_add_vect(cube->a, ft_mult_vect(cube->radius, dirz));
	}
}

void				ft_face_cube(t_cube *cube, int i)
{
	t_coo	j;
	t_coo	k;
	t_coo	l;
	t_coo	rotz;
	t_coo	rotx;

	rotx = ft_new_vect(0, 0, 90);
	rotz = ft_new_vect(90, 0, 0);
	j = ft_rotation(ft_mult_vect(cube->radius * 2, cube->dir), rotx);
	k = ft_mult_vect(cube->radius * 2, cube->dir);
	l = ft_rotation(ft_mult_vect(cube->radius * 2, cube->dir), rotz);
	j = ft_rotation(j, cube->rot);
	k = ft_rotation(k, cube->rot);
	l = ft_rotation(l, cube->rot);
	if (i == 1 || i == 2)
		cube->u = k;
	if (i == 1 || i == 3)
		cube->v = ft_mult_vect(-1, j);
	if (i == 2)
		cube->v = l;
	if (i == 3)
		cube->u = l;
	if (i == 4 || i == 6)
		cube->u = j;
	if (i == 4 || i == 5)
		cube->v = ft_mult_vect(-1, k);
	if (i == 6)
		cube->v = ft_mult_vect(-1, l);
	if (i == 5)
		cube->u = ft_mult_vect(-1, l);
}

void				ft_norm_cube(t_rt *rt, int i)
{
	rt->inter->angle->dir = ft_new_vect(0, 0, 0);
	if (i == 1)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, 0, 1),
	rt->cube->rot);
	if (i == 2)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(1, 0, 0),
	rt->cube->rot);
	if (i == 3)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, -1, 0),
	rt->cube->rot);
	if (i == 4)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, 0, -1),
	rt->cube->rot);
	if (i == 5)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(-1, 0, 0),
	rt->cube->rot);
	if (i == 6)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, 1, 0),
	rt->cube->rot);
}

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
		rt->inter->num = rt->cube->obj;
		rt->inter->mat->r = rt->cube->color->r * rt->light->amb;
		rt->inter->mat->g = rt->cube->color->g * rt->light->amb;
		rt->inter->mat->b = rt->cube->color->b * rt->light->amb;
		return ;
	}
	if (type == 1 && rt->inter->obj == CUB && i == rt->cube->obj)
	{
		rt->light->shine = rt->cube->shine;
		ft_norm_cube(rt, i);
		rt->inter->mat->r *= 2;
		rt->inter->mat->g *= 2;
		rt->inter->mat->b *= 2;
	}
}

void				check_cube_inter(t_rt *rt, int type)
{
	double		tmp;
	int			i;

	if (rt->start->cub != NULL)
	{
		rt->cube = rt->start->cub;
		while (rt->cube != NULL)
		{
			i = 1;
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
						rt->cube->obj = i;
					new_cube_dst(rt, type, tmp, i);
				}
				i++;
			}
			rt->cube = rt->cube->next;
		}
	}
}
