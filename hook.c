#include <printf.h>
#include "fractol.h"

int key_hook(int key, t_program *param)
{
	// todo: remove printf
	printf("%d\n", key);
	// ↑
	if (key == 65362)
	{
		param->ci1 += param->shift_size;
		param->ci2 += param->shift_size;
	}
	// ↓
	else if (key == 65364)
	{
		param->ci1 -= param->shift_size;
		param->ci2 -= param->shift_size;
	}
	// <-
	else if (key == 65361)
	{
		param->cr1 -= param->shift_size;
		param->cr2 -= param->shift_size;
	}
	// ->
	else if (key == 65363)
	{
		param->cr1 += param->shift_size;
		param->cr2 += param->shift_size;
	}
	// ESC
	else if (key == 65307)
	{
		mlx_destroy_image(param->mlx, param->img.img_ptr);
		mlx_destroy_window(param->mlx, param->win);
		exit(0);
	}
	// Ctrl
	else if (key == 65507)
		param->imax++;
	// Opt
	else if (key == 65406)
		param->imax--;
	// 1 - 5
	else if (key == 49)
		param->color = greyscale;
	else if (key == 50)
		param->color = reverse_greyscale;
	else if (key == 51)
		param->color = redscale;
	else if (key == 52)
		param->color = greenscale;
	else if (key == 53)
		param->color = bluescale;
	else
		return (0);
	display(param);
	mlx_put_image_to_window(param->mlx, param->win, param->img.img_ptr, 0, 0);
	return (0);
}

int mouse_hook(int button,int x,int y, t_program *param)
{
	static int zoom_cnt;

	printf("button: %d \n", button);
	printf("x: %d \n", x);
	printf("y: %d \n", y);
	// ↑ - zoom close
	if (button == 4)
	{
		printf("param->frame: %u \n", param->frame);
		printf("param->last_zoomed_frame: %u \n", param->last_zoomed_frame);
		if (param->frame ==  param->last_zoomed_frame)
		{
			printf("returned!! zoom_cnt: %d \n", zoom_cnt++);
			return (1);
		}
		param->shift_size = (param->cr2 - param->cr1) * 0.1;
		param->cr1 += param->shift_size * x / WIDTH;
		param->cr2 -= param->shift_size * (1 - x / (double)WIDTH);
		param->ci1 += param->shift_size * (1 - y / (double)HEIGHT);
		param->ci2 -= param->shift_size * y / HEIGHT;
		param->imax += 1;
		param->last_zoomed_frame = param->frame;
	}
	// ↓ - zoom out
	else if (button == 5)
	{
		if (param->frame ==  param->last_zoomed_frame)
			return (1);
		param->shift_size = (param->cr2 - param->cr1) * 0.1;
		param->cr1 -= param->shift_size * x / WIDTH;
		param->cr2 += param->shift_size * (1 - x / (double)WIDTH);
		param->ci1 -= param->shift_size * (1 - y / (double)HEIGHT);
		param->ci2 += param->shift_size * y / HEIGHT;
		param->imax -= 1;
		param->last_zoomed_frame = param->frame;
	}
	else
		return (1);
	printf("param->imax: %d \n", param->imax);
	printf("param->shift_size: %.10f \n", param->shift_size);
	printf("param->cr1: %.10f \n", param->cr1);
	printf("param->cr2: %.10f \n", param->cr2);
	printf("param->ci1: %.10f \n", param->ci1);
	printf("param->ci2: %.10f \n", param->ci2);
	if (param->cr1 > param->cr2)
		printf("ERROR: param->cr1 > param->cr2 \n");
	if (param->ci1 > param->ci2)
		printf("ERROR: param->ci2 > param->ci2 \n");
	display(param);
//	mlx_clear_window(param->mlx, param->win);
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

int	loop_hook(t_program *param)
{
	param->frame++;
	if (param->frame == UINT32_MAX)
		printf("frame == SIZE_MAX \n");
	return (0);
}
