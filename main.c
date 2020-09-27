/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/06/08 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		get_color(int a, int r, int g, int b)
{
	(r < 0) ? r = 0: 0;
	(r > 255) ? r = 255: 0;
	(g < 0) ? r = 0: 0;
	(g > 255) ? r = 255: 0;
	(b < 0) ? r = 0: 0;
	(b > 255) ? r = 255: 0;
	return(a << 24 | r << 16 | g << 8 | b);
}

void	*test_cal(void *args)
{
	t_mlx_data *d;
	double zx;
	double zy;
	double xold = 0;
	double yold = 0;
	double xtemp;
	size_t i;

	d = (t_mlx_data*)args;
	i = 0;
	zx = d->fract.new_real_n;
	zy = d->fract.new_im_n;
	while ((zx * zx) + (zy * zy) < 4 && i < d->max_iterations)
	{
		xtemp = zx * zx - zy * zy + d->fract.cRe;
		zy = zx * zy * 2 + d->fract.cIm;
		zx = xtemp;
		i++;
		if (zx == xold && zy == yold)
			break;
	}
	return (void*)i;
}

int julia(t_mlx_data *data)
{
	int x;
	int y;
	int i;

	int color;
	y = 0;
	while (y++ < data->height)
	{
		x = 0;
		while(x++ < data->width)
		{
			data->fract.new_im_n = (y - data->height / 2) / (0.5 * data->zoom * data->height) + data->move_x;
			data->fract.new_real_n = 1.5 * (x - data->width / 2) / (0.5 * data->zoom * data->width) + data->move_y;
			i = (int)test_cal(data);
			add_pixel(data, x, y, data->color[i]);
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_ptr, 0, 0);
	return(1);
}

int	mandelbrot_plot(t_mlx_data *d)
{
	double xr = 0;
	double yi = 0;
	double xtemp;

	int i;
	i = 0;
	while((xr * xr) + (yi * yi) <= 4 && i++ < d->max_iterations)
	{
		xtemp = (xr*xr) - (yi*yi) + d->fract.cRe;
		yi = 2 * xr*yi + d->fract.cIm;
		xr = xtemp;
	}
	return(i);
}

int		mandelbrot(t_mlx_data *d)
{
	int		x;
	int		y;
	int		i;

	y = 0;
	while (y++ < d->height)
	{
		x = 0;
		while (x++ < d->width)
		{
			d->fract.cRe = 1.5 * (x - d->width / 2) / (0.5 * d->zoom * d->width) + d->move_x;
			d->fract.cIm = (y - d->height / 2) / (0.5 * d->zoom * d->height) + d->move_y;
			i = mandelbrot_plot(d);
			add_pixel(d, x, y, d->color[i]);
		}
	}
	
			add_pixel(d, d->width/2, d->height/2, 0x000000);
	mlx_put_image_to_window(d->mlx_ptr, d->mlx_win, d->img_ptr, 0, 0);
	return(0);
}

int mousething(int x, int y, t_mlx_data *data)
{
	double perc_x = percent(0, data->width, x);
	double perc_y = percent(0, data->height, y);
	data->fract.cRe = -1 + (2 * perc_x);
	data->fract.cIm = -1 + (2 * perc_y);
	return(1);
}

int	mouse_too(int b, int x, int y,t_mlx_data *data)
{
	if (b == 4)
		data->zoom += 10;
	if (b == 5 )
		data->zoom -= (data->zoom - 10 < 0) ? 0 : 10;
	if (b == 1)
	{
		if (x > data->width / 2)
			data->move_x += ((double)(x - (data->width / 2)) / data->width * 3) / data->zoom;
		if (x < data->width / 2)
			data->move_x -= -((double)(x - (data->width / 2)) / data->width * 3) / data->zoom;
		if (y > data->height / 2)
			data->move_y += ((double)(y - (data->height / 2)) / data->height * 2) / data->zoom;
		if (y < data->height / 2)
			data->move_y -= -((double)(y - (data->height / 2)) / data->height * 2) / data->zoom;
	}
	printf("Mouse %d... %d... %d... move_x %f move_y %f zoom: %f\n",b,x,y,data->move_x,data->move_y, data->zoom);
	return(0);
}

void			calculate_colors(t_mlx_data *d)
{
	int i;
	int step;
	double p;

	i = 0;
	if (!(d->color = (int*)malloc(sizeof(int) * d->max_iterations)))
		exit(0);
	step = -(ft_smallest_int(d->rgb, 3)-ft_biggest_int(d->rgb, 3)) / (d->max_iterations * 0.2);
	while (i <= d->max_iterations)
	{
		p = percent(0, d->max_iterations, i);
		if (p < 0.2)
			d->color[i] = get_color(255, d->rgb[0], d->rgb[1] += step, d->rgb[2]);
		else if (p < 0.4)
			d->color[i] = get_color(255, d->rgb[0] -= step, d->rgb[1], d->rgb[2]);
		else if (p < 0.6)
			d->color[i] = get_color(255, d->rgb[0], d->rgb[1], d->rgb[2] += step);
		else if (p < 0.8)
			d->color[i] = get_color(255, d->rgb[0], d->rgb[1] -= step, d->rgb[2]);
		else if (p < 1)
			d->color[i] = get_color(255, d->rgb[0] -= step, d->rgb[1] -= step, d->rgb[2] -= step);
		i++;
	}
}

void			format_data(t_mlx_data *data)
{
	data->width = 600;
	data->height = 600;
	data->max_iterations = 200;
	data->rgb[0] = 164;
	data->rgb[1] = 40;
	data->rgb[2] = 40;
	data->zoom = 0;
	data->move_x = 0;
	data->move_y = 0;
	calculate_colors(data);
	if ((data->mlx_ptr = mlx_init()) == (void *)0)
		exit(0);
	if ((data->mlx_win = mlx_new_window(data->mlx_ptr, data->width,
			data->height, "Fractol Hive")) == NULL)
		exit(0);
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->bpp),
		&(data->size_line), &(data->endian));
}

int				main(int argc, char **argv)
{
	if (argc > 1)
	{
		t_mlx_data	data;

		format_data(&data);
		if (!ft_strcmp(argv[1], "julia"))
		{
			mlx_key_hook(data.mlx_win, deal_key, &data);
			mlx_hook(data.mlx_win, 4, (1L<<2), mouse_too, &data);
			mlx_hook(data.mlx_win, 6, (1L<<6), mousething, &data);
			mlx_loop_hook(data.mlx_ptr, julia, &data);
			mlx_loop(data.mlx_ptr);
		}
		if (!ft_strcmp(argv[1], "mandelbrot"))
		{
			mlx_key_hook(data.mlx_win, deal_key, &data);
			mlx_hook(data.mlx_win, 4, (1L<<2), mouse_too, &data);
			mlx_hook(data.mlx_win, 6, (1L<<6), mousething, &data);
			mlx_loop_hook(data.mlx_ptr, mandelbrot, &data);
			mlx_loop(data.mlx_ptr);
		}
	}
	else
		ft_putstr(USAGE);
	return (0);
}
