/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:12:26 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 14:30:07 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	error_checker(int argc)
{
	if (argc != 2)
	{
		ft_putstr("\nUsage : ./fractol [fractal_name]\n");
		ft_putstr("\t-Mandelbrot\n\t-Julia\n\t-BurningShip\n\n");
		exit(0);
	}
	if (NB_THREAD <= 0 || NB_THREAD > 8)
	{
		ft_putstr("NB_THREAD error\n");
		exit(0);
	}
}

void	clear(t_disp *d)
{
	mlx_destroy_image(d->mlx, d->pic);
	d->pic = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->img = mlx_get_data_addr(d->pic, &d->bpp, &d->sl, &d->end);
}

void	fract_center2(t_disp *d, double l, double t)
{
	t = dist_btw_two_pts(0, d->p.ymax, 0, d->p.ymin);
	l = (HEIGHT * t) / WIDTH;
	if (d->p.ymax < 0)
		d->p.ymax = (fabs(d->p.ymax) + (l - t) / 2) * -1;
	else
		d->p.ymax = (fabs(d->p.ymax) + (l - t) / 2);
	if (d->p.ymin < 0)
		d->p.ymin = (fabs(d->p.ymin) + (l - t) / 2) * -1;
	else
		d->p.ymin = (fabs(d->p.ymin) + (l - t) / 2);
}

void	fract_center(t_disp *d)
{
	double		l;
	double		t;

	if (WIDTH > HEIGHT)
	{
		t = dist_btw_two_pts(0, d->p.xmax, 0, d->p.xmin);
		l = (WIDTH * t) / HEIGHT;
		if (d->p.xmax < 0)
			d->p.xmax = (fabs(d->p.xmax) + (l - t) / 2) * -1;
		else
			d->p.xmax = (fabs(d->p.xmax) + (l - t) / 2);
		if (d->p.xmin < 0)
			d->p.xmin = (fabs(d->p.xmin) + (l - t) / 2) * -1;
		else
			d->p.xmin = (fabs(d->p.xmin) + (l - t) / 2);
	}
	else
		fract_center2(d, l, t);
}
