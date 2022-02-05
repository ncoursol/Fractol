/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <ncoursol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:14:57 by ncoursol          #+#    #+#             */
/*   Updated: 2022/01/31 14:53:40 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "../lib/libft/libft.h"
# include "../lib/minilibx_macos/mlx.h"

# define WIDTH 1000
# define HEIGHT 800

# define NB_THREAD 8

# define JULIA 1
# define MANDELBROT 2
# define BURNINGSHIP 3

# define ESC 53
# define TAB 48
# define PLUS 69
# define MINUS 78
# define LEFT 123
# define UP 126
# define RIGHT 124
# define DOWN 125
# define SPACE 49
# define Q 12
# define E 14
# define Z 6
# define X 7
# define W 13
# define A 0
# define S 1
# define D 2
# define R 15
# define G 5
# define B 11
# define WHEELUP 4
# define WHEELDOWN 5
# define MOUSERIGHT 3
# define MOUSELEFT 1
# define WHEEL 1

typedef struct s_coord
{
	double	x;
	double	y;
}		t_coord;

typedef struct s_param
{
	double	xmax;
	double	ymax;
	double	xmin;
	double	ymin;
	double	x;
	double	y;
	double	xn;
	double	yn;
	double	zoom;
	double	mult;
	float	color_s;
	int		iter;
	int		color_swap;
	int		color_r;
	int		color_g;
	int		color_b;
}			t_param;

typedef struct s_disp
{
	void			*mlx;
	void			*win;
	void			*pic;
	char			*img;
	pthread_t		th;
	int				choice;
	int				bpp;
	int				sl;
	int				end;
	int				nb;
	int				lock;
	struct s_coord	screen;
	struct s_param	p;
}			t_disp;

int		julia(t_disp *d);
int		multibrot(t_disp *d);
int		mandelbrot(t_disp *d);
int		burning_ship(t_disp *d);
double	math_fct(double a, double b);
double	dist_btw_two_pts(double xa, double ya, double xb, double yb);
int		mouse_move(int x, int y, t_disp *d);
int		key_press(int key, t_disp *d);
int		mouse_press(int key, int x, int y, t_disp *d);
void	init(t_disp *d, int i);
void	threads(t_disp *d);
void	fract_center(t_disp *d);
void	init_fract_var(t_disp *d);
void	init_main_var(t_disp *d);
void	iter(t_disp *d, int key);
void	move(t_disp *d, int key);
void	change_coloring(t_disp *d, int key);
void	end_program(t_disp *d);
int		redirect(t_disp *d);
int		choice(char **argv);
void	end_program(t_disp *d);
void	error_checker(int argc);
void	clear(t_disp *d);
void	fract_center(t_disp *d);

#endif
