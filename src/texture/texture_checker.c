/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 17:14:52 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 17:27:08 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int			ft_texture_checker_2(t_coo p, int c1, int c2)
{
	int		px;
	int		py;
	int		pz;

	px = (int)p.x;
	py = (int)p.y;
	pz = (int)p.z;
	if (pz % 2 == 0)
	{
		if ((px % 2 == 0 && py % 2 == 0) || (px % 2 != 0 && py % 2 != 0))
		{
			return (c1);
		}
		else
			return (c2);
	}
	else
	{
		if ((px % 2 == 0 && py % 2 == 0) || (px % 2 != 0 && py % 2 != 0))
			return (c2);
		else
			return (c1);
	}
	return (2);
}

int			ft_texture_checker(double l, t_coo hit)
{
	t_coo	p;
	int		tmp;

	p.x = (int)(hit.x / l);
	p.y = (int)(hit.y / l);
	p.z = (int)(hit.z / l);
	if (hit.y >= 0)
	{
		if (hit.x >= 0)
			tmp = ft_texture_checker_2(p, 1, 0);
		else
			tmp = ft_texture_checker_2(p, 0, 1);
	}
	else
	{
		if (hit.x >= 0)
			tmp = ft_texture_checker_2(p, 0, 1);
		else
			tmp = ft_texture_checker_2(p, 1, 0);
	}
	return (tmp);
}
