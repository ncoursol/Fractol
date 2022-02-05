/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:38:31 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 14:50:09 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	mouse_move(int x, int y, t_disp *d)
{
	if (d->choice == JULIA && d->lock == 0)
	{
		d->p.x = 2 * (double)x / WIDTH - 1;
		d->p.y = 2 * (double)y / HEIGHT - 1;
		threads(d);
	}
	return (0);
}

void	key_press2(int key, t_disp *d)
{
	if ((d->choice == MANDELBROT) && (key == Z || key == X))
	{
		if (key == Z && d->p.mult < 20)
		{
			d->p.mult++;
			threads(d);
		}
		else if (key == X && d->p.mult > 2)
		{
			d->p.mult--;
			threads(d);
		}
	}
	else if (key == Q || key == E)
	{
		d->p.iter = 50;
		if (d->choice > 1 && key == Q)
			d->choice--;
		if (d->choice < 3 && key == E)
			d->choice++;
		init_main_var(d);
		init_fract_var(d);
		fract_center(d);
		threads(d);
	}
}

int	key_press(int key, t_disp *d)
{
	if (key == ESC)
		end_program(d);
	else if (key == R || key == G || key == B
		|| key == W || key == A || key == S || key == D)
		change_coloring(d, key);
	else if (key == SPACE)
		d->lock = !d->lock;
	else if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
		move(d, key);
	else if ((key == PLUS || key == MINUS) && d->lock == 1)
		iter(d, key);
	key_press2(key, d);
	return (0);
}

void	wheel_down(t_disp *d, int x, int y)
{
	double	ratio_x;
	double	ratio_y;
	double	frac_width;
	double	frac_height;

	ratio_x = (int)(((double)x / WIDTH) * 100);
	ratio_y = (int)(((double)y / HEIGHT) * 100);
	frac_width = dist_btw_two_pts(0, d->p.xmax, 0, d->p.xmin);
	frac_height = dist_btw_two_pts(0, d->p.ymax, 0, d->p.ymin);
	d->p.xmax += -(frac_width * d->p.zoom * ratio_x)
		/ 200 + frac_width / 2;
	d->p.xmin -= -(frac_width * d->p.zoom * (100 - ratio_x))
		/ 200 + frac_width / 2;
	d->p.ymax += -(frac_height * d->p.zoom * (100 - ratio_y))
		/ 200 + frac_height / 2;
	d->p.ymin -= -(frac_height * d->p.zoom * ratio_y)
		/ 200 + frac_height / 2;
	threads(d);
}

int	mouse_press(int key, int x, int y, t_disp *d)
{
	double	ratio_x;
	double	ratio_y;
	double	frac_width;
	double	frac_height;

	if (key == WHEELUP)
	{
		ratio_x = (int)(((double)x / WIDTH) * 100);
		ratio_y = (int)(((double)y / HEIGHT) * 100);
		frac_width = dist_btw_two_pts(0, d->p.xmax, 0, d->p.xmin);
		frac_height = dist_btw_two_pts(0, d->p.ymax, 0, d->p.ymin);
		d->p.xmax -= -(frac_width * d->p.zoom * ratio_x)
			/ 200 + frac_width / 2;
		d->p.xmin += -(frac_width * d->p.zoom * (100 - ratio_x))
			/ 200 + frac_width / 2;
		d->p.ymax -= -(frac_height * d->p.zoom * (100 - ratio_y))
			/ 200 + frac_height / 2;
		d->p.ymin += -(frac_height * d->p.zoom * ratio_y)
			/ 200 + frac_height / 2;
		threads(d);
	}
	else if (key == WHEELDOWN)
		wheel_down(d, x, y);
	return (0);
}
