/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:40:59 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/10 13:41:00 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		move_object(t_rt *rt, int x, int y)
{
	rt->ray->o.x = rt->view->length / x;
	rt->ray->o.y = rt->view->height / y;
	rt->ray->o.z = rt->cam->pos.z;
	rt->ray->dir = (t_coo){0, 0, 1};
	rt->inter->obj = 0;
	check_forms(rt, 0);
	printf("Actual coordinates %f %f %f\n", rt->ray->o.x, rt->ray->o.y, rt->ray->o.z);
	printf("Hit obj %d\n", rt->inter->obj);
	ft_reset(rt);
}
