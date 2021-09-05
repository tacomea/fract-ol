#include "fractol.h"

t_color color_init(double r, double g, double b)
{
	t_color rtn;

	rtn.r = r;
	rtn.g = g;
	rtn.b = b;
	return (rtn);
}

int color_to_int(t_color color)
{
	int rtn = 0;

	rtn |= (int)(color.b * 255);
	rtn |= (int)(color.g * 255) << 8;
	rtn |= (int)(color.r * 255) << 16;
	return (rtn);
}

void	put_color(t_program *param, int pixel, int color)
{
	param->img.buffer[pixel + 0] = (char)(color & 0xFF);
	param->img.buffer[pixel + 1] = (char)((color >> 8) & 0xFF);
	param->img.buffer[pixel + 2] = (char)((color >> 16) & 0xFF);
	param->img.buffer[pixel + 3] = (char)(color >> 24);
}