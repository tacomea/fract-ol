#include <math.h>
#include "fractol.h"

# define MAX(A, B) (A > B ? A : B)
# define MIN(A, B) (A > B ? B : A)
#define MOD(a) ((a < 0) ? -a : a)

//float mod(float i)
//{
//	return (i < 0) ? -i : i;
//}

void isometric(double *x, double *y, int z, t_fdf *data)
{
	double tmp_x;
	double tmp_y;

	tmp_x = *x;
	tmp_y = *y;
//	*x = (*x - *y) * cos(data->rotation);
//	*y = (*x + *y) * sin(data->rotation) - z;
//	*x = *x * cos(data->rotation);
//	*y = *y * sin(data->rotation);
	*x = *x * cos(data->rotation) - *y * sin(data->rotation);
	*y = *y * cos(data->rotation) + *x * sin(data->rotation) - z;
//	*x = tmp_x * cos(data->rotation) - tmp_y * sin(data->rotation);
//	*y = tmp_y * cos(data->rotation) + tmp_x * sin(data->rotation) - z;
}

void bresenham(double x, double y, double x1, double y1, t_fdf *data)
{
	double x_step;
	double y_step;
	double max;
	int z;
	int z1;

	z = data->z_matrix[(int)y][(int)x];
	z1 = data->z_matrix[(int)y1][(int)x1];

	// zoom
	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;

	// color
	data->color = (z || z1) ? 0x00ff00 : 0xffffff;

	// 3D
	isometric(&x, &y, z, data);
	isometric(&x1, &y1, z1, data);

	// shift
	x += data->shift_x;
	y += data->shift_y;
	x1 += data->shift_x;
	y1 += data->shift_y;

	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(MOD(x_step), MOD(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, (int)x, (int)y, data->color);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_fdf *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				bresenham(x, y, x + 1, y, data);
			if (y < data->height - 1)
				bresenham(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}