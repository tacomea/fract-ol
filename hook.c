#include <stdlib.h>
#include "fractol.h"

#define MOUSE_UP 4
#define MOUSE_DOWN 5
#define ARROW_UP 65362
#define ARROW_DOWN 65364
#define ARROW_LEFT 65361
#define ARROW_RIGHT 65363
#define ESC 65307
#define CTRL 65507
#define OPT 65406
#define ONE 49
#define SIX 54

//printf("param->imax: %d \n", param->var->imax);
int	key_hook(int key, t_param *param)
{
	t_var	*var;

	var = param->var;
	if (key == ARROW_UP)
		shift(&var->start.i, &var->end.i, -1 * var->shift_size);
	else if (key == ARROW_DOWN)
		shift(&var->start.i, &var->end.i, var->shift_size);
	else if (key == ARROW_LEFT)
		shift(&var->start.r, &var->end.r, -1 * var->shift_size);
	else if (key == ARROW_RIGHT)
		shift(&var->start.r, &var->end.r, var->shift_size);
	else if (key == ESC)
		exit(free_all_ptr(param, EXIT_SUCCESS));
	else if (key == CTRL)
		var->imax++;
	else if (key == OPT)
		var->imax--;
	else if (key >= ONE && key <= SIX)
		var->color = key - ONE;
	else
		return (EXIT_FAILURE);
	display(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}

int	mouse_hook(int button, int x, int y, t_param *param)
{
	if ((button != MOUSE_UP && button != MOUSE_DOWN)
		|| param->var->frame == param->var->last_zoomed_frame)
		return (EXIT_FAILURE);
	param->var->shift_size = (param->var->end.r - param->var->start.r) * 0.1;
	param->var->last_zoomed_frame = param->var->frame;
	if (button == MOUSE_UP)
	{
		param->var->start.r += param->var->shift_size * x / WIDTH;
		param->var->end.r -= param->var->shift_size * (1 - x / (double)WIDTH);
		param->var->start.i += param->var->shift_size * y / HEIGHT;
		param->var->end.i -= param->var->shift_size * (1 - y / (double)HEIGHT);
		param->var->imax += 1;
	}
	else
	{
		param->var->start.r -= param->var->shift_size * x / WIDTH;
		param->var->end.r += param->var->shift_size * (1 - x / (double)WIDTH);
		param->var->start.i -= param->var->shift_size * y / HEIGHT;
		param->var->end.i += param->var->shift_size * (1 - y / (double)HEIGHT);
		param->var->imax -= 1;
	}
	display(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}

int	close_window(t_param *param)
{
	exit(free_all_ptr(param, EXIT_SUCCESS));
}

int	open_window(t_param *param)
{
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (EXIT_SUCCESS);
}

int	loop_hook(t_param *param)
{
	param->var->frame++;
	return (EXIT_SUCCESS);
}
