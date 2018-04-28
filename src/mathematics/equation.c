/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:21:20 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 19:50:58 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double		sqrt3(double a)
{
	if (a < 0)
		return (-pow(-a, 1.0 / 3));
	return (pow(a, 1.0 / 3));
}

double		disc_eq(double t1, double t2)
{
	if ((t1 > t2 && t2 > 0) || (t2 > t1 && t1 < 0))
		return (t2);
	return (t1);
}

double		ft_inter_plane_obj(t_plane *pln, double dc, t_coo data)
{
	if (dc >= 0)
	{
		if (data.x > data.y && data.x < data.z)
			data.z = data.x;
		if (data.x < data.y)
			return (0);
	}
	else
	{
		if (data.x > data.y && data.x < data.z)
		{
			pln->cut = 1;
			data.y = data.x;
		}
		if (data.x > data.z)
			return (0);
	}
	if (data.y > data.z)
		return (0);
	return (data.y);
}

double		ft_inter_plane_ini(t_ray *ray, t_plane *pln, double t1, double t2)
{
	t_coo		data;
	double		dc;
	double		dw;

	dc = scal(ray->dir, pln->norm);
	dw = scal(ft_sub_vect(ray->o, pln->o), pln->norm);
	data.x = -dw / dc;
	data.y = t1;
	data.z = t2;
	if (dc == 0 && dw > 0)
		return (0);
	return (ft_inter_plane_obj(pln, dc, data));
}

void		ft_equa2(t_equa *equa, double a, double b, double c)
{
	double		delta;

	delta = b * b - (4 * a * c);
	if (a == 0)
	{
		equa->x[0] = -c / b;
	}
	if (delta == 0)
	{
		equa->x[0] = -b / (2 * a);
	}
	if (delta > 0)
	{
		equa->x[0] = (-b - sqrt(delta)) / (2 * a);
		equa->x[1] = (-b + sqrt(delta)) / (2 * a);
	}
	if (delta < 0)
	{
		equa->x[0] = (-b - I * sqrt(-delta)) / (2 * a);
		equa->x[1] = (-b + I * sqrt(-delta)) / (2 * a);
	}
}
