/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:41:11 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 14:45:43 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	color(t_disp *d, int n)
{
	int			i;
	int			c;

	i = ((d->screen.x * (d->bpp / 8)) + (d->screen.y * d->sl));
	if (n == d->p.iter)
	{
		d->img[i] = 0x00;
		d->img[i + 1] = 0x00;
		d->img[i + 2] = 0x00;
		d->img[i + 3] = 0x00;
	}
	else
	{
		c = -(log(math_fct(d->p.xn, d->p.yn)) / log(2)) + n + d->p.color_swap;
		d->img[i] = sin(d->p.color_s * (c + d->p.color_b)) * 127.5 + 127.5;
		d->img[i + 1] = sin(d->p.color_s * (c + d->p.color_g)) * 127.5 + 127.5;
		d->img[i + 2] = sin(d->p.color_s * (c + d->p.color_r)) * 127.5 + 127.5;
		d->img[i + 3] = 0x00;
	}
}

void	draw(t_disp *d)
{
	int		end;

	end = 0;
	if (NB_THREAD > 0)
	{
		end = ((d->nb + 1) * HEIGHT) / NB_THREAD;
		d->screen.y = (HEIGHT / NB_THREAD) * d->nb;
	}
	while (d->screen.y < end)
	{
		d->screen.x = 0;
		while (d->screen.x < WIDTH)
		{
			color(d, redirect(d));
			d->screen.x += 1;
		}
		d->screen.y += 1;
	}
}

void	threads(t_disp *d)
{
	int		i;

	i = 0;
	clear(d);
	mlx_put_image_to_window(d[0].mlx, d[0].win, d[0].pic, 0, 0);
	while (i < NB_THREAD)
	{
		if (i != 0)
			d[i] = d[i - 1];
		d[i].nb = i;
		pthread_create(&d[i].th, NULL, (void *)draw, &d[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(d[i].th, NULL);
		i++;
	}
	mlx_put_image_to_window(d[0].mlx, d[0].win, d[0].pic, 0, 0);
}

int	main(int argc, char **argv)
{
	t_disp		*d;
	int			i;

	error_checker(argc);
	i = choice(argv);
	if (i != 0)
	{
		d = (t_disp *)malloc(sizeof(t_disp) * NB_THREAD);
		if (!d)
		{
			ft_putstr("malloc error\n");
			exit(0);
		}
		init(&d[0], i);
		threads(d);
		mlx_hook(d[0].win, 2, 1, key_press, &d[0]);
		mlx_hook(d[0].win, 4, 1L << 2, mouse_press, &d[0]);
		mlx_hook(d[0].win, 6, 1L << 6, mouse_move, &d[0]);
		mlx_loop(d[0].mlx);
	}
	return (0);
}
