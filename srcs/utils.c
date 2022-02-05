/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:41:21 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 14:31:18 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	math_fct(double a, double b)
{
	return (log(a * a + b * b));
}

double	dist_btw_two_pts(double xa, double ya, double xb, double yb)
{
	return (sqrt(pow(xb - xa, 2) + pow(yb - ya, 2)));
}

int	redirect(t_disp *d)
{
	if (d->choice == JULIA)
		return (julia(d));
	if (d->choice == MANDELBROT && d->p.mult > 2)
		return (multibrot(d));
	if (d->choice == MANDELBROT)
		return (mandelbrot(d));
	if (d->choice == BURNINGSHIP)
		return (burning_ship(d));
	return (0);
}

int	choice(char **argv)
{
	if (ft_strncmp("Julia", argv[1], 6) == 0)
		return (JULIA);
	else if (ft_strncmp("Mandelbrot", argv[1], 11) == 0)
		return (MANDELBROT);
	else if (ft_strncmp("BurningShip", argv[1], 12) == 0)
		return (BURNINGSHIP);
	else
	{
		ft_putstr("Usage : ./fractol [fractal_name]\n");
		ft_putstr("\t-Mandelbrot\n\t-Julia\n\t-BurningShip\n\n");
		exit(0);
	}
	return (0);
}

void	end_program(t_disp *d)
{
	mlx_destroy_image(d->mlx, d->pic);
	mlx_destroy_window(d->mlx, d->win);
	free(d);
	exit(0);
}
