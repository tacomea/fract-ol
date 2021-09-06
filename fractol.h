#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define  WIDTH  800
# define  HEIGHT  800

typedef struct s_color {
	double	r;
	double	g;
	double	b;
} t_color;

typedef struct s_img_inf {
	void	*img_ptr;
	int		bits_per_pixel; //32
	int		size_line;
	int		endian; // 0
	char *buffer;
} t_img_inf;

enum e_color {
	greyscale,
	reverse_greyscale,
	redscale,
	greenscale,
	bluescale,
};

enum e_fractal {
	mandelbrot,
	julia,
	burningship,
};

typedef struct s_var {
	double			diverge;
	int				imax;
	double			cr;
	double			ci;
	double			r_start;
	double			r_end;
	double			i_start;
	double			i_end;
	double			shift_size;
	unsigned int 	frame;
	unsigned int	last_zoomed_frame;
	enum e_color	color;
	enum e_fractal	fractal;
} t_var;

// diverge: 発散とする値の二乗
// imax: max num of loop
typedef struct s_program {
	t_var			*var;
	void			*mlx;
	void			*win;
//	t_img_inf		*img;
	t_img_inf		img;
} t_program;

// main.c
void	display(t_program *param);
void	free_all_ptr(t_program *param);

// calculate.c
int calc_mandelbrot(t_var *var, double cr, double ci);
int calc_julia(t_var *var, double x, double y);

// color.c
void	put_color(t_program *param, int pixel, int color);
int		color_to_int(t_color color);
t_color	color_init(double r, double g, double b);

// hook.c
int	close_window(int keycode, t_program *param);
int	mouse_hook(int button, int x, int y, t_program *param);
int	key_hook(int key, t_program *param);
int	loop_hook(t_program *param);

// draw.c
//void bresenham(double x, double y, double x1, double y1, t_fdf *data);
//void	draw(t_fdf *data);

#endif //FDF_FRACTOL_H
