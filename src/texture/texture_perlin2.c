/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_perlin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:08:49 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/30 05:20:53 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double		ft_texture_perlin(t_coo hit)
{
	double	n;
	double	vec[3];

	vec[0] = hit.x;
	vec[1] = hit.y;
	vec[2] = hit.z;
	n = ft_noise(vec);
	return (n);
}

double		ft_texture_marble(t_coo hit)
{
	double	n;
	double	vec[3];

	vec[0] = hit.x;
	vec[1] = hit.y;
	vec[2] = hit.z;
	n = sin(2 * M_PI * ft_noise(vec));
	return (n);
}

double		ft_texture_wood(t_coo hit)
{
	double	n;
	double	vec[3];
	double	v;

	vec[0] = hit.x;
	vec[1] = hit.y;
	vec[2] = hit.z;
	v = 20 * ft_noise(vec);
	n = v - (int)(v);
	return (n);
}
