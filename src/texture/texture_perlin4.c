/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_perlin4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:08:40 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/30 19:20:05 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

void			ft_free_bl(t_perlin *l, int **b)
{
	if (l)
		free(l);
	if (b)
	{
		if (b[0])
			free(b[0]);
		if (b[1])
			free(b[1]);
		free(b);
	}
}

double			ft_lerp(double s1, double *tab)
{
	double		n;

	n = lerp(s1, tab[2], tab[3]);
	free(tab);
	return (n);
}

t_perlin		*ft_rndm(t_perlin *l, double g3[B + B + 2][3], int i)
{
	int			j;

	j = -1;
	while (++j < 3)
		g3[i][j] = (double)((random() % (B + B)) - B) / B;
	return (l);
}

int				*ft_init_p(t_perlin *l, int i, int j, int k)
{
	l->p[i] = l->p[j];
	l->p[j] = k;
	return (l->p);
}
