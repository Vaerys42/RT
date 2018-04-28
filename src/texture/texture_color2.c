/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:45:33 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 16:30:35 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double			ft_texture_waves(t_coo hit)
{
	double		n;

	n = sin(hit.y * 20 + sin(hit.x * 5) * 2);
	return (n);
}

int				ft_texture_square(t_coo hit, t_rt *rt)
{
	t_coo		point_2d;
	double		u;
	double		v;
	int			u2;
	int			v2;

	point_2d = ft_mapping_all(hit, rt);
	u = point_2d.x;
	v = point_2d.y;
	u2 = floor(u * 10);
	v2 = floor(v * 10);
	if (u2 % 2 == 0 && v2 % 2 == 0)
		return (1);
	return (0);
}

int				ft_texture_sparkle(void)
{
	double		n;

	n = -rand() / (double)(RAND_MAX + 1);
	if (n < 0.4)
		return (1);
	return (0);
}
