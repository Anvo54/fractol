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
#include <stdio.h>

int		get_color(int a, int r, int g, int b)
{
	return(a << 24 | r << 16 | g << 8 | b);
}

void	*test_cal(void *args)
{
	t_mlx_data *d;
	double zx;
	double zy;
	double xold = 0;
	double yold = 0;
	int per = 0;
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
		per++;
		if (per > 20)
		{
			per = 0;
			xold = zx;
			yold = zy;
		}
	}
	return (void*)i;
}

int julia(t_mlx_data *data)
{
	int x;
	int y;
	int i;

	int color = 0xFFFFFF;
	y = 0;
	while (y++ < data->height)
	{
		x = 0;
		while(x++ < data->width)
		{
			data->fract.new_im_n = (y - data->height / 2) / (0.5 * data->height);
			data->fract.new_real_n = 1.5 * (x - data->width / 2) / (0.5 * data->width);
			i = (int)test_cal(data);
			int color = get_color(0, data->reds[i], data->greens[i], data->blues[i]);
			//add_pixel(data, x, y, color);
			//add_pixel(data, x, y, i * 400 % color * (i < 50));
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
	while((xr * xr) + (yi * yi) <= 4 && i++ < 100)
	{
		xtemp = (xr*xr) - (yi*yi) + d->fract.cRe;
		yi = 2 * xr*yi + d->fract.cIm;
		xr = xtemp;
	}
	return(i);
}

void	mandelbrot(t_mlx_data *d)
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
			d->fract.cRe = 1.5 * (x - d->width / 2) / (0.5 * d->width);
			d->fract.cIm = (y - d->height / 2) / (0.5 * d->height);
			i = mandelbrot_plot(d);
			int color = get_color(0, d->reds[i], d->greens[i], d->blues[i]);
			add_pixel(d, x, y, color);
			//add_pixel(d, x, y, i * 400 % 0xFFFFFF * (i < d->max_iterations));
		}
	}
	mlx_put_image_to_window(d->mlx_ptr, d->mlx_win, d->img_ptr, 0, 0);
}

int mousething(int x, int y, t_mlx_data *data)
{
	double perc_x = percent(0, data->width, x);
	double perc_y = percent(0, data->height, y);

	if (data->prev_x != x || data->prev_y != y)
	{
		data->prev_x = x;
		data->prev_y = y;
		if ((!ft_strcmp(data->selected_f, "julia")))
		{
			data->fract.cRe = -1 + (2 * perc_x);
			data->fract.cIm = -1 + (2 * perc_y);
			julia(data);
		}
		if (!ft_strcmp(data->selected_f, "mandelbrot"))
			mandelbrot(data);
		
	}
	return(1);
}

void			calculate_colors(t_mlx_data *d)
{
	int i;

	i = 0;
	if (!(d->reds = (int*)malloc(sizeof(int) * d->max_iterations)))
		exit(0);
	if (!(d->greens = (int*)malloc(sizeof(int) * d->max_iterations)))
		exit(0);
	if (!(d->blues = (int*)malloc(sizeof(int) * d->max_iterations)))
		exit(0);
	while (i <= d->max_iterations)
	{
		d->reds[i] = 0 + (2.55 * i);
		d->greens[i] = 0 + (2.55 * i);
		d->blues[i] = 0 + (2.55 * i);
		i++;
	}
}

void			format_data(t_mlx_data *data)
{
	data->width = 1024;
	data->height = 768;
	data->max_iterations = 100;
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
		int color = 0xFFFFFF;
		t_mlx_data	data;

		data.fract.cRe = -0.74543;
		data.fract.cIm = 0.27015;

		data.prev_x = 0;
		data.prev_y = 0;
		format_data(&data);
		if (!ft_strcmp(argv[1], "julia") || !ft_strcmp(argv[1], "mandelbrot"))
		{
			data.selected_f = argv[1];
			mlx_key_hook(data.mlx_win, deal_key, &data);
			mlx_hook(data.mlx_win, 6, (1L<<6) ,mousething, &data);
			mlx_loop(data.mlx_ptr);
		}
	}
	else
		ft_putstr(USAGE);

	
	return (0);
}
