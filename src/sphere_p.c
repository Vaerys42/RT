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

#include "../rt.h"

void		ft_sphere_info(t_sphere *sphere)
{
	if (sphere->color == NULL)
		ft_putstr("Needs color for sphere (0 to 1). Ex : color: 1 0 1\n");
	else if (sphere->radius == -1)
		ft_putstr("Needs radius for sphere. Ex radius: 3\n");
	else if (sphere->shine < 0)
		ft_putstr("Needs shine for sphere. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

int			sphere_list(t_rt *rt, t_sphere *sphere)
{
	ft_sphere_info(sphere);
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
	if (!(sphere->pln = (t_plane*)malloc(sizeof(t_plane))))
		ft_malloc_error();
	sphere->next = NULL;
	sphere->o = ft_new_vect(0, 0, 0);
	sphere->dir = ft_new_vect(0, 1, 0);
	sphere->color = NULL;
	sphere->rot = ft_new_vect(0, 0, 0);
	sphere->radius = -1;
	sphere->shine = -1;
	sphere->pln->o = ft_new_vect(MAX, MAX, MAX);
	sphere->pln->norm = ft_new_vect(0, 1, 0);
	sphere->pln->color = sphere->color;
	return (sphere);
}

void		ft_sphere_line(char **datas, t_sphere *sphere, t_rt *rt, int fd)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		sphere->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		sphere->color = get_color(datas);
	else if (ft_strcmp(datas[0], "radius:") == 0)
		sphere->radius = get_radius(datas);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		sphere->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		sphere->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnn:") == 0)
		sphere->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		sphere->pln->color = get_color(datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		sphere->pln->o = get_coo(datas, 7);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_sphere(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_sphere	*sphere;

	sphere = sph_ini();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_sphere_line(datas, sphere, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (sphere_list(rt, sphere));
}
