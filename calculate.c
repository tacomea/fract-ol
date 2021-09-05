#include "fractol.h"

// 46577.000000
//int calc_mandelbrot(t_program *param, double cr, double ci)
//{
//	double	zr;
//	double	zi;
//	double	zrn;
//	double	zin;
//	int		i;
//
//	zr = 0.0;
//	zi = 0.0;
//	i = 0;
//	while (zr * zr + zi * zi <= param->diverge && i < param->imax)
//	{
//		zrn = zr * zr - zi * zi + cr;
//		zin = 2.0 * zr * zi + ci;
//		zr = zrn;
//		zi = zin;
//		i++;
//	}
//	return (i);
//}

// 40727.000000
int calc_mandelbrot(t_program *param, double cr, double ci)
{
	double	x;
	double	y;
	double	x2;
	double	y2;
	int		i;

	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	i = 0;
	while (x2 + y2 <= param->diverge && i < param->imax)
	{
		y = 2 * x * y + ci;
		x = x2 - y2 + cr;
		x2 = x * x;
		y2 = y * y;
		i++;
	}
	return (i);
}
