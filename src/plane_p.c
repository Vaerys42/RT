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

#include "../rtv1.h"

void		ft_plane_info(t_plane *plane)
{
	if (plane->color == NULL)
		ft_putstr("Needs color for plane (0 to 1). Ex : color: 1 0 1\n");
	else
		return ;
	exit(-1);
}

t_plane		*ini_plane(void)
{
	t_plane		*plane;

	if (!(plane = (t_plane*)malloc(sizeof(t_plane))))
		ft_malloc_error();
	plane->next = NULL;
	plane->o = ft_new_vect(0, 0, 0);
	plane->color = NULL;
	plane->norm = ft_new_vect(0, 1, 0);
	plane->obj = 0;
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

void		ft_plane_line(char **datas, int fd, t_rt *rt, t_plane *plane)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		plane->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		plane->color = get_color(datas);
	else if (ft_strcmp(datas[0], "norm:") == 0)
		plane->norm = get_coo(datas, 6);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_plane(int fd, t_rt *rt, int obj)
{
	int			ret;
	char		*line;
	char		**datas;
	t_plane		*plane;

	plane = ini_plane();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_plane_line(datas, fd, rt, plane);
		ft_freetab(datas);
		free(line);
	}
	plane->obj = obj;
	return (plane_lst(rt, plane));
}
