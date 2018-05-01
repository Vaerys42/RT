/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 01:16:36 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/31 01:16:37 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int			cylinder_list(t_rt *rt, t_cylinder *cylinder)
{
	if (cylinder->color == NULL)
	{
		ft_putstr("Needs color for cylinder (0 to 1). Ex : color: 1 0 1\n");
		exit(-1);
	}
	if (cylinder->pln != NULL && cylinder->pln->color == NULL)
		cylinder->pln->color = cylinder->color;
	if (rt->cylinder == NULL)
	{
		rt->cylinder = cylinder;
		rt->start->cyl = rt->cylinder;
	}
	else
	{
		rt->cylinder->next = cylinder;
		rt->cylinder = rt->cylinder->next;
	}
	return (1);
}

t_cylinder	*cyl_ini(void)
{
	t_cylinder	*cylinder;

	if (!(cylinder = (t_cylinder*)malloc(sizeof(t_cylinder))))
		ft_malloc_error();
	cylinder->dir = ft_new_vect(0, 1, 0);
	cylinder->next = NULL;
	cylinder->o = ft_new_vect(0, 0, 0);
	cylinder->color = NULL;
	cylinder->rot = ft_new_vect(0, 0, 0);
	cylinder->radius = 1;
	cylinder->shine = 0.5;
	cylinder->pln = NULL;
	cylinder->reflex = 0;
	if (!(cylinder->texture = (t_texture*)malloc(sizeof(t_texture))))
		ft_malloc_error();
	ft_ini_texture(cylinder->texture);
	return (cylinder);
}

int			ft_cyl_read_line2(char **datas, t_cylinder *cyl, t_rt *rt, int fd)
{
	int		random;

	if (ft_strcmp(datas[0], "plnn:") == 0 ||
	ft_strcmp(datas[0], "plnc:") == 0 || ft_strcmp(datas[0], "plno:") == 0)
		inter_plane_cylinder(cyl, datas);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		random = 0;
	else if (ft_strcmp(datas[0], "texture:") == 0)
		cyl->texture->type = get_texture_type(datas);
	else if (ft_strcmp(datas[0], "scale:") == 0)
		cyl->texture->scale = get_scale(datas, 8);
	else if (ft_strcmp(datas[0], "offset:") == 0)
		cyl->texture->offset = get_offset(datas, 9);
	else if (ft_strcmp(datas[0], "path:") == 0)
	{
		cyl->texture->path = get_path(datas);
		cyl->texture->surface = ft_upload_texture(cyl->texture->path);
	}
	else
		return (0);
	return (1);
}

int			ft_cyl_read_line(char **datas, t_cylinder *cyl)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		cyl->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		cyl->color = check_color(cyl->color, datas);
	else if (ft_strcmp(datas[0], "radius:") == 0)
		cyl->radius = get_radius(datas);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		cyl->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		cyl->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "reflex:") == 0)
		cyl->reflex = get_radius(datas);
	else
		return (0);
	return (1);
}

int			ft_add_cylinder(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cylinder	*cylinder;

	cylinder = cyl_ini();
	cylinder->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (ft_cyl_read_line(datas, cylinder) == 0 &&
		ft_cyl_read_line2(datas, cylinder, rt, fd) == 0)
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (cylinder_list(rt, cylinder));
}
