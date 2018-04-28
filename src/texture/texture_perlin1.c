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

#define SETUP(i,b0,b1,r0,r1) t = vec[i] + N; b0 = ((int)t) & BM; b1 = (b0+1) & BM; r0 = t - (int)t; r1 = r0 - 1.;

double		ft_noise(double vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	int i, j;

	if (start)
	{
		start = 0;
		init();
	}
	SETUP(0, bx0, bx1, rx0, rx1);
	SETUP(1, by0, by1, ry0, ry1);
	SETUP(2, bz0, bz1, rz0, rz1);
	i = p[bx0];
	j = p[bx1];
	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];
	t = S_CURVE(rx0);
	sy = S_CURVE(ry0);
	sz = S_CURVE(rz0);
	q = g3[b00 + bz0];
	u = AT3(rx0, ry0, rz0);
	q = g3[b10 + bz0];
	v = AT3(rx1, ry0, rz0);
	a = lerp(t, u, v);
	q = g3[b01 + bz0];
	u = AT3(rx0, ry1, rz0);
	q = g3[b11 + bz0];
	v = AT3(rx1, ry1, rz0);
	b = lerp(t, u, v);
	c = lerp(sy, a, b);
	q = g3[b00 + bz1];
	u = AT3(rx0, ry0, rz1);
	q = g3[b10 + bz1];
	v = AT3(rx1, ry0, rz1);
	a = lerp(t, u, v);
	q = g3[b01 + bz1];
	u = AT3(rx0, ry1, rz1);
	q = g3[b11 + bz1];
	v = AT3(rx1, ry1, rz1);
	b = lerp(t, u, v);
	d = lerp(sy, a, b);
	return (lerp(sz, c, d));
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
