/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:51:42 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 20:51:43 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

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

void				ft_face_cube_2(t_cube *cube, int i, t_coo k, t_coo l)
{
	if (i == 4 || i == 5)
		cube->v = ft_mult_vect(-1, k);
	if (i == 6)
		cube->v = ft_mult_vect(-1, l);
	if (i == 5)
		cube->u = ft_mult_vect(-1, l);
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
	ft_face_cube_2(cube, i, k, l);
}

void				ft_norm_cube(t_rt *rt, int i)
{
	rt->inter->angle->dir = ft_new_vect(0, 0, 0);
	if (i == 1)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, 0, 1),
	rt->cube->rot);
	else if (i == 2)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(1, 0, 0),
	rt->cube->rot);
	else if (i == 3)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, -1, 0),
	rt->cube->rot);
	else if (i == 4)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, 0, -1),
	rt->cube->rot);
	else if (i == 5)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(-1, 0, 0),
	rt->cube->rot);
	else if (i == 6)
		rt->inter->angle->dir = ft_rotation(ft_new_vect(0, 1, 0),
	rt->cube->rot);
}
