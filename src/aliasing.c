/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliasing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 22:26:16 by kboucaud          #+#    #+#             */
/*   Updated: 2018/03/23 22:26:19 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		put_pxl(t_data *data, int x, int y, t_material *color)
{
	int		i;

	if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	i = (x * 4) + (y * data->s_l);
	if (i > WIN_HEIGHT * WIN_LEN * 4)
		return ;
	data->image_string[i] = color->b;
	data->image_string[++i] = color->g;
	data->image_string[++i] = color->r;
}

void            col(t_rt *rt, int x, int y, char *prev)
{
    int         i;

    if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	i = (x * 4) + (y * rt->data->s_l);
	if (i > WIN_HEIGHT * WIN_LEN * 4)
		return ;
    rt->data->image_string[i] = (prev[i] + prev[i - rt->data->s_l]) / 2;
    i++;
    rt->data->image_string[i] = (prev[i] + prev[i - rt->data->s_l]) / 2;
    i++;
    rt->data->image_string[i] = (prev[i] + prev[i - rt->data->s_l]) / 2;
}

void            line(t_rt *rt, int x, int y, char *prev)
{
    int         i;

    if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	i = (x * 4) + (y * rt->data->s_l);
	if (i > WIN_HEIGHT * WIN_LEN * 4)
		return ;
    rt->data->image_string[i] = (prev[i] + prev[i + 4]) / 2;
    i++;
    rt->data->image_string[i] = (prev[i] + prev[i + 4]) / 2;
    i++;
    rt->data->image_string[i] = (prev[i] + prev[i + 4]) / 2;
}

void            class(t_rt *rt, int x, int y, char *prev)
{
    int         i;

    if (x * 4 >= WIN_LEN * 4 || x * 4 < 0)
		return ;
	i = (x * 4) + (y * rt->data->s_l);
	if (i > WIN_HEIGHT * WIN_LEN * 4)
		return ;
	if (prev[i] - prev[i + 4] > 150)
		rt->data->image_string[i] = prev[i] / 2;
	else if (prev[i + 4] - prev[i] > 150)
		rt->data->image_string[i] = prev[i + 4] / 2;
	i++;
	if (prev[i] - prev[i + 4] > 150)
		rt->data->image_string[i] = prev[i] / 2;
	else if (prev[i + 4] - prev[i] > 150)
		rt->data->image_string[i] = prev[i + 4] / 2;
	i++;
	if (prev[i] - prev[i + 4] > 150)
		rt->data->image_string[i] = prev[i] / 2;
	else if (prev[i + 4] - prev[i] > 150)
		rt->data->image_string[i] = prev[i + 4] / 2;
	return ;
}

void            aliasing(t_rt *rt)
{
    int         x;
    int         y;
    int         random;
    char        *prev;

    y = -1;
    prev = rt->data->image_string;
    while (++y <= WIN_HEIGHT)
	{
		x = -1;
		while (++x <= WIN_LEN)
        {
            if (y == 0 && x == WIN_LEN)
                random = x;
            else if (y == 0)
                line(rt, x, y, prev);
            else if (x == WIN_LEN)
                col(rt, x ,y, prev);
            else
                class(rt, x ,y, prev);
        }
	}
}