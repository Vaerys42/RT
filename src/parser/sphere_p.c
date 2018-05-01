/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:21:24 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 22:21:25 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int			sphere_list(t_rt *rt, t_sphere *sphere)
{
	ft_sphere_info(sphere);
	if (sphere->pln != NULL && sphere->pln->color == NULL)
		sphere->pln->color = sphere->color;
	if (rt->sphere == NULL)
	{
		rt->sphere = sphere;
		rt->start->sph = rt->sphere;
	}
	else
	{
		rt->sphere->next = sphere;
		rt->sphere = rt->sphere->next;
	}
	return (1);
}

t_sphere	*sph_ini(void)
{
	t_sphere	*sphere;

	if (!(sphere = (t_sphere*)malloc(sizeof(t_sphere))))
		ft_malloc_error();
	sphere->pln = NULL;
	sphere->next = NULL;
	sphere->o = ft_new_vect(0, 0, 0);
	sphere->dir = ft_new_vect(0, 1, 0);
	sphere->color = NULL;
	sphere->rot = ft_new_vect(0, 0, 0);
	sphere->radius = -1;
	sphere->shine = -1;
	sphere->reflex = 0;
	if (!(sphere->texture = (t_texture*)malloc(sizeof(t_texture))))
		ft_malloc_error();
	ft_ini_texture(sphere->texture);
	return (sphere);
}

int			ft_sphere_line2(char **datas, t_sphere *sphere, t_rt *rt, int fd)
{
	int		rand;

	if (ft_strcmp(datas[0], "plnn:") == 0 ||
	ft_strcmp(datas[0], "plnc:") == 0 || ft_strcmp(datas[0], "plno:") == 0)
		inter_plane_sphere(sphere, datas);
	else if (ft_strcmp(datas[0], "texture:") == 0)
		sphere->texture->type = get_texture_type(datas);
	else if (ft_strcmp(datas[0], "scale:") == 0)
		sphere->texture->scale = get_scale(datas, 8);
	else if (ft_strcmp(datas[0], "offset:") == 0)
		sphere->texture->offset = get_offset(datas, 9);
	else if (ft_strcmp(datas[0], "path:") == 0)
	{
		sphere->texture->path = get_path(datas);
		sphere->texture->surface = ft_upload_texture(sphere->texture->path);
	}
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		return (0);
	return (1);
}

int			ft_sphere_line(char **datas, t_sphere *sphere)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		sphere->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		sphere->color = check_color(sphere->color, datas);
	else if (ft_strcmp(datas[0], "radius:") == 0)
		sphere->radius = get_radius(datas);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		sphere->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "reflex:") == 0)
		sphere->reflex = get_radius(datas);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		sphere->rot = get_coo(datas, 7);
	else
		return (0);
	return (1);
}

int			ft_add_sphere(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_sphere	*sphere;

	sphere = sph_ini();
	sphere->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (ft_sphere_line(datas, sphere) == 0 &&
		ft_sphere_line2(datas, sphere, rt, fd) == 0)
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (sphere_list(rt, sphere));
}
