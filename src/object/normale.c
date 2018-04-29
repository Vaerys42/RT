/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 19:29:21 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/29 19:29:25 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		norm_cylinder(t_rt *rt)
{
	t_coo		norm;
	t_coo		op;
	double		a;
	double		b;
	double		c;

	op = ft_sub_vect(rt->inter->point, rt->cylinder->o);
	a = rt->cylinder->dir.y * op.z - rt->cylinder->dir.z * op.y;
	b = rt->cylinder->dir.z * op.x - rt->cylinder->dir.x * op.z;
	c = rt->cylinder->dir.x * op.y - rt->cylinder->dir.y * op.x;
	norm = ft_new_vect(a, b, c);
	rt->inter->angle->dir = ft_det_vect(norm, rt->cylinder->dir);
	if (rt->cylinder->pln != NULL && rt->cylinder->pln->cut == 1)
		rt->inter->angle->dir = rt->cylinder->pln->norm;
}

void		get_norm_cone(t_rt *rt)
{
	t_coo		norm;
	t_coo		op;
	double		a;
	double		b;
	double		c;

	op = ft_sub_vect(rt->inter->point, rt->cone->o);
	a = rt->cone->dir.y * op.z - rt->cone->dir.z * op.y;
	b = rt->cone->dir.z * op.x - rt->cone->dir.x * op.z;
	c = rt->cone->dir.x * op.y - rt->cone->dir.y * op.x;
	norm = ft_new_vect(a, b, c);
	rt->inter->angle->dir = ft_det_vect(norm, op);
	if (rt->cone->pln != NULL && rt->cone->pln->cut == 1)
		rt->inter->angle->dir = rt->cone->pln->norm;
}
