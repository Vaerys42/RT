/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 22:57:06 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/25 22:57:08 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_equa3_next(t_rt *rt, t_equa_2 eq, double a, double b)
{
	rt->equa->u[0] = sqrt3((-eq.q + sqrt(-eq.delta / 27)) / 2);
	rt->equa->v[0] = sqrt3((-eq.q - sqrt(-eq.delta / 27)) / 2);
	rt->equa->u[1] = eq.j * sqrt3((-eq.q + sqrt(-eq.delta / 27)) / 2);
	rt->equa->v[1] = eq.j * sqrt3((-eq.q - sqrt(-eq.delta / 27)) / 2);
	rt->equa->u[2] = eq.j2 * sqrt3((-eq.q + sqrt(-eq.delta / 27)) / 2);
	rt->equa->v[2] = eq.j2 * sqrt3((-eq.q - sqrt(-eq.delta / 27)) / 2);
	rt->equa->x[0] = rt->equa->u[0] + rt->equa->v[0] - b / (3 * a);
	rt->equa->x[1] = rt->equa->u[1] + rt->equa->v[2] - b / (3 * a);
	rt->equa->x[2] = rt->equa->u[2] + rt->equa->v[1] - b / (3 * a);
}

t_equa_2	ini_equa_3(double a, double b, double c, double d)
{
	t_equa_2		eq;

	eq.p = c / a - (b * b) / (3 * a * a);
	eq.q = (b / (27 * a)) * ((2 * b * b) / (a * a) - (9 * c) / a) + d / a;
	eq.delta = -(27 * eq.q * eq.q + 4 * eq.p * eq.p * eq.p);
	eq.j = cexp(2 * I * M_PI / 3);
	eq.j2 = cexp(4 * I * M_PI / 3);
	eq.k = 0;
	return (eq);
}

void		pos_equa_3(t_rt *rt, t_equa_2 eq, double a, double b)
{
	rt->equa->x[0] = 2 * sqrt(-eq.p / 3) * cos(acos((3 * eq.q /
	(2 * eq.p)) * sqrt(-3 / eq.p)) / 3) - b / (3 * a);
	rt->equa->x[1] = 2 * sqrt(-eq.p / 3) * cos((acos((3 * eq.q /
	(2 * eq.p)) * sqrt(-3 / eq.p)) + 2 * M_PI) / 3) - b / (3 * a);
	rt->equa->x[2] = 2 * sqrt(-eq.p / 3) * cos((acos((3 * eq.q /
	(2 * eq.p)) * sqrt(-3 / eq.p)) + 4 * M_PI) / 3) - b / (3 * a);
}

void		ft_equa3(t_rt *rt, double a, t_coo data)
{
	t_equa_2		eq;

	eq = ini_equa_3(a, data.x, data.y, data.z);
	if (eq.p == 0 && eq.q == 0)
		rt->equa->x[0] = -data.x / (3 * a);
	else if (eq.p == 0 && eq.q != 0)
		rt->equa->x[0] = -eq.q;
	if (eq.delta < 0)
		ft_equa3_next(rt, eq, a, data.x);
	if (eq.delta == 0)
	{
		rt->equa->x[0] = 2 * sqrt3(-eq.q / 2) - data.x / (3 * a);
		rt->equa->x[1] = sqrt3(eq.q / 2) - data.x / (3 * a);
		rt->equa->x[2] = rt->equa->x[1];
	}
	if (eq.delta > 0)
		pos_equa_3(rt, eq, a, data.x);
}

double		ft_real(t_equa *equa)
{
	double		y;

	y = MAX;
	if (cimag(equa->x[0]) == 0)
		y = equa->x[0];
	else if (cimag(equa->x[1]) == 0)
		y = equa->x[1];
	else if (cimag(equa->x[2]) == 0)
		y = equa->x[2];
	else
	{
		equa->x[0] = MAX;
		equa->x[1] = MAX;
		equa->x[2] = MAX;
		equa->x[3] = MAX;
	}
	return (y);
}
