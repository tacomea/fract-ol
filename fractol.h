#ifndef FDF_FRACTOL_H
#define FDF_FRACTOL_H

#include "libft/libft.h"
# include "minilibx/mlx.h"

typedef struct s_color {
	double r;
	double g;
	double b;
} t_color;

typedef struct s_program {
	void *mlx;
	void *win;
	double cr1;
	double cr2;
	double ci1;
	double ci2;
	double e;
	int imax;
	int width;
	int height;
} t_program;

typedef struct s_img_inf {
	void *image;
	int bits_per_pixel; //32
	int size_line;
	int endian; // 0
	char *buffer;
} t_img_inf;

typedef struct s_fdf
{
	int width;
	int height;
	int **z_matrix;
	float zoom;
	int color;
	int shift_x;
	int shift_y;
	double rotation;
	void *mlx_ptr;
	void *win_ptr;
} t_fdf;


// draw.c
void bresenham(double x, double y, double x1, double y1, t_fdf *data);
void	draw(t_fdf *data);

#endif //FDF_FRACTOL_H
