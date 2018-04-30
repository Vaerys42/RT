/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_perlin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:08:40 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/30 19:20:18 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

t_perlin			*ft_init(t_perlin *l, double g3[B + B + 2][3])
{
	int				i;
	int				j;
	int				k;

	i = -1;
	while (++i < B)
	{
		l->p[i] = i;
		l = ft_rndm(l, g3, i);
	}
	while (--i)
	{
		k = l->p[i];
		j = random() % B;
		l->p = ft_init_p(l, i, j, k);
	}
	i = -1;
	while (++i < B + 2)
	{
		l->p[B + i] = l->p[i];
		j = -1;
		while (++j < 3)
			g3[B + i][j] = g3[i][j];
	}
	return (l);
}

t_perlin			*ft_q(t_perlin *l, int m, int n, double g3[B + B + 2][3])
{
	double			*q;

	q = g3[l->b[0][m] + l->b_tmp[2][n]];
	l->tab_2[1] = at3(l->r[0][0], l->r[1][m], l->r[2][n], q);
	q = g3[l->b[1][m] + l->b_tmp[2][n]];
	l->tab_2[2] = at3(l->r[0][1], l->r[1][m], l->r[2][n], q);
	return (l);
}

double				*ft_q_all(t_perlin *l, double sy, double g3[B + B + 2][3])
{
	double			*tab;

	if (!(tab = (double *)malloc(sizeof(double) * 4)))
		return (NULL);
	l = ft_q(l, 0, 0, g3);
	tab[0] = lerp(l->tab_2[0], l->tab_2[1], l->tab_2[2]);
	l = ft_q(l, 1, 0, g3);
	tab[1] = lerp(l->tab_2[0], l->tab_2[1], l->tab_2[2]);
	tab[2] = lerp(sy, tab[0], tab[1]);
	l = ft_q(l, 0, 1, g3);
	tab[0] = lerp(l->tab_2[0], l->tab_2[1], l->tab_2[2]);
	l = ft_q(l, 1, 1, g3);
	tab[1] = lerp(l->tab_2[0], l->tab_2[1], l->tab_2[2]);
	tab[3] = lerp(sy, tab[0], tab[1]);
	return (tab);
}

int					**ft_b(t_perlin *l)
{
	int				**b;

	if ((b = (int **)malloc(sizeof(int *) * 2)) == NULL)
		return (NULL);
	if ((b[0] = (int *)malloc(sizeof(int) * 2)) == NULL)
		return (NULL);
	if ((b[1] = (int *)malloc(sizeof(int) * 2)) == NULL)
		return (NULL);
	b[0][0] = l->p[l->p[l->b_tmp[0][0]] + l->b_tmp[1][0]];
	b[1][0] = l->p[l->p[l->b_tmp[0][1]] + l->b_tmp[1][0]];
	b[0][1] = l->p[l->p[l->b_tmp[0][0]] + l->b_tmp[1][1]];
	b[1][1] = l->p[l->p[l->b_tmp[0][1]] + l->b_tmp[1][1]];
	return (b);
}

double				ft_noise(double vec[3])
{
	t_perlin		*l;
	static int		start = 1;
	static int		p[B + B + 2];
	static double	g3[B + B + 2][3];

	if ((l = (t_perlin *)malloc(sizeof(t_perlin) * 1)) == NULL)
		return (1);
	l->p = p;
	if (start)
	{
		start = 0;
		l = ft_init(l, g3);
	}
	l = ft_setup(l, vec);
	l->b = ft_b(l);
	l->tab_2[0] = s_curve(l->r[0][0]);
	if ((l->tab = ft_q_all(l, s_curve(l->r[1][0]), g3)) == NULL)
		return (0);
	ft_free_bl(l, l->b);
	return (ft_lerp(s_curve(l->r[2][0]), l->tab));
}
