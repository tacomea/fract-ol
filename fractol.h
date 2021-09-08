#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define WIDTH  800
# define HEIGHT  800
# define DIVERGE 4

// endian - 0
// its_per_pixel - 32
typedef struct s_img_inf {
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*buffer;
}	t_img_inf;

typedef struct s_complex {
	double	r;
	double	i;
}	t_complex;

enum e_color {
	greyscale,
	reverse_greyscale,
	redscale,
	greenscale,
	bluescale,
	fire,
};

enum e_fractal {
	mandelbrot,
	julia,
	burningship,
};

typedef struct s_var {
	int				imax;
	t_complex		c;
	t_complex		start;
	t_complex		end;
	double			shift_size;
	unsigned int	frame;
	unsigned int	last_zoomed_frame;
	enum e_color	color;
	enum e_fractal	fractal;
}	t_var;

// diverge: 発散とする値の二乗
// imax: max num of loop
typedef struct s_param {
	t_var			*var;
	void			*mlx;
	void			*win;
	t_img_inf		img;
}	t_param;

// main.c
void	display(t_param *param);
int		free_all_ptr(t_param *param, int status);

// calculate.c
int		calc_mandelbrot(t_var *var, double cr, double ci);
int		calc_julia(t_var *var, double x, double y);
int		calc_burningship(t_var *var, double cr, double ci);

// color.c
void	put_color(t_param *param, int pixel, int color);
int		rgb_to_int(double r, double g, double b);
int		route_color(t_var *var, double cnt_itr);

// hook.c
int		close_window(int keycode, t_param *param);
int		mouse_hook(int button, int x, int y, t_param *param);
int		key_hook(int key, t_param *param);
int		loop_hook(t_param *param);
int		open_window(t_param *param);

// misc.c
void	shift(double *start, double *end, double shift_size);
int		free_all_ptr(t_param *param, int status);

// simple_atof.c
double	simple_atof(char *str);

#endif //FDF_FRACTOL_H
