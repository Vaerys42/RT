/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 00:31:27 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 18:38:18 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		ft_check_expose(t_material *mat, double max)
{
	if (mat->r > max)
		mat->r = max;
	if (mat->b > max)
		mat->b = max;
	if (mat->g > max)
		mat->g = max;
}

void		ft_check_expose_bis(t_material *mat, double max)
{
	if (mat->r > max)
		max = mat->r;
	if (mat->b > max)
		max = mat->b;
	if (mat->g > max)
		max = mat->g;
	move_color(mat, mat->r / max, mat->g / max, mat->b / max);
}

void		ft_get_point(t_rt *rt)
{
	rt->inter->point = ft_mult_vect(rt->inter->dst, rt->ray->dir);
	rt->inter->point = ft_add_vect(rt->cam->pos, rt->inter->point);
}

void		ft_apply_light(t_rt *rt)
{
	// Couleur ambiante
	rt->inter->mat->r += AMB;
	rt->inter->mat->g += AMB;
	rt->inter->mat->b += AMB;
	ft_check_expose_bis(rt->inter->mat, 1);
	// On applique l'intensite calculee a la couleur de l'objet
	rt->inter->mat->r *= rt->inter->col->r;
	rt->inter->mat->g *= rt->inter->col->g;
	rt->inter->mat->b *= rt->inter->col->b;
	//ft_check_expose(rt->inter->mat, 1.0);
}

void		ft_light_diffspec(t_rt *rt)
{
	double		diff;
	t_coo		vue;
	t_coo		refl;
	double		spec;

	move_color(rt->inter->kdif, 0.5, 0.5, 0.5);
	move_color(rt->inter->kspe, 0.2, 0.2, 0.2);	
	rt->light_ray->dir = ft_sub_vect(rt->light->o, rt->inter->point);
	//rt->light_ray->dir = ft_sub_vect(rt->inter->point, rt->light->o);
	rt->light_ray->dir = ft_normalize(rt->light_ray->dir);
	rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	diff = scal(rt->light_ray->dir, rt->inter->angle->dir);
	diff = (diff < 0.01) ? 0.01 : diff;
	vue = ft_mult_vect(-1, rt->ray->dir);
	refl = ft_mult_vect(2 * diff, rt->inter->angle->dir);
	refl = ft_sub_vect(refl, rt->light_ray->dir);
	refl = ft_normalize(refl);
	spec = scal(refl, vue);
	/*refl = ft_mult_vect(2 * diff, rt->inter->angle->dir);
	refl = ft_sub_vect(rt->light_ray->dir, refl);
	spec = scal(refl, rt->light_ray->dir);*/
	rt->inter->mat->r += rt->light->color->r * diff * rt->inter->kdif->r + rt->inter->kspe->r * pow(spec, 10);
	rt->inter->mat->g += rt->light->color->g * diff * rt->inter->kdif->g + rt->inter->kspe->r * pow(spec, 10);
	rt->inter->mat->b += rt->light->color->b * diff * rt->inter->kdif->b + rt->inter->kspe->r * pow(spec, 10);
	ft_check_expose_bis(rt->inter->mat, 1);
}

void		check_forms(t_rt *rt, int type)
{
	check_sphere_inter(rt, type);
	check_cone_inter(rt, type);
	check_cylinder_inter(rt, type);
	check_cube_inter(rt, type);
	check_ellipse_inter(rt, type);
	check_plane_inter(rt, type);
}

void		ft_get_light(t_rt *rt)
{
	move_color(rt->inter->mat, 0, 0, 0);
	rt->light = rt->start->lgh;
	while (rt->light)
	{
		rt->inter->dst = MAX;
		rt->inter->angle->dir = rt->ray->dir;
		rt->light_ray->o = rt->light->o;
		rt->light_ray->dir = ft_normalize(ft_sub_vect(rt->inter->point,
		rt->light->o));
		rt->light->shine = 0;
		check_forms(rt, 1);
		ft_light_diffspec(rt);
		rt->light = rt->light->next;
	}
	ft_apply_light(rt);
	ft_check_expose(rt->inter->mat, 1.0);
}

void		ft_check_object(t_rt *rt)
{
	rt->inter->dst = MAX;
	rt->inter->obj = 0;
	rt->inter->angle->dir = rt->ray->dir;
	rt->inter->num = 0;
	move_color(rt->inter->col, 0, 0, 0);
	rt->light = rt->start->lgh;
	check_forms(rt, 0);
	if (rt->inter->dst <= 0.01)
		rt->inter->dst = 0;
	if (rt->inter->dst != MAX)
	{
		ft_get_point(rt);
		ft_get_light(rt);
	}
	return ;
}
