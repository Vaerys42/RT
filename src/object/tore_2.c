/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 21:28:24 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 21:28:27 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

double		ft_min(t_rt *rt, t_equa *equa)
{
	double		t[4];
	double		t1;
	double		t2;
	int			k;
	int			i;

	k = 0;
	i = 0;
	t[0] = MAX;
	t[1] = MAX;
	while (k < 4)
	{
		if (cimag(equa->x[k]) == 0 && creal(equa->x[k])
		< MAX && creal(equa->x[k]) > 0.1)
			t[i++] = creal(equa->x[k]);
		k++;
	}
	t1 = t[0];
	t2 = t[1];
	if (rt->tore->pln == NULL)
		return (disc_eq(t1, t2));
	return (ft_inter_plane_ini(rt->ray, rt->tore->pln, t1, t2));
}

void		ft_tore_det(t_tore *tore, t_equa *equa, t_ray *ray)
{
	ray->obj = ft_sub_vect(ray->o, tore->o);
	equa->ini[0] = pow(scal(ray->dir, ray->dir), 2);
	equa->ini[1] = 4 * scal(ray->dir, ray->dir) * scal(ray->dir, ray->obj);
	equa->ini[2] = 4 * pow(scal(ray->dir, ray->obj), 2) + 2 * scal(ray->dir,
	ray->dir) * (scal(ray->obj, ray->obj) - pow(tore->radiusb, 2) -
	pow(tore->radiusa, 2)) + 4 * pow(tore->radiusb, 2) *
	pow(scal(ray->dir, tore->dir), 2);
	equa->ini[3] = 4 * scal(ray->dir, ray->obj) * (scal(ray->obj, ray->obj) -
	pow(tore->radiusb, 2) - pow(tore->radiusa, 2)) + 8 * pow(tore->radiusb, 2)
	* scal(ray->dir, tore->dir) * scal(ray->obj, tore->dir);
	equa->ini[4] = pow(scal(ray->obj, ray->obj) - pow(tore->radiusb, 2) -
	pow(tore->radiusa, 2), 2) + 4 * pow(tore->radiusb, 2) * pow(scal(ray->obj,
	tore->dir), 2) - 4 * pow(tore->radiusb, 2) * pow(tore->radiusa, 2);
}

double		ft_check_tore(t_rt *rt, t_ray *ray)
{
	t_coo		data;

	ft_tore_det(rt->tore, rt->equa, ray);
	if (rt->equa->ini[4] == 0 && rt->equa->ini[3] == 0)
	{
		ft_equa2(rt->equa, rt->equa->ini[0],
		rt->equa->ini[1], rt->equa->ini[2]);
		return (ft_min(rt, rt->equa));
	}
	if (rt->equa->ini[4] == 0 && rt->equa->ini[3] != 0)
	{
		data.x = rt->equa->ini[1];
		data.y = rt->equa->ini[2];
		data.z = rt->equa->ini[3];
		ft_equa3(rt, rt->equa->ini[0], data);
		return (ft_min(rt, rt->equa));
	}
	if (rt->equa->ini[4] != 0)
	{
		ft_equa4(rt);
		return (ft_min(rt, rt->equa));
	}
	return (0);
}
