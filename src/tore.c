/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:01:32 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:01:34 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double      ft_min(t_rt *rt, t_equa *equa)
{
	double		t[4];
    double      t1;
	double		t2;
	int			k;
	int			i;

	k = 0;
	i = 0;
	t[0] = MAX;
	t[1] = MAX;
	while (k < 4)
	{
	if (cimag(equa->x[k]) == 0 && creal(equa->x[k]) < MAX && creal(equa->x[k]) > 0.1)
			{
				t[i] = creal(equa->x[k]);
				i++;
			}
		k++;
	}
	t1 = t[0];
	t2 = t[1];
	if (rt->tore->pln == NULL)
		return (disc_eq(t1, t2));
	return (ft_inter_plane_ini(rt->ray, rt->tore->pln, t1, t2));
}


void        ft_tore_det(t_tore *tore, t_equa *equa, t_ray *ray)
{
	ray->obj = ft_sub_vect(ray->o, tore->o);
	equa->ini[0] = pow(scal(ray->dir, ray->dir), 2);
   	equa->ini[1] = 4 * scal(ray->dir, ray->dir) * scal(ray->dir, ray->obj);
   	equa->ini[2] = 4 * pow(scal(ray->dir, ray->obj), 2) + 2 * scal(ray->dir, ray->dir) * (scal(ray->obj, ray->obj) - pow(tore->radiusb, 2) - pow(tore->radiusa, 2)) + 4 * pow(tore->radiusb, 2) * pow(scal(ray->dir, tore->dir), 2);
   	equa->ini[3] = 4 * scal(ray->dir, ray->obj) * (scal(ray->obj, ray->obj) - pow(tore->radiusb, 2) - pow(tore->radiusa, 2)) + 8 * pow(tore->radiusb, 2) * scal(ray->dir, tore->dir) * scal(ray->obj, tore->dir);
   	equa->ini[4] = pow(scal(ray->obj, ray->obj) - pow(tore->radiusb, 2) - pow(tore->radiusa, 2), 2) + 4 * pow(tore->radiusb, 2) * pow(scal(ray->obj, tore->dir), 2) - 4 * pow(tore->radiusb, 2) * pow(tore->radiusa, 2);
}

double		ft_check_tore(t_rt *rt, t_ray *ray)
{
    ft_tore_det(rt->tore, rt->equa, ray);
    if (rt->equa->ini[4] == 0 && rt->equa->ini[3] == 0)
	{
		ft_equa2(rt->equa, rt->equa->ini[0], rt->equa->ini[1], rt->equa->ini[2]);
		return (ft_min(rt, rt->equa));
	}
    if (rt->equa->ini[4] == 0 && rt->equa->ini[3] != 0)
    {
        ft_equa3(rt, rt->equa->ini[0], rt->equa->ini[1], rt->equa->ini[2], rt->equa->ini[3]);
        return (ft_min(rt, rt->equa));
    }
    if (rt->equa->ini[4] != 0)
	{
		ft_equa4(rt);
		return (ft_min(rt, rt->equa));
	}
    return (0);
}

void		cam_tore_inter(t_rt *rt)
{
	rt->inter->obj = TOR;
	rt->inter->num = rt->tore->id;
	rt->inter->col->r = rt->tore->color->r;
	rt->inter->col->g = rt->tore->color->g;
	rt->inter->col->b = rt->tore->color->b;
	if (rt->tore->pln != NULL && rt->tore->pln->cut == 1)
	{
		rt->inter->col->r = rt->tore->pln->color->r;
		rt->inter->col->g = rt->tore->pln->color->g;
		rt->inter->col->b = rt->tore->pln->color->b;
	}
}

void		light_tore_inter(t_rt *rt)
{
	t_coo	obj;

	rt->light->shine = rt->tore->shine;
	obj = ft_sub_vect(rt->inter->point, rt->tore->o);
	rt->ray->obj = ft_sub_vect(rt->ray->o, rt->tore->o);
	rt->inter->angle->dir.x = 4 * obj.x * (scal(obj, obj) +
	pow(rt->tore->radiusb, 2) - pow(rt->tore->radiusa, 2)) - 8 * 
    pow(rt->tore->radiusb, 2) * obj.x;
	rt->inter->angle->dir.y = 4 * obj.y * (scal(obj, obj) + 
    pow(rt->tore->radiusb, 2) - pow(rt->tore->radiusa, 2)) - 8 * 
    pow(rt->tore->radiusb, 2) * obj.y;
	rt->inter->angle->dir.z = 4 * obj.z * (scal(obj, obj) + 
    pow(rt->tore->radiusb, 2) - pow(rt->tore->radiusa, 2));
	if (rt->tore->pln != NULL && rt->tore->pln->cut == 1)
		rt->inter->angle->dir = rt->tore->pln->norm;
}

void		new_tore_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
		cam_tore_inter(rt);
	if (type == 1 && rt->inter->obj == TOR)
		light_tore_inter(rt);
}

void		check_tore_inter(t_rt *rt, int type)
{
	double	tmp;

	if (rt->start->tor != NULL)
	{
		rt->tore = rt->start->tor;
		while (rt->tore != NULL)
		{
			if (rt->tore->pln != NULL)
				rt->tore->pln->cut = 0;
			if (type == 0)
				tmp = ft_check_tore(rt, rt->ray);
			else
				tmp = ft_check_tore(rt, rt->light_ray);
			if (tmp > 0.01 && tmp < rt->inter->dst)
				new_tore_dst(rt, type, tmp);
			rt->tore = rt->tore->next;
		}
	}
}

