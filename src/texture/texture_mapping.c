/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:29:07 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/27 15:32:39 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_coo				ft_mapping_all(t_coo hit, t_rt *rt)
{
	t_coo			point_2d;

	point_2d = hit;
	point_2d.z = 0;
	if (rt->inter->obj == SPH)
		point_2d = ft_mapping_sphere(hit);
	else if (rt->inter->obj == CYL)
		point_2d = ft_mapping_cylinder(hit);
	else if (rt->inter->obj == CON)
		point_2d = ft_mapping_cone(hit);
	else if (rt->inter->obj == PLN)
		point_2d = ft_mapping_plane(hit, rt->plane->o, rt->plane->norm);
	return (point_2d);
}

t_coo				ft_mapping_plane(t_coo hit, t_coo origin, t_coo norm)
{
	t_coo			point_2d;
	t_coo			u_fixed;
	t_coo			v_fixed;
	double			scale_x;
	double			scale_y;

	scale_x = 0.25;
	scale_y = 0.25;
	origin.x = 0;
	u_fixed = norm;
	u_fixed.x = norm.y;
	u_fixed.y = norm.z;
	u_fixed.z = -norm.x;
	v_fixed.x = u_fixed.y * norm.z - u_fixed.z * norm.y;
	v_fixed.y = u_fixed.z * norm.x - u_fixed.x * norm.z;
	v_fixed.z = u_fixed.x * norm.y - u_fixed.y * norm.x;
	point_2d.x = scal(hit, u_fixed) * scale_x;
	point_2d.y = scal(hit, v_fixed) * scale_y;
	point_2d.x -= floor(point_2d.x);
	point_2d.y -= floor(point_2d.y);
	return (point_2d);
}

t_coo				ft_mapping_cone(t_coo hit)
{
	t_coo			point_2d;

	point_2d.x = 0.5 + atan2(hit.z, hit.x) / (2 * M_PI);
	point_2d.y = hit.y / M_PI - floor(hit.y / M_PI);
	return (point_2d);
}

t_coo				ft_mapping_cylinder(t_coo hit)
{
	t_coo			point_2d;

	point_2d.x = 0.5 + atan2(hit.z, hit.x) / (2 * M_PI);
	point_2d.y = hit.y / M_PI - floor(hit.y / M_PI);
	return (point_2d);
}

t_coo				ft_mapping_sphere(t_coo hit)
{
	t_coo			point_2d;

	hit = ft_normalize(hit);
	point_2d.x = 0.5 + atan2(hit.z, hit.x) / (2 * M_PI);
	point_2d.y = 0.5 - asin(hit.y) / M_PI;
	return (point_2d);
}
