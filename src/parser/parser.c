/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 17:50:21 by kboucaud          #+#    #+#             */
/*   Updated: 2017/11/02 17:50:23 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int			check_object_name_1(char *str, int fd, t_rt *rt, int id)
{
	if (str[0] == 0)
		return (0);
	else if (ft_strcmp(str, "plane") == 0)
		return (ft_add_plane(fd, rt, id));
	else if (ft_strcmp(str, "sphere") == 0)
		return (ft_add_sphere(fd, rt, id));
	else if (ft_strcmp(str, "cone") == 0)
		return (ft_add_cone(fd, rt, id));
	else if (ft_strcmp(str, "cylinder") == 0)
		return (ft_add_cylinder(fd, rt, id));
	else if (ft_strcmp(str, "cube") == 0)
		return (ft_add_cube(fd, rt, id));
	else if (ft_strcmp(str, "ellipse") == 0)
		return (ft_add_ellipse(fd, rt, id));
	else if (ft_strcmp(str, "parabol") == 0)
		return (ft_add_parabol(fd, rt, id));
	return (0);
}

int			check_object_name_2(char *str, int fd, t_rt *rt, int id)
{
	if (ft_strcmp(str, "tore") == 0)
		return (ft_add_tore(fd, rt, id++));
	else if (ft_strcmp(str, "camera") == 0)
		return (ft_add_cam(fd, rt));
	else if (ft_strcmp(str, "light") == 0)
		return (ft_add_light(fd, rt, id++));
	else if (ft_strcmp(str, "ambiant") == 0)
		return (light_amb(rt, fd));
	else
		ft_bad_arg(5);
	return (0);
}

int			ft_check_obj(char *str, int fd, t_rt *rt)
{
	static int			id = 0;

	id++;
	if (check_object_name_1(str, fd, rt, id) == 1 ||
	check_object_name_2(str, fd, rt, id) == 1)
		return (1);
	return (0);
}

void		ft_ini_struct(t_rt *rt)
{
	if (!(rt->start = (t_start*)malloc(sizeof(t_start))))
		ft_malloc_error();
	rt->sphere = NULL;
	rt->plane = NULL;
	rt->cone = NULL;
	rt->cylinder = NULL;
	rt->cube = NULL;
	rt->cam = NULL;
	rt->light = NULL;
	rt->ellipse = NULL;
	rt->tore = NULL;
	rt->parabol = NULL;
	rt->start->sph = NULL;
	rt->start->pln = NULL;
	rt->start->con = NULL;
	rt->start->cyl = NULL;
	rt->start->cub = NULL;
	rt->start->lgh = NULL;
	rt->start->ell = NULL;
	rt->start->tor = NULL;
	rt->start->par = NULL;
	rt->amb = AMB;
}

void		parser(t_rt *rt, char *file)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_bad_arg(1);
	ft_ini_struct(rt);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_check_obj(line, fd, rt);
		free(line);
	}
	if (ret == -1)
		ft_bad_arg(-1);
	if (rt->cam == NULL || rt->cam->pos.z < -99)
	{
		ft_putstr("Needs a cam or cam too far\n");
		exit(-1);
	}
	close(fd);
}
