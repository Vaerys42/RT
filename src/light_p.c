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

#include "../rt.h"

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
	light->color = NULL;
	light->power = -1;
	light->shine = 0;
	light->amb = 0.1;
	light->next = NULL;
	return (light);
}

int			ft_add_light(int fd, t_rt *rt)
{
	int			ret;
	char		*line;
	char		**datas;
	t_light		*light;

	light = light_ini();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (datas[0] == 0)
			ret++;
		else if (ft_strcmp(datas[0], "coo:") == 0)
			light->o = get_coo(datas, 2);
		else if (ft_strcmp(datas[0], "color:") == 0)
			light->color = get_color(datas);
		else if (ft_strcmp(datas[0], "pow:") == 0)
			light->power = get_radius(datas);
		else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (light_list(rt, light));
}
