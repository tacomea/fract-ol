#include "fractol.h"

int	route_color(t_var *var, double cnt_itr)
{
	int				color;
	const double	ratio = cnt_itr / var->imax;

	if (var->color == greyscale)
		color = rgb_to_int(ratio, ratio, ratio);
	else if (var->color == reverse_greyscale)
		color = rgb_to_int(1 - ratio, 1 - ratio, 1 - ratio);
	else if (var->color == redscale)
		color = rgb_to_int(1 - ratio, 0, 0);
	else if (var->color == greenscale)
		color = rgb_to_int(0, 1 - ratio, 0);
	else if (var->color == bluescale)
		color = rgb_to_int(0, 0, 1 - ratio);
	else if (var->color == fire)
	{
		if (var->imax == cnt_itr)
			color = rgb_to_int(0, 0, 0);
		else if (var->imax - cnt_itr < var->imax / 2.0)
			color = rgb_to_int(0.95686275, 0.00392157, 0.00392157);
		else
			color = rgb_to_int(0.26666667, 0.00392157, 0);
	}
	else
		color = rgb_to_int(0, 0, 0);
	return (color);
}

int	rgb_to_int(double r, double g, double b)
{
	int		rtn;

	rtn = 0;
	rtn |= (int)(b * 255);
	rtn |= (int)(g * 255) << 8;
	rtn |= (int)(r * 255) << 16;
	return (rtn);
}

void	put_color(t_param *param, int pixel, int color)
{
	param->img.buffer[pixel + 0] = (char)(color & 0xFF);
	param->img.buffer[pixel + 1] = (char)((color >> 8) & 0xFF);
	param->img.buffer[pixel + 2] = (char)((color >> 16) & 0xFF);
	param->img.buffer[pixel + 3] = (char)(color >> 24);
}
