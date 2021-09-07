#include "fractol.h"
#include <stdlib.h>

void	shift(double *start, double *end, double shift_size)
{
	*start += shift_size;
	*end += shift_size;
}

int	free_all_ptr(t_param *param, int status)
{
	mlx_destroy_image(param->mlx, param->img.img_ptr);
	mlx_destroy_window(param->mlx, param->win);
	mlx_destroy_display(param->mlx);
	free(param->mlx);
	free(param->var);
	free(param->win);
	free(param->img.img_ptr);
	return (status);
}
