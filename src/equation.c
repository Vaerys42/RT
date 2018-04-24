/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 14:21:20 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/09 14:21:23 by kboucaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

double		sqrt3(double a)
{
	if (a < 0)
		return(-pow(-a, 1.0 / 3));
	return(pow(a, 1.0 / 3));
}

double		disc_eq(double t1, double t2)
{
	if (t1 > t2 && t2 > 0)
		return (t2);
	return (t1);
}

double		ft_inter_plane_obj(t_plane *pln, double dc, double t, double t1, double t2)
{
	if (dc >= 0)
	{
		if (t > t1 && t < t2)
			t2 = t;
		if (t < t1)
			return (0);
	}
	else
	{
		if (t > t1 && t < t2)
		{
			pln->cut = 1;
			t1 = t;
		}
		if (t > t2)
			return (0);
	}
	if (t1 > t2)
		return (0);
	return (t1);
}

double		ft_inter_plane_ini(t_ray *ray, t_plane *pln, double t1, double t2)
{
	double		t;
	double		dc;
	double		dw;

	dc = scal(ray->dir, pln->norm);
	dw = scal(ft_sub_vect(ray->o, pln->o), pln->norm);
	t = -dw / dc;
	if (dc == 0 && dw > 0)
		return (0);
	return (ft_inter_plane_obj(pln, dc, t, t1, t2));
}

void		ft_equa2(t_equa *equa, double a, double b, double c)
{
    double      delta;

	delta = b * b - (4 * a * c);
    if (a == 0)
    {
        equa->x[0] = - c / b;
    }
	if (delta == 0)
	{
        equa->x[0] = - b / ( 2 * a);
    }
	if (delta > 0)
	{
        equa->x[0] = (- b - sqrt(delta)) / (2 * a);
        equa->x[1] = (- b + sqrt(delta)) / (2 * a);
    }
    if (delta < 0)
	{
       equa->x[0] = (- b - I * sqrt(- delta)) / (2 * a);
       equa->x[1] = (- b + I * sqrt(- delta)) / (2 * a);
    }
}

void		ft_equa3(t_rt *rt, double a, double b, double c, double d)
{
    double      p;
    double      q;
    double      delta;
	int			k;
	_Complex double	j;
	_Complex double	j2;
	//printf("a %f b %f c %f d %f\n", a, b, c, d);
	p = c / a - (b * b) / (3 * a * a);
	q = (b / (27 * a)) * ((2 * b * b) / (a * a) - (9 * c) / a) + d / a;
	if (p == 0 && q == 0)
		rt->equa->x[0] = -b / (3 * a);
	else if (p == 0 && q != 0)
		rt->equa->x[0] = -q;
	delta = -(27 * q * q + 4 * p * p * p);
	j = cexp(2 * I * M_PI / 3);
	j2 = cexp(4 * I * M_PI / 3);
	k = 0;
	if (delta < 0)
	{
		rt->equa->u[0] = sqrt3((-q + sqrt(-delta / 27)) / 2);
		rt->equa->v[0] = sqrt3((-q - sqrt(-delta / 27)) / 2);
		rt->equa->u[1] = j * sqrt3((-q + sqrt(-delta / 27)) / 2);
		rt->equa->v[1] = j * sqrt3((-q - sqrt(-delta / 27)) / 2);
		rt->equa->u[2] = j2 * sqrt3((-q + sqrt(-delta / 27)) / 2);
		rt->equa->v[2] = j2 * sqrt3((-q - sqrt(-delta / 27)) / 2);
		rt->equa->x[0] = rt->equa->u[0] + rt->equa->v[0] - b / (3 * a);
		rt->equa->x[1] = rt->equa->u[1] + rt->equa->v[2] - b / (3 * a);
		rt->equa->x[2] = rt->equa->u[2] + rt->equa->v[1] - b / (3 * a);
	}
	if (delta == 0)
	{
		rt->equa->x[0] = 2 * sqrt3(-q / 2) - b / (3 * a);
		rt->equa->x[1] = sqrt3(q / 2) - b / (3 * a);
		rt->equa->x[2] = rt->equa->x[1];
	}
	if (delta > 0)
	{
		rt->equa->x[0] = 2 * sqrt(-p / 3) * cos(acos((3 * q / (2 * p)) * sqrt(-3 / p)) / 3) - b / (3 * a);
		rt->equa->x[1] = 2 * sqrt(-p / 3) * cos((acos((3 * q / (2 * p)) * sqrt(-3 / p)) + 2 * M_PI) / 3) - b / (3 * a);
		rt->equa->x[2] = 2 * sqrt(-p / 3) * cos((acos((3 * q / (2 * p)) * sqrt(-3 / p)) + 4 * M_PI) / 3) - b / (3 * a);
	}
	//printf("xo %f i%f x1 %f i%f x2 %f i%f \n", creal(rt->equa->x[0]), cimag(rt->equa->x[0]),  creal(rt->equa->x[1]), cimag(rt->equa->x[1]),  creal(rt->equa->x[2]), cimag(rt->equa->x[2]));
}

double      ft_real(t_equa *equa)
{
    double      y;

	y = MAX;
    if (cimag(equa->x[0]) == 0)
        y = equa->x[0];
    else if (cimag(equa->x[1]) == 0)
        y = equa->x[1];
    else if (cimag(equa->x[2]) == 0 )
        y = equa->x[2];
	else
	{
		equa->x[0] = MAX;
		equa->x[1] = MAX;
		equa->x[2] = MAX;
		equa->x[3] = MAX;
	}
	//printf("xo %f + i%f x1 %f + i%f x2 %f + i%f\n", creal(equa->x[0]), cimag(equa->x[0]), creal(equa->x[1]), cimag(equa->x[1]), creal(equa->x[2]), cimag(equa->x[2]));
	return (y);
}

void		ft_ini_equa4(t_rt *rt)
{
	rt->equa->a[0] = rt->equa->ini[0] / rt->equa->ini[0];
    rt->equa->a[1] = rt->equa->ini[1] / rt->equa->ini[0];
    rt->equa->a[2] = rt->equa->ini[2] / rt->equa->ini[0];
    rt->equa->a[3] = rt->equa->ini[3] / rt->equa->ini[0];
    rt->equa->a[4] = rt->equa->ini[4] / rt->equa->ini[0];
	//printf("xo %f + i%f x1 %f + i%f x2 %f + i%f x3 %f + i%f x4 %f + i %f\n", creal(rt->equa->a[0]), cimag(rt->equa->a[0]), creal(rt->equa->a[1]), cimag(rt->equa->a[1]), creal(rt->equa->a[2]), cimag(rt->equa->a[2]), creal(rt->equa->a[3]), cimag(rt->equa->a[3]), creal(rt->equa->a[4]), cimag(rt->equa->a[4]));
}
void		ft_equa4(t_rt *rt)
{
    double              p;
    double              q;
    double              r;
    double     			y;
	_Complex	double	a0;
	double				b0;

	ft_ini_equa4(rt);
    if( rt->equa->a[0] == 0)
    {
    	rt->equa->x[3] = 0;
	    ft_equa3(rt,rt->equa->a[0], rt->equa->a[1], rt->equa->a[2], rt->equa->a[3]);
    }
	else
    {
		p = -3 * pow(rt->equa->a[1], 2) / (8 * pow(rt->equa->a[0], 2)) + rt->equa->a[2] / rt->equa->a[0];
		q = pow(rt->equa->a[1] / 2, 3) / pow(rt->equa->a[0], 3) - (0.5 * rt->equa->a[1] * rt->equa->a[2]) / pow(rt->equa->a[0], 2) + rt->equa->a[3] / rt->equa->a[0];
		r = -3 * pow((rt->equa->a[1] / 4) / rt->equa->a[0], 4) + rt->equa->a[2] * (pow(rt->equa->a[1] / 4, 2) / pow(rt->equa->a[0], 3)) - (rt->equa->a[1] * rt->equa->a[3] / 4) / pow(rt->equa->a[0], 2) + rt->equa->a[4] / rt->equa->a[0];
		//printf("p %f, q %f, r %f\n", p, q, r);
		ft_equa3(rt, 8, -4 * p, -8 * r, 4 * r * p - (q * q));
		y = ft_real(rt->equa);
		//printf("y%f\n", y);
		if (y == MAX)
			return;
		//printf("y %f\n", 2 * y - p);
		if (-p + 2 * y > 0)
			a0 = sqrt(-p + 2 * y);
		else
			a0 = I * sqrt(p - 2 *y);
		if (2 * y - p == 0)
			b0 = sqrt(y * y - r);
		else
			b0 = - q / (2 * a0);
		ft_equa2(rt->equa, 1, a0, y + b0);
		rt->equa->x[2] = rt->equa->x[0] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
		rt->equa->x[3] = rt->equa->x[1] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
		ft_equa2(rt->equa, 1, -a0, y - b0);
		rt->equa->x[0] = rt->equa->x[0] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
		rt->equa->x[1] = rt->equa->x[1] - rt->equa->ini[1] / (4 * rt->equa->ini[0]);
		if (cimag(rt->equa->x[0]) != 0)
        	rt->equa->x[0] = MAX;
		if (cimag(rt->equa->x[1]) != 0)
        	rt->equa->x[1] = MAX;
		if (cimag(rt->equa->x[2]) != 0)
        	rt->equa->x[2] = MAX;
		if (cimag(rt->equa->x[3]) != 0)
        	rt->equa->x[3] = MAX;
	}
}