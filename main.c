#include <stdio.h>
#include <time.h>
#include "fractol.h"



//t_program param_init(int width, int height)
//{
//	t_program rtn;
//
//	rtn.width = width;
//	rtn.height = height;
//
//	// watching point setup
////	rtn.pe = pe;
//	return (rtn);
//}

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

void	display(t_program *param)
{
	clock_t start;
	double cr, ci, dcr, dci;
	int ix, iy;

	start = clock();
	dcr = (param->cr2 - param->cr1) / WIDTH; // 実部(横)刻み幅
	dci = (param->ci2 - param->ci1) / HEIGHT; // 虚部(縦)刻み幅
	for (ci = param->ci1, iy = HEIGHT; ci <= param->ci2; ci += dci, iy--) // 定数虚部（縦）
	{
		for (cr = param->cr1, ix = 0; cr <= param->cr2; cr += dcr, ix++)
		{
			double i = calc_mandelbrot(param, cr, ci);
			int color = color_to_int(color_init(i/param->imax, i/param->imax, i/param->imax));
			put_color(param, (iy * param->img.size_line) + (ix * 4), color);
		}
	}
	printf("calculation speed: %f \n", (double)(clock() - start));
}

int main(int argc, char **argv) {
	// param setup
	t_program param;
	param.mlx = mlx_init();
//	param.win = mlx_new_window(param.mlx, WIDTH, HEIGHT+18, "fract-ol");
	param.win = mlx_new_window(param.mlx, WIDTH, HEIGHT, "fract-ol");

	// const setup
	param.cr1 = -2.3; // 定数実部 始点
	param.cr2 = 0.7; // 定数実部 終点
	param.ci1 = -1.5; // 定数虚部 始点
	param.ci2 = 1.5; // 定数虚部 終点
	param.diverge = 4.0;
	param.imax = 20; // 最大計算回数

	// image setup
	param.img.img_ptr = mlx_new_image(param.mlx, WIDTH, HEIGHT);
	param.img.buffer = mlx_get_data_addr(param.img.img_ptr, &param.img.bits_per_pixel, &param.img.size_line, &param.img.endian);

//	data.zoom = 30;
//	data.rotation = 0.5;
//	data.shift_x = 300;
//	data.shift_y = 100;

//	bresenham(10, 10, 300, 100, data);
//	draw(&data);
	display(&param);

	mlx_key_hook(param.win, key_hook, &param);
	mlx_mouse_hook(param.win, mouse_hook, &param);
	mlx_hook(param.win, 17, 0, close_window, &param);
	mlx_put_image_to_window(param.mlx, param.win, param.img.img_ptr, 0, 0);

//	system("leaks fractol");

	mlx_loop(param.mlx);
	return 0;
}
