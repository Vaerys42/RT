/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipse_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:21:24 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/30 22:21:25 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		ft_ellipse_info(t_ellipse *ellipse)
{
	if (ellipse->color == NULL)
		ft_putstr("Needs color for ellipse (0 to 1). Ex : color: 1 0 1\n");
	else if (ellipse->shine < 0)
		ft_putstr("Needs shine for ellipse. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

int			ellipse_list(t_rt *rt, t_ellipse *ellipse)
{
	ft_ellipse_info(ellipse);
	if (rt->ellipse == NULL)
	{
		rt->ellipse = ellipse;
		rt->start->ell = rt->ellipse;
	}
	else
	{
		rt->ellipse->next = ellipse;
		rt->ellipse = rt->ellipse->next;
	}
	return (1);
}

t_ellipse	*ell_ini(void)
{
	t_ellipse	*ellipse;

	if (!(ellipse = (t_ellipse*)malloc(sizeof(t_ellipse))))
		ft_malloc_error();
	if (!(ellipse->obj = (t_object*)malloc(sizeof(t_object))))
		ft_malloc_error();
	if (!(ellipse->obj->pln = (t_plane*)malloc(sizeof(t_plane))))
		ft_malloc_error();
	ellipse->next = NULL;
	ellipse->o = ft_new_vect(0, 0, 0);
	ellipse->dir = ft_new_vect(0, 1, 0);
	ellipse->color = NULL;
	ellipse->rot = ft_new_vect(0, 0, 0);
	ellipse->rad1 = ft_new_vect(0, 0, 0);
    ellipse->rad2 = ft_new_vect(0, 0, 0);
    ellipse->rad3 = ft_new_vect(0, 0, 0);
	ellipse->shine = -1;
	ellipse->obj->pln->o = ft_new_vect(MAX, MAX, MAX);
	ellipse->obj->pln->norm = ft_new_vect(0, 1, 0);
	ellipse->obj->pln->color = ellipse->color;
	return (ellipse);
}

void		ft_ellipse_line(char **datas, t_ellipse *ellipse, t_rt *rt, int fd)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		ellipse->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		ellipse->color = get_color(datas);
	else if (ft_strcmp(datas[0], "rad1:") == 0)
		ellipse->rad1 = get_coo(datas, 7);
    else if (ft_strcmp(datas[0], "rad2:") == 0)
		ellipse->rad2 = get_coo(datas, 7);
    else if (ft_strcmp(datas[0], "rad3:") == 0)
		ellipse->rad3 = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		ellipse->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		ellipse->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnn:") == 0)
		ellipse->obj->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		ellipse->obj->pln->color = get_color(datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		ellipse->obj->pln->o = get_coo(datas, 7);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		{
            printf("%s\n", datas[0]);
            ft_bad_arg(5);}
}

int			ft_add_ellipse(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_ellipse	*ellipse;

	ellipse = ell_ini();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_ellipse_line(datas, ellipse, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (ellipse_list(rt, ellipse));
}
