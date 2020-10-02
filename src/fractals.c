/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void			hud(t_mlx_data *d)
{
	if (d->selected == julia)
		mlx_string_put(d->mlx_ptr, d->mlx_win, 20, 20, 0xFFFFFF,
			"(1) Julia");
	if (d->selected == mandelbrot)
		mlx_string_put(d->mlx_ptr, d->mlx_win, 20, 20, 0xFFFFFF,
			"(2) Mandelbrot");
	if (d->selected == burning_ship)
		mlx_string_put(d->mlx_ptr, d->mlx_win, 20, 20, 0xFFFFFF,
			"(3) Burning Ship");
	if (d->pause == 1)
		mlx_string_put(d->mlx_ptr, d->mlx_win, d->w * 0.9, d->h * 0.9, 0xFFFFFF,
			"Pause");
}

int				julia_plot(t_mlx_data *d, int y, int x)
{
	double		zx;
	double		zy;
	double		xtemp;
	int			i;

	i = 0;
	zx = (y - d->h / 2) / (0.5 * d->zoom * d->h) + d->move_y;
	zy = 1.5 * (x - d->w / 2) / (0.5 * d->zoom * d->w) + d->move_x;
	while ((zx * zx) + (zy * zy) < 4 && i < d->max_i)
	{
		xtemp = zx * zx - zy * zy + d->fract.re;
		zy = zx * zy * 2 + d->fract.im;
		zx = xtemp;
		i++;
	}
	return (i);
}

int				mandelbrot_plot(t_mlx_data *d, int y, int x)
{
	double		xr;
	double		yi;
	double		xtemp;
	int			i;

	xr = 0;
	yi = 0;
	i = 0;
	d->fract.re = 1.5 * (x - d->w / 2) / (0.5 * d->zoom * d->w) + d->move_x;
	d->fract.im = (y - d->h / 2) / (0.5 * d->zoom * d->h) + d->move_y;
	while ((xr * xr) + (yi * yi) <= 4 && i++ < d->max_i)
	{
		xtemp = (xr * xr) - (yi * yi) + d->fract.re;
		yi = 2 * (xr * yi) + d->fract.im;
		xr = xtemp;
	}
	return (i);
}

int				burning_plot(t_mlx_data *d, int y, int x)
{
	double		xr;
	double		yi;
	double		xtemp;
	int			i;

	xr = 0;
	yi = 0;
	i = 0;
	d->fract.re = 1.5 * (x - d->w / 2) / (0.5 * d->zoom * d->w) + d->move_x;
	d->fract.im = (y - d->h / 2) / (0.5 * d->zoom * d->h) + d->move_y;
	while ((xr * xr) + (yi * yi) <= 4 && i++ < d->max_i)
	{
		xtemp = (xr * xr) - (yi * yi) + d->fract.re;
		yi = fabs(2 * xr * yi) + d->fract.im;
		xr = xtemp;
	}
	return (i);
}

int				count_fractal(t_mlx_data *d)
{
	int			i;
	int			x;
	int			y;

	y = 0;
	while (y++ < d->h)
	{
		x = 0;
		while (x++ <= d->w)
		{
			if (d->selected == burning_ship)
				i = burning_plot(d, y, x);
			if (d->selected == mandelbrot)
				i = mandelbrot_plot(d, y, x);
			if (d->selected == julia)
				i = julia_plot(d, y, x);
			add_pixel(d, x, y, d->color[i]);
		}
	}
	mlx_put_image_to_window(d->mlx_ptr, d->mlx_win, d->img_ptr, 0, 0);
	hud(d);
	return (0);
}
