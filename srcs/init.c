/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:41:03 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 14:50:18 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_fract_var(t_disp *d)
{
	if (d->choice == JULIA)
	{
		d->p.xmax = 1.25;
		d->p.xmin = -1.25;
		d->p.ymax = 1.25;
		d->p.ymin = -1.25;
	}
	else if (d->choice == MANDELBROT)
	{
		d->p.xmax = 0.5;
		d->p.xmin = -2;
		d->p.ymax = 1.25;
		d->p.ymin = -1.25;
	}
	else if (d->choice == BURNINGSHIP)
	{
		d->p.xmax = 0.5;
		d->p.xmin = -2;
		d->p.ymax = 1.25;
		d->p.ymin = -1.25;
	}
}

void	init_main_var(t_disp *d)
{
	if (d->choice == JULIA)
		d->lock = 0;
	else
		d->lock = 1;
	d->p.mult = 2;
	d->p.zoom = 0.9;
	d->p.xmax = 0;
	d->p.xmin = 0;
	d->p.ymax = 0;
	d->p.ymin = 0;
	d->p.iter = 50;
	d->p.color_s = 0.01;
	d->p.color_swap = 0;
	d->p.color_b = 0;
	d->p.color_r = 0;
	d->p.color_g = 0;
}

void	init(t_disp *d, int i)
{
	d->mlx = mlx_init();
	if (!d->mlx)
	{
		ft_putstr("Error\n");
		exit(0);
	}
	d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "Fractol ncoursol");
	d->pic = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->img = mlx_get_data_addr(d->pic, &d->bpp, &d->sl, &d->end);
	if (!d->win || !d->pic || !d->img)
	{
		ft_putstr("Error\n");
		exit(0);
	}
	d->choice = i;
	init_main_var(d);
	init_fract_var(d);
	fract_center(d);
}
