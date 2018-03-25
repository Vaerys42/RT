/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:00:38 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 19:00:41 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void				ft_face_cube(t_rt *rt, t_cube *cube, int i)
{
    if (i == 1)
        {
            cube->a = ft_new_vect(cube->o.x + cube->radius, cube->o.y + cube->radius, cube->o.z - cube->radius);
            cube->u = ft_new_vect(0, 0, cube->radius * 2);
            cube->v = ft_new_vect(0, - cube->radius * 2, 0);
        }
	if (i == 2)
        {
            cube->a = ft_new_vect(cube->o.x - cube->radius, cube->o.y + cube->radius, cube->o.z + cube->radius);
            cube->u = ft_new_vect(0, 0, - cube->radius * 2);
            cube->v = ft_new_vect(0, - cube->radius * 2, 0);
        }
    if (i == 3)
        {
            cube->a = ft_new_vect(cube->o.x - cube->radius, cube->o.y + cube->radius, cube->o.z + cube->radius);
            cube->u = ft_new_vect(cube->radius * 2, 0, 0);
            cube->v = ft_new_vect(0, 0, - cube->radius * 2);
        }
    if (i == 4)
        {
            cube->a = ft_new_vect(cube->o.x - cube->radius, cube->o.y - cube->radius, cube->o.z - cube->radius);
            cube->u = ft_new_vect(cube->radius * 2, 0, 0);
            cube->v = ft_new_vect(0, 0 , cube->radius * 2);
            }
    if (i == 5)
        {
            cube->a = ft_new_vect(cube->o.x + cube->radius, cube->o.y - cube->radius, cube->o.z + cube->radius);
            cube->u = ft_new_vect(0, cube->radius * 2, 0);
            cube->v = ft_new_vect(- cube->radius * 2, 0, 0);
        }
    if (i == 6)
        {
            cube->a = ft_new_vect(cube->o.x - cube->radius, cube->o.y + cube->radius, cube->o.z - cube->radius);
            cube->u = ft_new_vect(cube->radius * 2, 0, 0);
            cube->v = ft_new_vect(0, - cube->radius * 2, 0);
        }
    rt->inter->angle->dir = ft_normalize(ft_det_vect(cube->u, cube->v));
}

double				ft_check_cube(t_cube *cube, t_ray *ray)
{
    double      D;
    double      a;
    double      b;
    double      t;

    ray->obj = ft_sub_vect(ray->o, cube->a);
    D = - scal(ft_det_vect(cube->u, cube->v), ray->dir);
    a = - (scal(ft_det_vect(ray->obj, cube->v), ray->dir)) / D;
    b = - (scal(ft_det_vect(cube->u, ray->obj), ray->dir)) / D;
    t = scal(ft_det_vect(cube->u, cube->v), ray->obj) / D;
    if (a > 0 && b > 0 && a <= 1 && b <= 1)
        return (t);
    return (0);
}

void				new_cube_dst(t_rt *rt, int type, double tmp)
{
	rt->inter->dst = tmp;
	if (type == 0)
	{
		rt->inter->obj = CUB;
		rt->inter->num = rt->cube->obj;
		rt->inter->mat->r = rt->cube->color->r * rt->light->amb;
		rt->inter->mat->g = rt->cube->color->g * rt->light->amb;
		rt->inter->mat->b = rt->cube->color->b * rt->light->amb;
		return ;
	}
	if (type == 1 && rt->inter->obj == CUB && rt->inter->num == rt->cube->obj)
	{
       // rt->light->shine = rt->cube->shine;
		rt->inter->mat->r *= 2;
		rt->inter->mat->g *= 2;
		rt->inter->mat->b *= 2;
	}
}

void				check_cube_inter(t_rt *rt, int type)
{
	double		tmp;
    int         i;

	if (rt->start->cub != NULL)
	{
		rt->cube = rt->start->cub;
		while (rt->cube != NULL)
		{
			i = 1;
			while (i <= 6)
			{
				ft_face_cube(rt, rt->cube, i);
				if (type == 0)
					tmp = ft_check_cube(rt->cube, rt->ray);
				else
					tmp = ft_check_cube(rt->cube, rt->light_ray);
				if (tmp > 0.01 && tmp < rt->inter->dst)
					new_cube_dst(rt, type, tmp);
				i++;
			}
			rt->cube = rt->cube->next;
		}
	}
}
