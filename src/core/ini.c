/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:42 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/30 21:19:45 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void	ft_ini_viewplane(t_rt *rt)
{
	if (!(rt->view = (t_view*)malloc(sizeof(t_view))))
		ft_malloc_error();
	rt->view->height = 35;
	rt->view->length = 50;
	rt->view->up_left = ft_add_vect(rt->cam->pos,
	ft_add_vect(ft_mult_vect(PLN_DST, rt->cam->forw), ft_sub_vect(ft_mult_vect(
	rt->view->height / 2, rt->cam->up), ft_mult_vect(rt->view->length / 2,
	rt->cam->right))));
}

void	ft_ini_cam(t_rt *rt)
{
	rt->cam->forw = ft_new_vect(0, 0, 1);
	rt->cam->up = ft_new_vect(0, 1, 0);
	rt->cam->right = ft_new_vect(1, 0, 0);
	ft_ini_viewplane(rt);
}

void	ft_malloc_ini(t_rt *rt)
{
	ft_create(rt);
	if (!(rt->inter = (t_inter*)malloc(sizeof(t_inter))))
		ft_malloc_error();
	if (!(rt->ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->light_ray = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->inter->angle = (t_ray*)malloc(sizeof(t_ray))))
		ft_malloc_error();
	if (!(rt->inter->mat = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->inter->col = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->inter->lgh = (t_material*)malloc(sizeof(t_material))))
		ft_malloc_error();
	if (!(rt->op = (t_options*)malloc(sizeof(t_options))))
		ft_malloc_error();
	if (!(rt->equa = (t_equa*)malloc(sizeof(t_equa))))
		ft_malloc_error();
}

void	ft_reset(t_rt *rt)
{
	rt->ray->o = rt->cam->pos;
	rt->inter->obj = -1;
	rt->op->max_depth = 5;
}

void	ft_ini(t_rt *rt)
{
	ft_malloc_ini(rt);
	ft_ini_cam(rt);
	ft_reset(rt);
	make_rot(rt);
	rt->op->sepia = 0;
	rt->op->blwh = 0;
	rt->op->maintain = 0;
	rt->maxdepth = 3;
}
