/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:21:20 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/09 14:21:23 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double		disc_eq(double a, double b, double c, double delta)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	t2 = (-b + sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	//printf("delta %f\n", delta);
	if (delta < - EPS)
		return (0);
	if (t1 > t2 && t2 > 0)
		return (t2);
	return (t1);
}

double		ft_inter_plane_obj(t_plane *pln, double dc, double t, double t1, double t2)
{
	if (dc >= 0)
	{
		if (t > t1 && t < t2)
			t2 = t;
		if (t < t1)
			return (0);
	}
	else
	{
		if (t > t1 && t < t2)
		{
			pln->cut = 1;
			t1 = t;
		}
		if (t > t2)
			return (0);
	}
	if (t1 > t2)
		return (0);
	return (t1);
}

double		ft_inter_plane_ini(t_ray *ray, t_plane *pln, double a, double b, double c)
{
	double		t;
	double		t1;
	double		t2;
	double		dc;
	double		dw;

	t1 = (-b - sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	t2 = (-b + sqrt(fabs(b * b - (4 * a * c)))) / (2 * a);
	if (b * b - (4 * a * c) < -EPS)
		return (0);
	dc = scal(ray->dir, pln->norm);
	dw = scal(ft_sub_vect(ray->o, pln->o), pln->norm);
	t = -dw / dc;
	if (dc == 0 && dw > 0)
		return (0);
	return (ft_inter_plane_obj(pln, dc, t, t1, t2));
}
