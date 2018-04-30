/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_perlin3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:08:40 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/30 05:11:21 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_perlin	*ft_setup_i(t_perlin *l, double *vec, int i)
{
	double	t;

	t = vec[i] + N;
	l->b_tmp[i][0] = ((int)t) & BM;
	l->b_tmp[i][1] = (l->b_tmp[i][0] + 1) & BM;
	l->r[i][0] = t - (int)t;
	l->r[i][1] = l->r[i][0] - 1.;
	return (l);
}

t_perlin	*ft_setup(t_perlin *l, double *vec)
{
	l = ft_setup_i(l, vec, 0);
	l = ft_setup_i(l, vec, 1);
	l = ft_setup_i(l, vec, 2);
	return (l);
}

double		s_curve(double t)
{
	return (t * t * (3. - 2. * t));
}

double		at3(double rx, double ry, double rz, double *q)
{
	return ((rx * q[0] + ry * q[1] + rz * q[2]));
}

double		lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}
