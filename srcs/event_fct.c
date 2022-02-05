/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:38:43 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 13:40:46 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	iter(t_disp *d, int key)
{
	if (key == PLUS)
		d->p.iter += 2;
	if (key == MINUS)
		d->p.iter -= 2;
	threads(d);
}

void	move(t_disp *d, int key)
{
	double	totalx;
	double	totaly;
	double	move;

	if (key == UP || key == DOWN)
	{
		totaly = dist_btw_two_pts(d->p.ymax, 0, d->p.ymin, 0);
		if (key == UP)
			move = (totaly / 10) * 1;
		else
			move = (totaly / 10) * -1;
		d->p.ymax = move + d->p.ymax;
		d->p.ymin = move + d->p.ymin;
	}
	else if (key == LEFT || key == RIGHT)
	{
		totalx = dist_btw_two_pts(d->p.xmax, 0, d->p.xmin, 0);
		if (key == LEFT)
			move = (totalx / 10) * -1;
		else
			move = (totalx / 10) * 1;
		d->p.xmax = move + d->p.xmax;
		d->p.xmin = move + d->p.xmin;
	}
	threads(d);
}

void	change_coloring(t_disp *d, int key)
{
	if (key == W)
		d->p.color_s += 0.002;
	else if (key == A)
		d->p.color_swap++;
	else if (key == S)
		d->p.color_s -= 0.002;
	else if (key == D)
		d->p.color_swap--;
	else if (key == R)
		d->p.color_r += 4;
	else if (key == G)
		d->p.color_g += 4;
	else if (key == B)
		d->p.color_b += 4;
	threads(d);
}
