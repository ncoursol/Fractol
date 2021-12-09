#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h> //SUPP

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "../lib/libft/libft.h"
# include "../lib/minilibx_linux/mlx.h"

# define WIDTH 800
# define HEIGHT 600

# define NB_THREAD 8

# define JULIA 1
# define MANDELBROT 2

# define ESC 65307
# define TAB 65289
# define PLUS 65451
# define MINUS 65453
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define SPACE 32
# define A 97
# define E 101
# define W 119
# define X 120
# define WHEELUP 4
# define WHEELDOWN 5
# define MOUSERIGHT 3
# define MOUSELEFT 1
# define WHEEL 1

typedef struct		s_coord
{
	double					x;
	double					y;
}									t_coord;

typedef struct		s_param
{
	double					xmax;
	double					ymax;
	double					xmin;
	double					ymin;
	double					x;
	double					y;
	double					xn;
	double					yn;
	double					zoom;
	double					mult;
	int							iter;
}									t_param;

typedef struct		s_disp
{
	void						*mlx;
	void						*win;
	void						*pic;
	char						*img;
	pthread_t				th;
	int							count;
	int							choice;
	int							bpp;
	int							sl;
	int							end;
	int							nb;
	int							lock;
	struct s_coord	screen;
	struct s_param	p;
}									t_disp;

#endif
