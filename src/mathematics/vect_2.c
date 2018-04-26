/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 00:22:11 by kboucaud          #+#    #+#             */
/*   Updated: 2018/02/26 00:22:12 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_coo		ft_mult_vect(double i, t_coo vect)
{
	t_coo		new;

	new = ft_new_vect(i * vect.x, i * vect.y, i * vect.z);
	return (new);
}

t_coo		ft_add_vect(t_coo vect1, t_coo vect2)
{
	t_coo		new;

	new = ft_new_vect(vect1.x + vect2.x, vect1.y + vect2.y, vect1.z + vect2.z);
	return (new);
}

t_coo		ft_sub_vect(t_coo vect1, t_coo vect2)
{
	t_coo		new;

	new = ft_new_vect(vect1.x - vect2.x, vect1.y - vect2.y, vect1.z - vect2.z);
	return (new);
}

t_coo		ft_div_vect(double i, t_coo vect)
{
	t_coo		new;

	if (i == 0)
		return (vect);
	new = ft_new_vect(vect.x / i, vect.y / i, vect.z / i);
	return (new);
}

t_coo		ft_det_vect(t_coo vect1, t_coo vect2)
{
	t_coo		new;

	new.x = vect1.y * vect2.z - vect1.z * vect2.y;
	new.y = -(vect1.x * vect2.z - vect1.z * vect2.x);
	new.z = vect1.x * vect2.y - vect1.y * vect2.x;
	return (new);
}
