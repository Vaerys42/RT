/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 00:49:56 by kboucaud          #+#    #+#             */
/*   Updated: 2018/01/31 00:49:58 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		ft_cube_info(t_cube *cube)
{
	if (cube->color == NULL)
		ft_putstr("Needs color for cube (0 to 1). Ex : color: 1 0 1\n");
	else if (cube->radius == -1)
		ft_putstr("Needs radius for cube. Ex radius: 3\n");
	else if (cube->shine < 0)
		ft_putstr("Needs shine for sphere. Ex shine: 0.5\n");
	else
		return ;
	exit(-1);
}

t_cube		*ini_cube(void)
{
	t_cube		*cube;

	if (!(cube = (t_cube*)malloc(sizeof(t_cube))))
		ft_malloc_error();
	cube->next = NULL;
	cube->o = ft_new_vect(0, 0, 0);
	cube->a = ft_new_vect(0, 0, 0);
	cube->u = ft_new_vect(0, 0, 0);
	cube->v = ft_new_vect(0, 0, 0);
	cube->shine = -1;
	cube->rot = ft_new_vect(0, 0, 0);
	cube->color = NULL;
	cube->dir = ft_new_vect(0, 1, 0);
	cube->radius = -1;
	return (cube);
}

int			cube_lst(t_rt *rt, t_cube *cube)
{
	ft_cube_info(cube);
	if (rt->cube == NULL)
	{
		rt->cube = cube;
		rt->start->cub = rt->cube;
	}
	else
	{
		rt->cube->next = cube;
		rt->cube = rt->cube->next;
	}
	return (1);
}

void		ft_cube_line(char **datas, int fd, t_rt *rt, t_cube *cube)
{
	int		rand;

	if (datas[0] == 0)
		rand = 0;
	else if (ft_strcmp(datas[0], "coo:") == 0)
		cube->o = get_coo(datas, 2);
	else if (ft_strcmp(datas[0], "color:") == 0)
		cube->color = get_color(datas);
	else if (ft_strcmp(datas[0], "norm:") == 0)
		cube->dir = get_coo(datas, 6);
	else if (ft_strcmp(datas[0], "rot:") == 0)
		cube->rot = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "shine:") == 0)
		cube->shine = get_radius(datas);
	else if (ft_strcmp(datas[0], "radius:") == 0)
		cube->radius = get_radius(datas);
	else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
		rand = 0;
	else
		ft_bad_arg(5);
}

int			ft_add_cube(int fd, t_rt *rt, int id)
{
	int			ret;
	char		*line;
	char		**datas;
	t_cube		*cube;

	cube = ini_cube();
	cube->id = id;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		ft_cube_line(datas, fd, rt, cube);
		ft_freetab(datas);
		free(line);
	}
	return (cube_lst(rt, cube));
}
