#include "fractol.h"

// 41255.000000
int calc_mandelbrot(t_program *param, double cr, double ci)
{
	double	zr;
	double	zi;
	double	zrn;
	double	zin;
	int		i;

	zr = 0.0;
	zi = 0.0;
	for (i = 0; i < param->imax; i++)
	{
		zrn = zr * zr - zi * zi + cr;
		zin = 2.0 * zr * zi + ci;
		if (zrn * zrn + zin * zin > param->diverge * param->diverge)
			return (i);
		zr = zrn;
		zi = zin;
	}
	return (i);
}