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

#include "../../rt.h"

t_coo		ft_new_vect(float x, float y, float z)
{
	t_coo		new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_coo		ft_normalize(t_coo vect)
{
	double		norm;
	t_coo		new;

	norm = ft_norme(vect);
	new = ft_div_vect(norm, vect);
	return (new);
}

double		ft_norme(t_coo vect)
{
	double	rslt;

	rslt = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
	return (rslt);
}

double		ft_dst(t_coo vect1, t_coo vect2)
{
	double		rslt;

	rslt = sqrt(pow(vect2.x - vect1.x, 2) +
	pow(vect2.y - vect1.y, 2) + pow(vect2.z - vect1.z, 2));
	return (rslt);
}

double		scal(t_coo v1, t_coo v2)
{
	double		rslt;

	rslt = (v1.x * v2.x) + v1.y * v2.y + v1.z * v2.z;
	return (rslt);
}
