/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_perlin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagirard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:08:40 by lagirard          #+#    #+#             */
/*   Updated: 2018/04/28 18:08:45 by lagirard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../rt.h"

#define B 0x100
#define BM 0xff

#define N 0x1000
#define NP 12
#define NM 0xfff

static int p[B + B + 2];
static double g3[B + B + 2][3];
static double g2[B + B + 2][2];
static double g1[B + B + 2];
static int start = 1;

static void init(void);

#define S_CURVE(t) (t * t * (3. - 2. * t))

#define AT3(rx,ry,rz) (rx * q[0] + ry * q[1] + rz * q[2])

double		lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double		ft_noise(double vec[3])
{
	int		b[10];
	double	r[6];
	double	p[9];
	double 	*q;
	int 	i;
	int		j;

	if (start)
	{
		start = 0;
		init();
	}
	p[6] = vec[0] + N;
	b[0] = ((int)p[6]) & BM;
	b[1] = (b[0] + 1) & BM;
	r[0] = p[6] - (int)p[6];
	r[1] = r[0] - 1.;
	p[6] = vec[1] + N;
	b[2] = ((int)p[6]) & BM;
	b[3] = (b[2] + 1) & BM;
	r[2] = p[6] - (int)p[6];
	r[3] = r[2] - 1.;
	p[6] = vec[2] + N;
	b[4] = ((int)p[6]) & BM;
	b[5] = (b[4] + 1) & BM;
	r[4] = p[6] - (int)p[6];
	r[5] = r[4] - 1.;
	i = p[b[0]];
	j = p[b[1]];
	b[6] = p[i + b[2]];
	b[7] = p[j + b[2]];
	b[8] = p[i + b[3]];
	b[9] = p[j + b[3]];
	p[6] = S_CURVE(r[0]);
	p[0] = S_CURVE(r[2]);
	p[1] = S_CURVE(r[4]);
	q = g3[b[6] + b[4]];
	p[7] = AT3(r[0], r[2], r[4]);
	q = g3[b[7] + b[4]];
	p[8] = AT3(r[1], r[2], r[4]);
	p[2] = lerp(p[6], p[7], p[8]);
	q = g3[b[8] + b[4]];
	p[7] = AT3(r[0], r[3], r[4]);
	q = g3[b[9] + b[4]];
	p[8] = AT3(r[1], r[3], r[4]);
	p[3] = lerp(p[6], p[7], p[8]);
	p[4] = lerp(p[0], p[2], p[3]);
	q = g3[b[6] + b[5]];
	p[7] = AT3(r[0], r[2], r[5]);
	q = g3[b[7] + b[5]];
	p[8] = AT3(r[1], r[2], r[5]);
	p[2] = lerp(p[6], p[7], p[8]);
	q = g3[b[8] + b[5]];
	p[7] = AT3(r[0], r[3], r[5]);
	q = g3[b[9] + b[5]];
	p[8] = AT3(r[1], r[3], r[5]);
	p[3] = lerp(p[6], p[7], p[8]);
	p[5] = lerp(p[0], p[2], p[3]);
	return (lerp(p[1], p[4], p[5]));
}

static void	normalize2(double v[2])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

static void	normalize3(double v[3])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

static void	init(void)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < B)
	{
		p[i] = i;
		g1[i] = (double)((random() % (B + B)) - B) / B;
		j = -1;
		while (++j < 2)
			g2[i][j] = (double)((random() % (B + B)) - B) / B;
		normalize2(g2[i]);
		j = -1;
		while (++j < 3)
			g3[i][j] = (double)((random() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}
	while (--i)
	{
		k = p[i];
		j = random() % B;
		p[i] = p[j];
		p[j] = k;
	}
	i = -1;
	while (++i < B + 2)
	{
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		j = -1;
		while (++j < 2)
			g2[B + i][j] = g2[i][j];
		j = -1;
		while (++j < 3)
			g3[B + i][j] = g3[i][j];
	}
}
