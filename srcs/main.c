#include "../includes/fractol.h"

void	end_program(t_disp *d)
{
	mlx_destroy_image(d->mlx, d->pic);
	mlx_destroy_window(d->mlx, d->win);
	exit(0);
}

void	menu()
{

}

int		choice(char **argv)
{
	if (ft_strncmp("Julia", argv[1], 6) == 0)
		return (JULIA);
	else if (ft_strncmp("Mandelbrot", argv[1], 11) == 0)
		return (MANDELBROT);
	else
		exit(printf("Usage : ./fractol [fractal_name]\n"));
	return (0);
}

void	init_var(t_disp *d, int i)
{
	double		l;
	double		t;

	if (!(d->mlx = mlx_init()))
		exit(printf("Error\n"));
	if (!(d->win = mlx_new_window(d->mlx, WIDTH, HEIGHT, "Fractol ncoursol"))
		|| !(d->pic = mlx_new_image(d->mlx, WIDTH, HEIGHT))
		|| !(d->img = mlx_get_data_addr(d->pic, &d->bpp, &d->sl, &d->end)))
		exit(printf("Error\n"));
	d->choice = i;
	d->lock = 1;
	d->p.mult = 2;
	d->p.zoom = 1;
	d->p.xmax = 0;
	d->p.xmin = 0;
	d->p.ymax = 0;
	d->p.ymin = 0;
	d->p.move_x = 0;
	d->p.move_y = 0;
	d->p.iter = 50;
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
	if (WIDTH > HEIGHT)
	{
		t = fabs(d->p.xmax) + fabs(d->p.xmin);
		l = (WIDTH * t) / HEIGHT;
		d->p.xmax = (fabs(d->p.xmax) + (l - t) / 2) * (d->p.xmax < 0 ? -1 : 1);
		d->p.xmin = (fabs(d->p.xmin) + (l - t) / 2) * (d->p.xmin < 0 ? -1 : 1);
	}
	else
	{
		t = fabs(d->p.ymax) + fabs(d->p.ymin);
		l = (HEIGHT * t) / WIDTH;
		d->p.ymax = (fabs(d->p.ymax) + (l - t) / 2) * (d->p.ymax < 0 ? -1 : 1);
		d->p.ymin = (fabs(d->p.ymin) + (l - t) / 2) * (d->p.ymin < 0 ? -1 : 1);
	}
}

double	mathFct(double a, double b)
{
	return (log(a * a + b * b));
}


int		mandelbrot(t_disp *d)
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
		d->p.xn = tmp_x * tmp_x - d->p.yn * d->p.yn + d->p.x;
		d->p.yn = 2 * tmp_x * d->p.yn + d->p.y;
		n++;
	}
	return (n);
}

int		multibrot(t_disp *d)
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
		d->p.xn = pow((tmp_x * tmp_x + d->p.yn * d->p.yn), d->p.mult / 2) * cos(d->p.mult * atan2(d->p.yn, tmp_x)) + d->p.x;
		d->p.yn = pow((tmp_x * tmp_x + d->p.yn * d->p.yn), d->p.mult / 2) * sin(d->p.mult * atan2(d->p.yn, tmp_x)) + d->p.y;
		n++;
	}
	return (n);
}

int		julia(t_disp *d)
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

int		redirect(t_disp *d)
{
	if (d->choice == JULIA)
		return(julia(d));
	if (d->choice == MANDELBROT)
		return (mandelbrot(d));
	return (0);
}

void	color(t_disp *d, int n)
{
	int			i;
	double		c;

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
		c = -(log(mathFct(d->p.xn, d->p.yn)) / log(2)) + n + 1;
		d->img[i] = (int)(c * 3) % 256;
		d->img[i + 1] = (int)(c * 2) % 256;
		d->img[i + 2] = (int)(c * 1) % 256;
		d->img[i + 3] = 0xFF;
	}
}

void	fract_var(t_disp *d)
{
	d->p.xmax = (d->p.move_x + d->p.xmax) * d->p.zoom;
	d->p.xmin = (d->p.move_x + d->p.xmin) * d->p.zoom;
	d->p.ymax = (d->p.move_y + d->p.ymax) * d->p.zoom;
	d->p.ymin = (d->p.move_y + d->p.ymin) * d->p.zoom;

}

void	draw(t_disp *d)
{
	int		end;

	end = ((d->nb + 1) * HEIGHT) / NB_THREAD;
	d->screen.y = (HEIGHT / NB_THREAD) * d->nb;
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

void	clear(t_disp *d)
{
	mlx_destroy_image(d->mlx, d->pic);
	d->pic = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	d->img = mlx_get_data_addr(d->pic, &d->bpp, &d->sl, &d->end);
}

void	threads(t_disp *d)
{
	int		i;

	i = 0;
	clear(d);
	fract_var(d);
	while (i < NB_THREAD)
	{
		if (i != 0)
			d[i] = d[i - 1];
		d[i].nb = i;
		pthread_create(&d[i].th, NULL, (void*)draw, &d[i]);
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		pthread_join(d[i].th, NULL);
		i++;
	}
	if (NB_THREAD == 0)
		draw(d);
	mlx_put_image_to_window(d[0].mlx, d[0].win, d[0].pic, 0, 0);
}

void	iter(t_disp *d, int key)
{
	if (key == PLUS)
		d->p.iter += 2;
	if (key == MINUS)
		d->p.iter -= 2;
	threads(d);
}

void	move(t_disp *d, int key, int x, int y)
{
	double		totalx;
	double		totaly;
	
	totalx = fabs(d->p.xmax) + fabs(d->p.xmin);
	totaly = fabs(d->p.ymax) + fabs(d->p.ymin);
	if (key == UP || key == DOWN)
	{
		d->p.move_y += (totaly / 10) * (key == UP ? 1 : -1);
		threads(d);
	}
	else if (key == LEFT || key == RIGHT)
	{
		d->p.move_x += (totalx / 10) * (key == LEFT ? -1 : 1);
		threads(d);
	}
	else
	{
		if (x <= WIDTH / 2)
			d->p.move_x += ((WIDTH / 2) - x);
		else
			d->p.move_x += x;
		if (y <= HEIGHT / 2)
			d->p.move_y += y;
		else
			d->p.move_y += ((HEIGHT / 2) - y);
	}
}

int		mouse_move(int x, int y, t_disp *d)
{
	if (d->lock == 0)
		d->count++;
	if (d->choice == JULIA && d->lock == 0 && d->count >= 10)
	{
		d->count = 0;
		d->p.x = 2 * (double)x / WIDTH - 1;
		d->p.y = 2 * (double)y / HEIGHT - 1;
		threads(d);
	}
	return (0);
}

void	anime(int key, t_disp *d)
{
	if ((key == W && d->p.mult < 7) || (key == X && d->p.mult > 2))
	{
		d->p.mult += key == W ? 1 : -1;
		threads(d);
	}
}

int		key_press(int key, t_disp *d)
{
	if (key == ESC)
		end_program(d);
	else if (key == TAB)
		menu(d);
	else if (key == SPACE)
		d->lock = (d->lock == 1 ? 0 : 1);
	else if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
		move(d, key, 0, 0);
	else if ((key == PLUS || key == MINUS) && d->lock == 1)
		iter(d, key);
	else if (key == A || key == E)
	{
		d->p.iter = 50;
		d->p.move_y = 0;
		d->p.move_y = 0;
		d->p.zoom = 1;
		if (d->choice > 1 && key == A)
			d->choice -= 1;
		if (d->choice < 2 && key == E)
			d->choice += 1;
		threads(d);
	}
	else if ((d->choice == MANDELBROT) && (key == W || key == X))
		anime(key, d);
	return (0);
}

int		mouse_press(int key, int x, int y, t_disp *d)
{
	if (key == WHEELUP)
	{
		d->p.zoom *= 0.9;
		move(d, key, x, y);
		threads(d);
	}
	else if (key == WHEELDOWN)
	{
		d->p.zoom *= 1 / 0.9;
		move(d, key, x, y);
		threads(d);
	}
	return (0);
}

int		mouse_release(int key, int x, int y, t_disp *d)
{
	//	printf("key : [%d]\n", key);
	return (0);
}

int		main(int argc, char **argv)
{
	t_disp		*d;
	int			i;

	if (argc != 2)
		exit(printf("Usage : ./fractol [fractal_name]\n"));
	if ((i = choice(argv)) != 0)
	{
		if (!(d = (t_disp*)malloc(sizeof(t_disp) * NB_THREAD)))
			exit(printf("malloc error\n"));
		init_var(&d[0], i);
		threads(d);
		mlx_hook(d[0].win, 2, 1, key_press, &d[0]);
		mlx_hook(d[0].win, 5, 1L << 3, mouse_release, &d[0]);
		mlx_hook(d[0].win, 4, 1L << 2, mouse_press, &d[0]);
		mlx_hook(d[0].win, 6, 1L << 6, mouse_move, &d[0]);
		mlx_loop(d[0].mlx);
	}
	return (0);
}
