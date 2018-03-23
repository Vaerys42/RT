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

void				ft_face_cube(t_cube *cube, int i)
{
	if (i == 2)
        cube->norm = ft_new_vect(0, -1, 0);

}

double				ft_check_cube(t_cube *cube, t_ray *ray)
{
	double		tmin = -9999;
	double		tmax = 9999;
    t_coo       L;
    double      d;
    double      m;
    double      t1;
    double      t2;
    double      t;

	L = ft_sub_vect(cube->o, ray->o);
    d = scal(cube->norm, L);
    m = scal(cube->norm, ray->dir);
    printf("d %f m %f\n", d, m);
    if (fabs(m) < EPS && fabs(d) > cube->radius)
        return (0);
    else
    {
        t1 = (d - cube->radius) / m;
        t2 = (d + cube->radius) / m;
        if (t1 > t2)
        {
            t = t1;
            t1 = t2;
            t2 = t;
        }
        if (t1 > tmin)
            tmin = t1;
        if (t2 < tmax)
            tmax = t2;
        if (tmin > tmax || tmax < 0)
            return (0);
    }
    if (tmin > 0)
        return (tmin);
    return (tmax);
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
		rt->inter->angle->dir = rt->cube->norm;
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
			while (i <= 2)
			{
				ft_face_cube(rt->cube, i);			
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
