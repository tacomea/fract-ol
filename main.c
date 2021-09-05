#include <stdio.h>
#include "fractol.h"

#define  XMAX  800
#define  YMAX  800

t_program param_init(int width, int height)
{
	t_program rtn;

	rtn.width = width;
	rtn.height = height;
	rtn.mlx = mlx_init();
	rtn.win = mlx_new_window(rtn.mlx, rtn.width, rtn.height, "fract-ol");
	// watching point setup
//	rtn.pe = pe;
	return (rtn);
}

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

void	put_color(int pixel, int color, t_img_inf *img)
{
	img->buffer[pixel + 0] = (char)(color & 0xFF);
	img->buffer[pixel + 1] = (char)((color >> 8) & 0xFF);
	img->buffer[pixel + 2] = (char)((color >> 16) & 0xFF);
	img->buffer[pixel + 3] = (char)(color >> 24);
}

int deal_key(int key, t_fdf *data)
{
	// todo: remove printf
	printf("%d\n", key);
	// ↑
	if (key == 65362)
		data->shift_y -= 10;
	// ↓
	if (key == 65364)
		data->shift_y += 10;
	// <-
	if (key == 65361)
		data->shift_x -= 10;
	// ->
	if (key == 65363)
		data->shift_x += 10;
	// ESC
	if (key == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw(data);
	return (0);
}

int    close_window(int keycode, t_program *param)
{
	(void)keycode;
	// free_map(param);
	// free_all_ptr(param);
	mlx_destroy_window(param->mlx, param->win);
	exit(0);
	return (0);
}

void	display(t_program *param, t_img_inf *img)
{
	double cr, ci, dcr, dci;
	double zr, zi, zrn, zin;
	int i, ix, iy, cl, nc;

	dcr = (param->cr2 - param->cr1) / XMAX; // 実部(横)刻み幅
	dci = (param->ci2 - param->ci1) / YMAX; // 虚部(縦)刻み幅
	nc = param->imax/256; // 階調比率(256階調)
	if (nc <= 0)
		nc = 1;
	for (ci = param->ci1, iy = YMAX; ci <= param->ci2; ci += dci, iy--) // 定数虚部（縦）
	{
		for (cr = param->cr1, ix = 0; cr <= param->cr2; cr += dcr, ix++)
		{
			zr = 0.0;
			zi = 0.0;
			for (i = 0; i < param->imax; i++) // 漸化式計算
			{
				zrn = zr * zr - zi * zi + cr; // 実部漸化式計算
				if (zrn > param->e)
					break ;
				zin = 2.0 * zr * zi + ci;
				if (zin > param->e)
					break ;
				zr = zrn;
				zi = zin;
			}
			cl  = i / nc; //階数調整
			if (cl > 255)
				cl = 255;
			int color;
			color = color_to_int(color_init(cl/255.0, cl/255.0, cl/255.0));
			put_color((iy * img->size_line) + (ix * 4), color, img);
		}
	}
}

int main(int argc, char **argv) {
	// param setup
	t_program param;
	param = param_init(XMAX, YMAX+18);

	// const setup
	param.cr1 = -2.3; // 定数実部 始点
	param.cr2 = 0.7; // 定数実部 終点
	param.ci1 = -1.5; // 定数虚部 始点
	param.ci2 = 1.5; // 定数虚部 終点
	param.e = 2.0; // 発散とする値
	param.imax = 400; // 最大計算回数

	// image setup
	t_img_inf img;
	img.image = mlx_new_image(param.mlx, param.width, param.height);
	img.buffer = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.size_line, &img.endian);

//	data.zoom = 30;
//	data.rotation = 0.5;
//	data.shift_x = 300;
//	data.shift_y = 100;

//	bresenham(10, 10, 300, 100, data);
//	draw(&data);
	display(&param, &img);
	mlx_key_hook(param.win, deal_key, &param);
	mlx_hook(param.win, 17, 0, close_window, &param);
	mlx_put_image_to_window(param.mlx, param.win, img.image, 0, 0);

//	system("leaks fractol");

	mlx_loop(param.mlx);
	return 0;
}
