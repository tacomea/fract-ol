#include <printf.h>
#include "fractol.h"

int key_hook(int key, t_program *param)
{
	// todo: remove printf
	printf("key: %d\n", key);
	// ↑
	if (key == 65362)
	{
		param->var->i_start += param->var->shift_size;
		param->var->i_end += param->var->shift_size;
	}
	// ↓
	else if (key == 65364)
	{
		param->var->i_start -= param->var->shift_size;
		param->var->i_end -= param->var->shift_size;
	}
	// <-
	else if (key == 65361)
	{
		param->var->r_start -= param->var->shift_size;
		param->var->r_end -= param->var->shift_size;
	}
	// ->
	else if (key == 65363)
	{
		param->var->r_start += param->var->shift_size;
		param->var->r_end += param->var->shift_size;
	}
	// ESC
	else if (key == 65307)
	{
		free_all_ptr(param);
		exit(0);
	}
	// Ctrl
	else if (key == 65507)
		param->var->imax++;
	// Opt
	else if (key == 65406)
		param->var->imax--;
	// 1 - 5
	else if (key == 49)
		param->var->color = greyscale;
	else if (key == 50)
		param->var->color = reverse_greyscale;
	else if (key == 51)
		param->var->color = redscale;
	else if (key == 52)
		param->var->color = greenscale;
	else if (key == 53)
		param->var->color = bluescale;
	else
		return (1);
	printf("param->imax: %d \n", param->var->imax);
	display(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (0);
}

int mouse_hook(int button,int x,int y, t_program *param)
{
//	printf("button: %d \n", button);
	// ↑ - zoom close
	if (button == 4)
	{
		if (param->var->frame ==  param->var->last_zoomed_frame)
		{
			param->var->last_zoomed_frame++;
			param->var->frame++;
			return (1);
		}
		param->var->shift_size = (param->var->r_end - param->var->r_start) * 0.1;
		param->var->r_start += param->var->shift_size * x / WIDTH;
		param->var->r_end -= param->var->shift_size * (1 - x / (double)WIDTH);
		param->var->i_start += param->var->shift_size * (1 - y / (double)HEIGHT);
		param->var->i_end -= param->var->shift_size * y / HEIGHT;
		param->var->imax += 1;
		param->var->last_zoomed_frame = param->var->frame;
	}
	// ↓ - zoom out
	else if (button == 5)
	{
		if (param->var->frame ==  param->var->last_zoomed_frame)
			return (1);
		param->var->shift_size = (param->var->r_end - param->var->r_start) * 0.1;
		param->var->r_start -= param->var->shift_size * x / WIDTH;
		param->var->r_end += param->var->shift_size * (1 - x / (double)WIDTH);
		param->var->i_start -= param->var->shift_size * (1 - y / (double)HEIGHT);
		param->var->i_end += param->var->shift_size * y / HEIGHT;
		param->var->imax -= 1;
		param->var->last_zoomed_frame = param->var->frame;
	}
	else
		return (1);
	printf("param->imax: %d \n", param->var->imax);
//	printf("param->shift_size: %.10f \n", param->shift_size);
//	printf("param->r_start: %.10f \n", param->r_start);
//	printf("param->r_end: %.10f \n", param->r_end);
//	printf("param->i_start: %.10f \n", param->i_start);
//	printf("param->i_end: %.10f \n", param->i_end);
	display(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (0);
}

int    close_window(int keycode, t_program *param)
{
	(void)keycode;
	 free_all_ptr(param);
	exit(0);
}

int	loop_hook(t_program *param)
{
	param->var->frame++;
	return (0);
}
