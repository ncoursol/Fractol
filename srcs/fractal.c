/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:40:55 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 13:40:57 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	burning_ship(t_disp *d)
{
	int		n;
	double	tmp_x;
	int		p;

	d->p.x = (d->screen.x * (d->p.xmax - d->p.xmin) / WIDTH + d->p.xmin);
	d->p.y = (d->screen.y * (d->p.ymin - d->p.ymax) / HEIGHT + d->p.ymax);
	p = dist_btw_two_pts(1 / 4, d->p.y, d->p.x, d->p.y);
	if ((d->p.x >= p - 2 * (p * p) + 1 / 4)
		|| (pow(d->p.x + 1, 2) + d->p.y * d->p.y >= 1 / 16))
	{
		d->p.xn = 0;
		d->p.yn = 0;
		n = 0;
		while ((d->p.xn * d->p.xn + d->p.yn * d->p.yn) <= 4 && n < d->p.iter)
		{
			tmp_x = d->p.xn;
			d->p.xn = tmp_x * tmp_x - d->p.yn * d->p.yn - d->p.x;
			d->p.yn = 2 * fabs(tmp_x * d->p.yn) - d->p.y;
			n++;
		}
	}
	else
		n = d->p.iter;
	return (n);
}

int	mandelbrot(t_disp *d)
{
	int		n;
	double	tmp_x;
	int		p;

	d->p.x = (d->screen.x * (d->p.xmax - d->p.xmin) / WIDTH + d->p.xmin);
	d->p.y = (d->screen.y * (d->p.ymin - d->p.ymax) / HEIGHT + d->p.ymax);
	p = dist_btw_two_pts(1 / 4, d->p.y, d->p.x, d->p.y);
	if ((d->p.x >= p - 2 * (p * p) + 1 / 4)
		|| (pow(d->p.x + 1, 2) + d->p.y * d->p.y >= 1 / 16))
	{
		d->p.xn = 0;
		d->p.yn = 0;
		n = 0;
		while ((d->p.xn * d->p.xn + d->p.yn * d->p.yn) <= 4 && n < d->p.iter)
		{
			tmp_x = d->p.xn;
			d->p.xn = tmp_x * tmp_x - d->p.yn * d->p.yn + d->p.x;
			d->p.yn = 2 * tmp_x * d->p.yn + d->p.y;
			n++;
		}
	}
	else
		n = d->p.iter;
	return (n);
}

int	multibrot(t_disp *d)
{
	int		n;
	double	tmp_x;

	d->p.x = (d->screen.x * (d->p.xmax - d->p.xmin) / WIDTH + d->p.xmin);
	d->p.y = (d->screen.y * (d->p.ymin - d->p.ymax) / HEIGHT + d->p.ymax);
	d->p.xn = 0;
	d->p.yn = 0;
	n = 0;
	while ((d->p.xn * d->p.xn + d->p.yn * d->p.yn) <= 4 && n < d->p.iter)
	{
		tmp_x = d->p.xn;
		d->p.xn = pow((tmp_x * tmp_x + d->p.yn * d->p.yn), d->p.mult / 2)
			* cos(d->p.mult * atan2(d->p.yn, tmp_x)) + d->p.x;
		d->p.yn = pow((tmp_x * tmp_x + d->p.yn * d->p.yn), d->p.mult / 2)
			* sin(d->p.mult * atan2(d->p.yn, tmp_x)) + d->p.y;
		n++;
	}
	return (n);
}

int	julia(t_disp *d)
{
	int		n;
	double	tmp_x;

	d->p.xn = (d->screen.x * (d->p.xmax - d->p.xmin) / WIDTH + d->p.xmin);
	d->p.yn = (d->screen.y * (d->p.ymin - d->p.ymax) / HEIGHT + d->p.ymax);
	n = 0;
	while ((d->p.xn * d->p.xn + d->p.yn * d->p.yn) <= 4 && n < d->p.iter)
	{
		tmp_x = d->p.xn;
		d->p.xn = tmp_x * tmp_x - d->p.yn * d->p.yn + d->p.x;
		d->p.yn = 2 * tmp_x * d->p.yn + d->p.y;
		n++;
	}
	return (n);
}
