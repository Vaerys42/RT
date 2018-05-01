/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parabol_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:21:24 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 18:08:49 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int			parabol_list(t_rt *rt, t_parabol *parabol)
{
	ft_parabol_info(parabol);
	if (parabol->pln != NULL && parabol->pln->color == NULL)
		parabol->pln->color = parabol->color;
	if (rt->parabol == NULL)
	{
		rt->parabol = parabol;
		rt->start->par = rt->parabol;
	}
	else
	{
		rt->parabol->next = parabol;
		rt->parabol = rt->parabol->next;
	}
	return (1);
}

t_parabol	*par_ini(void)
{
	t_parabol	*parabol;

	if (!(parabol = (t_parabol*)malloc(sizeof(t_parabol))))
		ft_malloc_error();
	parabol->pln = NULL;
	parabol->next = NULL;
	parabol->o = ft_new_vect(0, 0, 0);
	parabol->dir = ft_new_vect(0, 1, 0);
	parabol->color = NULL;
	parabol->rot = ft_new_vect(0, 0, 0);
	parabol->rad1 = -1;
	parabol->rad2 = -2;
	parabol->shine = -1;
	return (parabol);
}

void		inter_plane_parabol(t_parabol *parabol, char **datas)
{
	if (parabol->pln == NULL)
	{
		if (!(parabol->pln = (t_plane*)malloc(sizeof(t_plane))))
			ft_malloc_error();
		parabol->pln->o = (t_coo){0, 0, 0};
		parabol->pln->norm = (t_coo){0, 1, 0};
		parabol->pln->color = NULL;
		parabol->pln->cut = 0;
	}
	if (ft_strcmp(datas[0], "plnn:") == 0)
		parabol->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		parabol->pln->color = check_color(parabol->pln->color, datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		parabol->pln->o = get_coo(datas, 7);
}

void		ft_parabol_line(char **datas, t_parabol *parabol, t_rt *rt, int fd)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		parabol->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		parabol->color = check_color(parabol->color, datas);
	else if (ft_strcmp(datas[0], "rad1:") == 0)
		parabol->rad1 = get_radius(datas);
	else if (ft_strcmp(datas[0], "rad2:") == 0)
		parabol->rad2 = get_radius(datas);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		parabol->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		parabol->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnn:") == 0 ||
	ft_strcmp(datas[0], "plnc:") == 0 || ft_strcmp(datas[0], "plno:") == 0)
		inter_plane_parabol(parabol, datas);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_parabol(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_parabol	*parabol;

	parabol = par_ini();
	parabol->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_parabol_line(datas, parabol, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (parabol_list(rt, parabol));
}
