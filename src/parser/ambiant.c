/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiant.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 22:38:48 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/25 22:38:49 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

int			light_amb(t_rt *rt, int fd)
{
	int			ret;
	char		*line;
	char		**datas;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		datas = ft_strsplit(line, ' ');
		if (datas[0] == 0)
			ret++;
		if (ft_strcmp(datas[0], "power:") == 0)
		{
			rt->amb = ft_atof(datas[1]);
			if (rt->amb < 0 || rt->amb > 1)
				ft_bad_arg(11);
		}
		else if (datas[1] == NULL && ft_check_obj(datas[0], fd, rt) == 1)
			ret++;
		else
			ft_bad_arg(5);
		ft_freetab(datas);
		free(line);
	}
	return (1);
}
