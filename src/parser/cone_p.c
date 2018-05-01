/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 01:16:26 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/31 01:16:26 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_cone		*new_cone(void)
{
	t_cone		*cone;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		ft_malloc_error();
	cone->next = NULL;
	cone->pln = NULL;
	cone->o = ft_new_vect(0, 0, 0);
	cone->dir = ft_new_vect(0, 1, 0);
	cone->color = NULL;
	cone->rot = ft_new_vect(0, 0, 0);
	cone->angle = -1;
	cone->shine = -1;
	cone->reflex = 0;
	if (!(cone->texture = (t_texture*)malloc(sizeof(t_texture))))
		ft_malloc_error();
	ft_ini_texture(cone->texture);
	return (cone);
}

int			cone_lst(t_rt *rt, t_cone *cone)
{
	ft_cone_info(cone);
	if (cone->pln != NULL && cone->pln->color == NULL)
		cone->pln->color = cone->color;
	cone->dir = ft_normalize(cone->dir);
	cone->angle = (cone->angle * M_PI) / 180;
	if (rt->cone == NULL)
	{
		rt->cone = cone;
		rt->start->con = rt->cone;
	}
	else
	{
		rt->cone->next = cone;
		rt->cone = rt->cone->next;
	}
	return (1);
}

int			ft_read_line2(char **datas, t_cone *cone, t_rt *rt, int fd)
{
	int			random;

	if (ft_strcmp(datas[0], "plnn:") == 0 ||
	ft_strcmp(datas[0], "plnc:") == 0 || ft_strcmp(datas[0], "plno:") == 0)
		inter_plane_cone(cone, datas);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		random = 0;
	else if (ft_strcmp(datas[0], "texture:") == 0)
		cone->texture->type = get_texture_type(datas);
	else if (ft_strcmp(datas[0], "scale:") == 0)
		cone->texture->scale = get_scale(datas, 8);
	else if (ft_strcmp(datas[0], "offset:") == 0)
		cone->texture->offset = get_offset(datas, 9);
	else if (ft_strcmp(datas[0], "path:") == 0)
	{
		cone->texture->path = get_path(datas);
		cone->texture->surface = ft_upload_texture(cone->texture->path);
	}
	else
		return (0);
	return (1);
}

int			ft_read_line(char **datas, t_cone *cone)
{
	int		random;

	if (datas[0] == 0)
		random = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		cone->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		cone->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "color:") == 0)
		cone->color = check_color(cone->color, datas);
	else if (ft_strcmp(datas[0], "angle:") == 0)
		cone->angle = get_radius(datas);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		cone->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "reflex:") == 0)
		cone->reflex = get_radius(datas);
	else
		return (0);
	return (1);
}

int			ft_add_cone(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cone		*cone;

	cone = new_cone();
	cone->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (ft_read_line(datas, cone) == 0 &&
		ft_read_line2(datas, cone, rt, fd) == 0)
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (cone_lst(rt, cone));
}
