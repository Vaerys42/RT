/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 03:09:23 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/26 03:09:24 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_ini_equa4(t_rt *rt)
{
	rt->equa->a[0] = rt->equa->ini[0] / rt->equa->ini[0];
	rt->equa->a[1] = rt->equa->ini[1] / rt->equa->ini[0];
	rt->equa->a[2] = rt->equa->ini[2] / rt->equa->ini[0];
	rt->equa->a[3] = rt->equa->ini[3] / rt->equa->ini[0];
	rt->equa->a[4] = rt->equa->ini[4] / rt->equa->ini[0];
}

void		ft_equa4_next(t_rt *rt, _Complex double a0, double y, double b0)
{
	ft_equa2(rt->equa, 1, a0, y + b0);
	rt->equa->x[2] = rt->equa->x[0] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
	rt->equa->x[3] = rt->equa->x[1] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
	ft_equa2(rt->equa, 1, -a0, y - b0);
	rt->equa->x[0] = rt->equa->x[0] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
	rt->equa->x[1] = rt->equa->x[1] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
	if (cimag(rt->equa->x[0]) != 0)
		rt->equa->x[0] = MAX;
	if (cimag(rt->equa->x[1]) != 0)
		rt->equa->x[1] = MAX;
	if (cimag(rt->equa->x[2]) != 0)
		rt->equa->x[2] = MAX;
	if (cimag(rt->equa->x[3]) != 0)
		rt->equa->x[3] = MAX;
}

t_equa_3	equa4_mid(t_rt *rt)
{
	t_equa_3		eq;
	t_coo			data;

	eq.p = -3 * pow(rt->equa->a[1], 2) / (8 * pow(rt->equa->a[0], 2))
	+ rt->equa->a[2] / rt->equa->a[0];
	eq.q = pow(rt->equa->a[1] / 2, 3) / pow(rt->equa->a[0], 3) - (0.5 *
	rt->equa->a[1] * rt->equa->a[2]) / pow(rt->equa->a[0], 2) +
	rt->equa->a[3] / rt->equa->a[0];
	eq.r = -3 * pow((rt->equa->a[1] / 4) / rt->equa->a[0], 4) +
	rt->equa->a[2] * (pow(rt->equa->a[1] / 4, 2) / pow(rt->equa->a[0], 3)) -
	(rt->equa->a[1] * rt->equa->a[3] / 4) / pow(rt->equa->a[0], 2)
	+ rt->equa->a[4] / rt->equa->a[0];
	data.x = -4 * eq.p;
	data.y = -8 * eq.r;
	data.z = 4 * eq.r * eq.p - (eq.q * eq.q);
	ft_equa3(rt, 8, data);
	eq.y = ft_real(rt->equa);
	return (eq);
}

void		ft_equa4_1(t_rt *rt)
{
	t_coo		data;

	rt->equa->x[3] = 0;
	data.x = rt->equa->a[1];
	data.y = rt->equa->a[2];
	data.z = rt->equa->a[3];
	ft_equa3(rt, rt->equa->a[0], data);
}

void		ft_equa4(t_rt *rt)
{
	t_equa_3		eq;

	ft_ini_equa4(rt);
	if (rt->equa->a[0] == 0)
		ft_equa4_1(rt);
	else
	{
		eq = equa4_mid(rt);
		if (eq.y == MAX)
			return ;
		if (-eq.p + 2 * eq.y > 0)
			eq.a0 = sqrt(-eq.p + 2 * eq.y);
		else
			eq.a0 = I * sqrt(eq.p - 2 * eq.y);
		if (2 * eq.y - eq.p == 0)
			eq.b0 = sqrt(eq.y * eq.y - eq.r);
		else
			eq.b0 = -eq.q / (2 * eq.a0);
		ft_equa4_next(rt, eq.a0, eq.y, eq.b0);
	}
}
