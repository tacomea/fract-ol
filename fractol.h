#ifndef FDF_FRACTOL_H
#define FDF_FRACTOL_H

#include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define  WIDTH  800
# define  HEIGHT  800

typedef struct s_color {
	double r;
	double g;
	double b;
} t_color;

typedef struct s_img_inf {
	void *img_ptr;
	int bits_per_pixel; //32
	int size_line;
	int endian; // 0
	char *buffer;
} t_img_inf;

// diverge: 発散とする値の二乗
typedef struct s_program {
	void *mlx;
	void *win;
	double cr1;
	double cr2;
	double ci1;
	double ci2;
	double diverge;
	int imax;
//	int width;
//	int height;
	t_img_inf img;
} t_program;

//typedef struct s_fdf
//{
//	int width;
//	int height;
//	int **z_matrix;
//	float zoom;
//	int color;
//	int shift_x;
//	int shift_y;
//	double rotation;
//	void *mlx_ptr;
//	void *win_ptr;
//} t_fdf;

// main.c
void	display(t_program *param);

// calculate.c
int calc_mandelbrot(t_program *param, double cr, double ci);

// hook.c
int    close_window(int keycode, t_program *param);
int mouse_hook(int button,int x,int y, t_program *param);
int key_hook(int key, t_program *param);

// draw.c
//void bresenham(double x, double y, double x1, double y1, t_fdf *data);
//void	draw(t_fdf *data);

#endif //FDF_FRACTOL_H
