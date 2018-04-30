/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infos2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 17:27:51 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/30 17:27:54 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void		ft_plane_info(t_plane *plane)
{
	if (plane->color == NULL)
		ft_putstr("Needs color for plane (0 to 1). Ex : color: 1 0 1\n");
	else
		return ;
	exit(-1);
}
