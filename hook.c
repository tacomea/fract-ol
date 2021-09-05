#include <printf.h>
#include "fractol.h"

#define SHIFT_SIZE 0.1

int key_hook(int key, t_program *param)
{
	// todo: remove printf
	printf("%d\n", key);
	// ↑
	if (key == 65362)
	{
		param->ci1 -= SHIFT_SIZE;
		param->ci2 -= SHIFT_SIZE;
	}
	// ↓
	else if (key == 65364)
	{
		param->ci1 += SHIFT_SIZE;
		param->ci2 += SHIFT_SIZE;
	}
	// <-
	else if (key == 65361)
	{
		param->cr1 += SHIFT_SIZE;
		param->cr2 += SHIFT_SIZE;
	}
	// ->
	else if (key == 65363)
	{
		param->cr1 -= SHIFT_SIZE;
		param->cr2 -= SHIFT_SIZE;
	}
	// ESC
	else if (key == 65307)
	{
		mlx_destroy_image(param->mlx, param->img.img_ptr);
		mlx_destroy_window(param->mlx, param->win);
		exit(0);
	}
	else
		return (0);
	mlx_clear_window(param->mlx, param->win);
	display(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (0);
}

int mouse_hook(int button,int x,int y, t_program *param)
{
	printf("button: %d \n", button);
	printf("x: %d \n", x);
	printf("y: %d \n", y);
	// ↑ - zoom close
	if (button == 4)
	{
		param->cr1 += SHIFT_SIZE * x / WIDTH;
		param->cr2 -= SHIFT_SIZE * (1 - x / (double)WIDTH);
		param->ci1 += SHIFT_SIZE * (1 - y / (double)HEIGHT);
		param->ci2 -= SHIFT_SIZE * y / HEIGHT;
	}
	// ↓ - zoom out
	else if (button == 5)
	{
		param->cr1 -= SHIFT_SIZE * x / WIDTH;
		param->cr2 += SHIFT_SIZE * (1 - x / (double)WIDTH);
		param->ci1 -= SHIFT_SIZE * (1 - y / (double)HEIGHT);
		param->ci2 += SHIFT_SIZE * y / HEIGHT;
	}
	else
		return (1);
	mlx_clear_window(param->mlx, param->win);
	display(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (0);
}

int    close_window(int keycode, t_program *param)
{
	(void)keycode;
	// free_map(param);
	// free_all_ptr(param);
	mlx_destroy_window(param->mlx, param->win);
	exit(0);
}
