/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 01:04:33 by kboucaud          #+#    #+#             */
/*   Updated: 2017/10/21 01:09:43 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		ft_create(t_rt *rt)
{
	if (!(rt->data = (t_data*)malloc(sizeof(t_data))))
		ft_malloc_error();
	if (!(rt->data->mlx = mlx_init()))
		ft_exit();
	if (!(rt->data->mlx_window = mlx_new_window(rt->data->mlx,
	WIN_LEN, WIN_HEIGHT, "RTV1")))
		ft_exit();
	if (!(rt->data->mlx_image = mlx_new_image(rt->data->mlx,
	WIN_LEN, WIN_HEIGHT)))
		ft_exit();
	if (!(rt->data->image_string = mlx_get_data_addr(rt->data->mlx_image,
	&rt->data->bpp, &rt->data->s_l, &rt->data->endian)))
		ft_exit();
	rt->data->image_int = (int*)(rt->data->image_string);
}

void		window(t_rt *rt)
{
	mlx_hook(rt->data->mlx_window, 2, 1L << 0, my_key_press, rt);
	mlx_hook(rt->data->mlx_window, 17, 0, ft_exit_cross, rt);
	mlx_loop(rt->data->mlx);
}

int			main(int argc, char **argv)
{
	t_rt		*rt;

	if (argc != 2)
		ft_bad_arg(0);
	if (!(rt = (t_rt*)malloc(sizeof(t_rt))))
		ft_malloc_error();
	parser(rt, argv[1]);
	ft_ini(rt);
	if (rt->light != NULL)
	{
		ft_raytracing(rt);
	}
	mlx_put_image_to_window(rt->data->mlx, rt->data->mlx_window,
	rt->data->mlx_image, 0, 0);
	window(rt);
	return (0);
}
