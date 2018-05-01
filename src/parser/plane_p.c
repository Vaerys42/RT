/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 00:49:56 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/31 00:49:58 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_plane		*ini_plane(void)
{
	t_plane		*plane;

	if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
		ft_malloc_error();
	plane->next = NULL;
	plane->o = ft_new_vect(0, 0, 0);
	plane->color = NULL;
	plane->norm = ft_new_vect(0, 1, 0);
	plane->reflex = 0;
	if (!(plane->texture = (t_texture*)malloc(sizeof(t_texture))))
		ft_malloc_error();
	ft_ini_texture(plane->texture);
	return (plane);
}

int			plane_lst(t_rt *rt, t_plane *plane)
{
	ft_plane_info(plane);
	plane->norm = ft_normalize(plane->norm);
	plane->supp = (-1) * plane->o.x * plane->norm.x +
	(-1) * plane->o.y * plane->norm.y +
	(-1) * plane->o.z * plane->norm.z;
	if (rt->plane == NULL)
	{
		rt->plane = plane;
		rt->start->pln = rt->plane;
	}
	else
	{
		rt->plane->next = plane;
		rt->plane = rt->plane->next;
	}
	return (1);
}

int			ft_plane_line2(char **datas, int fd, t_rt *rt, t_plane *plane)
{
	if (ft_strcmp(datas[0], "scale:") == 0)
		plane->texture->scale = get_scale(datas, 8);
	else if (ft_strcmp(datas[0], "offset:") == 0)
		plane->texture->offset = get_offset(datas, 9);
	else if (ft_strcmp(datas[0], "path:") == 0)
	{
		plane->texture->path = get_path(datas);
		plane->texture->surface = ft_upload_texture(plane->texture->path);
	}
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		return (1);
	else
		return (0);
	return (1);
}

int			ft_plane_line(char **datas, t_plane *plane)
{
	if (datas[0] == 0)
		return (1);
	else if (ft_strcmp(datas[0], "coo:") == 0)
		plane->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		plane->color = check_color(plane->color, datas);
	else if (ft_strcmp(datas[0], "norm:") == 0)
		plane->norm = get_coo(datas, 6);
	else if (ft_strcmp(datas[0], "reflex:") == 0)
		plane->reflex = get_radius(datas);
	else if (ft_strcmp(datas[0], "texture:") == 0)
		plane->texture->type = get_texture_type(datas);
	else
		return (0);
	return (1);
}

int			ft_add_plane(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_plane		*plane;

	plane = ini_plane();
	plane->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (ft_plane_line(datas, plane) == 0 &&
		ft_plane_line2(datas, fd, rt, plane) == 0)
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (plane_lst(rt, plane));
}
