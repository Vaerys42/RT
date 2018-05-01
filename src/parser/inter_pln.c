/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_pln.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 19:33:05 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/29 19:33:08 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		inter_plane_sphere(t_sphere *sphere, char **datas)
{
	if (sphere->pln == NULL)
	{
		if (!(sphere->pln = (t_plane*)malloc(sizeof(t_plane))))
			ft_malloc_error();
		sphere->pln->o = (t_coo){0, 0, 0};
		sphere->pln->norm = (t_coo){0, 1, 0};
		sphere->pln->color = NULL;
		sphere->pln->cut = 0;
	}
	if (ft_strcmp(datas[0], "plnn:") == 0)
		sphere->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		sphere->pln->color = check_color(sphere->pln->color, datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		sphere->pln->o = get_coo(datas, 7);
}

void		inter_plane_cylinder(t_cylinder *cylinder, char **datas)
{
	if (cylinder->pln == NULL)
	{
		if (!(cylinder->pln = (t_plane*)malloc(sizeof(t_plane))))
			ft_malloc_error();
		cylinder->pln->o = (t_coo){0, 0, 0};
		cylinder->pln->norm = (t_coo){0, 1, 0};
		cylinder->pln->color = NULL;
		cylinder->pln->cut = 0;
	}
	if (ft_strcmp(datas[0], "plnn:") == 0)
		cylinder->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		cylinder->pln->color = check_color(cylinder->pln->color, datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		cylinder->pln->o = get_coo(datas, 7);
}

void		inter_plane_cone(t_cone *cone, char **datas)
{
	if (cone->pln == NULL)
	{
		if (!(cone->pln = (t_plane*)malloc(sizeof(t_plane))))
			ft_malloc_error();
		cone->pln->o = (t_coo){0, 0, 0};
		cone->pln->norm = (t_coo){0, 1, 0};
		cone->pln->color = NULL;
		cone->pln->cut = 0;
	}
	if (ft_strcmp(datas[0], "plnn:") == 0)
		cone->pln->norm = get_coo(datas, 7);
	else if (ft_strcmp(datas[0], "plnc:") == 0)
		cone->pln->color = check_color(cone->pln->color, datas);
	else if (ft_strcmp(datas[0], "plno:") == 0)
		cone->pln->o = get_coo(datas, 7);
}
