/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 22:08:43 by kboucaud          #+#    #+#             */
/*   Updated: 2018/02/25 22:08:48 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_light_info(t_light *light)
{
	if (light->color == NULL)
		ft_putstr("Needs color for light (0 to 1). Ex : color: 1 0 1\n");
	else if (light->power == -1)
		ft_putstr("Needs power for light. Ex radius: 3\n");
	else
		return ;
	exit(-1);
}

int			light_list(t_rt *rt, t_light *light)
{
	ft_light_info(light);
	if (rt->start->lgh == NULL)
	{
		rt->light = light;
		rt->start->lgh = rt->light;
	}
	else
	{
		rt->light->next = light;
		rt->light = rt->light->next;
	}
	return (1);
}

t_light		*light_ini(void)
{
	t_light	*light;

	if (!(light = (t_light*)malloc(sizeof(t_light))))
		ft_malloc_error();
	light->o = ft_new_vect(0, 0, 0);
	light->dir = ft_new_vect(0, 0, 0);
	light->norm = ft_new_vect(0, 0, 0);
	light->color = NULL;
	light->power = -1;
	light->shine = 0;
	light->next = NULL;
	return (light);
}

void		ft_light_line(char **datas, t_light *light, t_rt *rt, int fd)
{
	int		random;

	if (datas[0] == 0)
		random = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		light->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "dir:") == 0)
		light->dir = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "norm:") == 0)
		light->norm = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		light->color = check_color(light->color, datas);
	else if (ft_strcmp(datas[0], "angle:") == 0)
		light->angle = get_radius(datas);
	else if (ft_strcmp(datas[0], "pow:") == 0)
		light->power = get_radius(datas);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		random = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_light(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_light		*light;

	light = light_ini();
	light->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_light_line(datas, light, rt, fd);
		ft_freetab(datas);
		free(line);
	}
	return (light_list(rt, light));
}
