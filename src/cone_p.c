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

#include "../rt.h"

void		ft_cone_info(t_cone *cone)
{
	if (cone->color == NULL)
		ft_putstr("Needs color for cone (0 to 1). Ex : color: 1 0 1\n");
	else if (cone->angle < 0)
		ft_putstr("Needs angle for cone. Ex angle: 30\n");
	else if (cone->shine < 0)
		ft_putstr("Needs shine for cone. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

t_cone		*new_cone(void)
{
	t_cone		*cone;

	if (!(cone = (t_cone*)malloc(sizeof(t_cone))))
		ft_malloc_error();
	if (!(cone->obj = (t_object*)malloc(sizeof(t_object))))
        ft_malloc_error();
	if (!(cone->obj->pln = (t_plane*)malloc(sizeof(t_plane))))
        ft_malloc_error();
	cone->next = NULL;
	cone->o = ft_new_vect(0, 0, 0);
	cone->dir = ft_new_vect(0, 1, 0);
	cone->color = NULL;
	cone->rot = ft_new_vect(0, 0, 0);
	cone->angle = -1;
	cone->shine = -1;
	cone->obj->cut = 0;
	cone->obj->pln->o = ft_new_vect(MAX, MAX, MAX);
	cone->obj->pln->norm = cone->dir;
	cone->obj->pln->color = cone->color;
	return (cone);
}

int			cone_lst(t_rt *rt, t_cone *cone)
{
	ft_cone_info(cone);
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

void		ft_read_line(char **datas, t_cone *cone, t_rt *rt, int fd)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		cone->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		cone->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "color:") == 0)
		cone->color = get_color(datas);
	else if (ft_strcmp(datas[0], "angle:") == 0)
		cone->angle = get_radius(datas);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		cone->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "plnn:") == 0)
		cone->obj->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		cone->obj->pln->color = get_color(datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		cone->obj->pln->o = get_coo(datas, 7);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_cone(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cone		*cone;

	cone = new_cone();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_read_line(datas, cone, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (cone_lst(rt, cone));
}
