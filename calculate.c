#include "fractol.h"
#include <math.h>

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
int	calc_mandelbrot(t_var *var, double cr, double ci)
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
	while (x2 + y2 <= DIVERGE && i < var->imax)
	{
		y = 2 * x * y + ci;
		x = x2 - y2 + cr;
		x2 = x * x;
		y2 = y * y;
		i++;
	}
	return (i);
}

// calculation speed: 300751.000000
//int calc_julia(t_var *var, double x, double y)
//{
//	double	xn;
//	double	yn;
//	int		i;
//
//	xn = 0.0;
//	yn = 0.0;
//	i = 0;
//	while (xn * xn + yn * yn <= DIVERGE && i < var->imax)
//	{
//		xn = x * x - y * y + var->cr;
//		yn = 2.0 * x * y + var->ci;
//		x = xn;
//		y = yn;
//		i++;
//	}
//	return (i);
//}

// calculation speed: 292033.000000
int	calc_julia(t_var *var, double x, double y)
{
	double	x2;
	double	y2;
	int		i;

	x2 = x * x;
	y2 = y * y;
	i = 0;
	while (x2 + y2 <= DIVERGE && i < var->imax)
	{
		y = 2 * x * y + var->c.i;
		x = x2 - y2 + var->c.r;
		x2 = x * x;
		y2 = y * y;
		i++;
	}
	return (i);
}

// calculation speed: 47073.000000
//int calc_burningship(t_var *var, double cr, double ci)
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
//	while (zr * zr + zi * zi <= DIVERGE && i < var->imax)
//	{
//		zrn = zr * zr - zi * zi + cr;
//		zin = 2.0 * MOD(zr) * MOD(zi) + ci;
//		zr = zrn;
//		zi = zin;
//		i++;
//	}
//	return (i);
//}

// calculation speed: 44161.000000
int	calc_burningship(t_var *var, double cr, double ci)
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
	while (x2 + y2 <= DIVERGE && i < var->imax)
	{
		y = 2.0 * fabs(x) * fabs(y) + ci;
		x = x2 - y2 + cr;
		x2 = x * x;
		y2 = y * y;
		i++;
	}
	return (i);
}
