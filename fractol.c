#include <stdlib.h>
#include "fractol.h"

void	init_params(t_param *param)
{
	t_img_inf	*img;

	param->mlx = NULL;
	param->win = NULL;
	param->img.img_ptr = NULL;
	param->var = malloc(sizeof(*param->var));
	if (!param->var)
		exit(free_all_ptr(param, EXIT_FAILURE));
	param->mlx = mlx_init();
	if (!param->mlx)
		exit(free_all_ptr(param, EXIT_FAILURE));
	param->win = mlx_new_window(param->mlx, WIDTH, HEIGHT, "fract-ol");
	if (!param->win)
		exit(free_all_ptr(param, EXIT_FAILURE));
	param->img.img_ptr = (mlx_new_image(param->mlx, WIDTH, HEIGHT));
	if (!param->img.img_ptr)
		exit(free_all_ptr(param, EXIT_FAILURE));
	img = &param->img;
	img->buffer = mlx_get_data_addr(img->img_ptr,
			&img->bits_per_pixel, &img->size_line, &img->endian);
}

void	init_vars(t_var *var)
{
	var->frame = 0;
	var->last_zoomed_frame = 0;
	var->color = greyscale;
	var->imax = 20;
	var->shift_size = 0.3;
	var->end.i = 1.5;
	var->start.i = -1.5;
	if (var->fractal == mandelbrot)
	{
		var->start.r = -2.3;
		var->end.r = 0.7;
	}
	else if (var->fractal == julia)
	{
		var->start.r = -1.5;
		var->end.r = 1.5;
		var->imax = 400;
	}
	else if (var->fractal == burningship)
	{
		var->start.r = -2.5;
		var->end.r = 1.5;
		var->start.i = -2.5;
		var->shift_size = 0.4;
	}
}

void	process_args(int argc, char **argv, t_param *param)
{
	if (argc != 1 && !ft_strncmp(argv[1], "M", 1))
		param->var->fractal = mandelbrot;
	else if (argc != 1 && !ft_strncmp(argv[1], "J", 1))
	{
		param->var->fractal = julia;
		if (argc > 3)
		{
			param->var->c.i = simple_atof(argv[3]);
			param->var->c.r = simple_atof(argv[2]);
		}
		else
		{
			param->var->c.i = -0.63;
			param->var->c.r = -0.3;
		}
	}
	else if (argc != 1 && !ft_strncmp(argv[1], "B", 1))
		param->var->fractal = burningship;
	else
	{
		ft_putstr_fd("usage:\tfractol M\n\tfractol J [R] [I]\n\tfractol B\n", 2);
		exit(free_all_ptr(param, EXIT_FAILURE));
	}
}

void	create_img(t_param *param)
{
	t_complex	current;
	int			ix;
	int			iy;
	double		cnt_itr;

	current.i = param->var->start.i;
	iy = -1;
	while (++iy <= HEIGHT)
	{
		current.r = param->var->start.r;
		ix = -1;
		while (++ix <= WIDTH)
		{
			if (param->var->fractal == mandelbrot)
				cnt_itr = calc_mandelbrot(param->var, current.r, current.i);
			else if (param->var->fractal == julia)
				cnt_itr = calc_julia(param->var, current.r, current.i);
			else if (param->var->fractal == burningship)
				cnt_itr = calc_burningship(param->var, current.r, current.i);
			put_color(param, (iy * param->img.size_line) + (ix * 4),
				  route_color(param->var, cnt_itr));
			current.r += (param->var->end.r - param->var->start.r) / WIDTH;
		}
		current.i += (param->var->end.i - param->var->start.i) / HEIGHT;
	}
}

int	main(int argc, char **argv)
{
	t_param	param;

	init_params(&param);
	process_args(argc, argv, &param);
	init_vars(param.var);
	create_img(&param);
	register_hooks(&param);
	mlx_put_image_to_window(param.mlx, param.win, param.img.img_ptr, 0, 0);
	mlx_loop(param.mlx);
	return (EXIT_SUCCESS);
}
