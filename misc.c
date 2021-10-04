#include "fractol.h"
#include <stdlib.h>

void	shift(double *start, double *end, double shift_size)
{
	*start += shift_size;
	*end += shift_size;
}

int	free_all_ptr(t_param *param, int status)
{
	if (param->mlx && param->img.img_ptr)
		mlx_destroy_image(param->mlx, param->img.img_ptr);
	if (param->mlx && param->win)
		mlx_destroy_window(param->mlx, param->win);
	if (param->mlx)
		mlx_destroy_display(param->mlx);
	free(param->mlx);
	free(param->var);
	return (status);
}

void	register_hooks(t_param *param)
{
	mlx_key_hook(param->win, key_hook, param);
	mlx_mouse_hook(param->win, mouse_hook, param);
	mlx_hook(param->win, 33, 1L << 17, close_window, param);
	mlx_expose_hook(param->win, open_window, param);
	mlx_loop_hook(param->mlx, loop_hook, param);
}
