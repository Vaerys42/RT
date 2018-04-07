/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 03:32:16 by kboucaud          #+#    #+#             */
/*   Updated: 2017/12/04 03:32:18 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		make_rot(t_rt *rt)
{
	rt->cylinder = rt->start->cyl;
	while (rt->cylinder != NULL)
	{
		rt->cylinder->dir = ft_rotation(rt->cylinder->dir, rt->cylinder->rot);
		if (rt->cylinder->obj->pln != NULL)
			rt->cylinder->obj->pln->norm = ft_rotation(rt->cylinder->obj->pln->norm, rt->cylinder->rot);
		rt->cylinder = rt->cylinder->next;
	}
	rt->cone = rt->start->con;
	while (rt->cone != NULL)
	{
		rt->cone->dir = ft_rotation(rt->cone->dir, rt->cone->rot);
		rt->cone->obj->pln->norm = ft_rotation(rt->cone->obj->pln->norm, rt->cone->rot);
		rt->cone = rt->cone->next;
	}
	while (rt->sphere != NULL)
	{
		rt->sphere->obj->pln->norm = ft_add_vect(rt->sphere->obj->pln->norm,rt->sphere->dir);
		rt->sphere->obj->pln->norm = ft_rotation(rt->sphere->obj->pln->norm, rt->sphere->rot);
		rt->sphere = rt->sphere->next;
	}
	while (rt->ellipse != NULL)
	{
		rt->ellipse->rad1 = ft_rotation(rt->ellipse->rad1,rt->ellipse->rot);
		rt->ellipse->rad2 = ft_rotation(rt->ellipse->rad2,rt->ellipse->rot);
		rt->ellipse->rad3 = ft_rotation(rt->ellipse->rad3,rt->ellipse->rot);
		rt->ellipse->obj->pln->norm = ft_rotation(rt->ellipse->obj->pln->norm, rt->ellipse->rot);
		rt->ellipse = rt->ellipse->next;
	}
}

t_coo		ft_rotation_2(t_coo vect, t_coo rot)
{
	t_coo	new;

	if (rot.x != 0)
	{
		new.x = vect.x;
		new.y = vect.y * cos(rot.x) + vect.z * sin(rot.x);
		new.z = -vect.y * sin(rot.x) + vect.z * cos(rot.x);
		vect = new;
	}
	if (rot.y != 0)
	{
		new.x = vect.x * cos(rot.y) - vect.z * sin(rot.y);
		new.y = vect.y;
		new.z = vect.x * sin(rot.y) + vect.z * cos(rot.y);
		vect = new;
	}
	if (rot.z != 0)
	{
		new.x = vect.x * cos(rot.z) + vect.y * sin(rot.z);
		new.y = -vect.x * sin(rot.z) + vect.y * cos(rot.z);
		new.z = vect.z;
	}
	return (new);
}

t_coo		ft_rotation(t_coo vect, t_coo rot)
{
	if (rot.x == 0 && rot.y == 0 && rot.z == 0)
		return (vect);
	rot = ft_mult_vect(M_PI / 180, rot);
	return (ft_rotation_2(vect, rot));
}
