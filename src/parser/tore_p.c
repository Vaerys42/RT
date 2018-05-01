/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:21:24 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/24 18:08:33 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int			tore_list(t_rt *rt, t_tore *tore)
{
	ft_tore_info(tore);
	if (tore->pln != NULL && tore->pln->color == NULL)
		tore->pln->color = tore->color;
	if (rt->tore == NULL)
	{
		rt->tore = tore;
		rt->start->tor = rt->tore;
	}
	else
	{
		rt->tore->next = tore;
		rt->tore = rt->tore->next;
	}
	return (1);
}

t_tore		*tor_ini(void)
{
	t_tore	*tore;

	if (!(tore = (t_tore*)malloc(sizeof(t_tore))))
		ft_malloc_error();
	tore->pln = NULL;
	tore->next = NULL;
	tore->o = ft_new_vect(0, 0, 0);
	tore->dir = ft_new_vect(0, 0, 1);
	tore->rot = ft_new_vect(0, 0, 0);
	tore->color = NULL;
	tore->radiusa = -1;
	tore->radiusb = -1;
	tore->shine = -1;
	return (tore);
}

void		inter_plane_tore(t_tore *tore, char **datas)
{
	if (tore->pln == NULL)
	{
		if (!(tore->pln = (t_plane*)malloc(sizeof(t_plane))))
			ft_malloc_error();
		tore->pln->o = (t_coo){0, 0, 0};
		tore->pln->norm = (t_coo){0, 1, 0};
		tore->pln->color = tore->color;
		tore->pln->cut = 0;
	}
	if (ft_strcmp(datas[0], "plnn:") == 0)
		tore->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		tore->pln->color = check_color(tore->pln->color, datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		tore->pln->o = get_coo(datas, 7);
}

void		ft_tore_line(char **datas, t_tore *tore, t_rt *rt, int fd)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		tore->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		tore->color = check_color(tore->color, datas);
	else if (ft_strcmp(datas[0], "radiusa:") == 0)
		tore->radiusa = get_radius(datas);
	else if (ft_strcmp(datas[0], "radiusb:") == 0)
		tore->radiusb = get_radius(datas);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		tore->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		tore->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnn:") == 0 ||
	ft_strcmp(datas[0], "plnc:") == 0 || ft_strcmp(datas[0], "plno:") == 0)
		inter_plane_tore(tore, datas);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_tore(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_tore		*tore;

	tore = tor_ini();
	tore->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_tore_line(datas, tore, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (tore_list(rt, tore));
}
