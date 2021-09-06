#include <time.h>
#include "fractol.h"
#include <printf.h>

void	free_all_ptr(t_program *param)
{
	mlx_destroy_image(param->mlx, param->img.img_ptr);
	mlx_destroy_window(param->mlx, param->win);
	mlx_destroy_display(param->mlx);
	free(param->mlx);
//	free(param->img);
//	free(param->win);
//	free(param->img.img_ptr);
}

void	process_args(int argc, char **argv, t_var *var)
{
	if (argc != 1 && !ft_strncmp(argv[1], "M", 1))
	{
		var->fractal = mandelbrot;
		var->r_start = -2.3;
		var->r_end = 0.7;
		var->i_start = -1.5;
		var->i_end = 1.5;
		var->imax = 20;
		var->shift_size = 0.4;
	}
	else if (argc != 1 && !ft_strncmp(argv[1], "J", 1))
	{
		var->fractal = julia;
		var->r_start = -1.5;
		var->r_end = 1.5;
		var->i_start = -1.5;
		var->i_end = 1.5;
		var->imax = 400;
		var->shift_size = 0.4;
		var->cr = atof(argv[2]);
		var->ci = atof(argv[3]);
	}
	else
	{
//		param->fractal = mandelbrot;
		ft_putstr_fd("usage:\tfractol -M\n\tfractol -J\n", 2);
		exit (0);
	}
}

void	display(t_program *param)
{
	clock_t start;
	double	r_current;
	double	i_current;
	double	dr;
	double	di;
	int ix;
	int iy;

//	start = clock();
	dr = (param->var->r_end - param->var->r_start) / WIDTH; // 実部(横)刻み幅
	di = (param->var->i_end - param->var->i_start) / HEIGHT; // 虚部(縦)刻み幅
	for (i_current = param->var->i_start, iy = HEIGHT; i_current <= param->var->i_end; i_current += di, iy--) // 定数虚部（縦）
//	for (ci = param->var->i_start, iy = 0; ci <= param->var->i_end; ci += dci, iy++) // 定数虚部（縦）
	{
		for (r_current = param->var->r_start, ix = 0; r_current <= param->var->r_end; r_current += dr, ix++)
		{
			double cnt_itr;
			if (param->var->fractal == mandelbrot)
				cnt_itr = calc_mandelbrot(param->var, r_current, i_current);
			else if (param->var->fractal == julia)
				cnt_itr = calc_julia(param->var, r_current, i_current);
			else
				return ;
			int color = color_to_int(color_init(0, 0, 0));
			if (param->var->color == greyscale)
				color = color_to_int(color_init(cnt_itr/param->var->imax, cnt_itr/param->var->imax, cnt_itr/param->var->imax));
			else if (param->var->color == reverse_greyscale)
				color = color_to_int(color_init(1 - cnt_itr/param->var->imax, 1 - cnt_itr/param->var->imax, 1 - cnt_itr/param->var->imax));
			else if (param->var->color == redscale)
				color = color_to_int(color_init(1 - cnt_itr/param->var->imax, 0, 0));
			else if (param->var->color == greenscale)
				color = color_to_int(color_init(0, 1 - cnt_itr/param->var->imax, 0));
			else if (param->var->color == bluescale)
				color = color_to_int(color_init(0, 0, 1 - cnt_itr/param->var->imax));
			put_color(param, (iy * param->img.size_line) + (ix * 4), color);
		}
	}
	printf("calculation speed: %f \n", (double)(clock() - start));
}

int main(int argc, char **argv)
{
	// param setup
	t_program param;

	printf("sizeof(t_program): %zu \n", sizeof(t_program));

	// var setup
	param.var = (t_var*)malloc(sizeof(t_var));
	if (!param.var)
		return (1);
	param.var->diverge = 4;
	param.var->frame = 0;
	param.var->last_zoomed_frame = 0;

	process_args(argc, argv, param.var);

	param.mlx = mlx_init();
	param.win = mlx_new_window(param.mlx, WIDTH, HEIGHT, "fract-ol");

	param.img.img_ptr = mlx_new_image(param.mlx, WIDTH, HEIGHT);
	param.img.buffer = mlx_get_data_addr(param.img.img_ptr, &param.img.bits_per_pixel, &param.img.size_line, &param.img.endian);

	display(&param);

	mlx_key_hook(param.win, key_hook, &param);
	mlx_mouse_hook(param.win, mouse_hook, &param);
	mlx_hook(param.win, 17, 0, close_window, &param);
	mlx_loop_hook(param.mlx, loop_hook, &param);

	mlx_put_image_to_window(param.mlx, param.win, param.img.img_ptr, 0, 0);

	mlx_loop(param.mlx);
	return 0;
}
