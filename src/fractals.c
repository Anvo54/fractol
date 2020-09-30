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

void			*julia_plot(void *args)
{
	t_mlx_data	*d;
	double		zx;
	double		zy;
	double		xtemp;
	size_t		i;

	d = (t_mlx_data*)args;
	i = 0;
	zx = (d->fract.y - d->h / 2) / (0.5 * d->zoom * d->h) + d->move_y;
	zy = 1.5 * (d->fract.x - d->w / 2) / (0.5 * d->zoom * d->w) + d->move_x;
	while ((zx * zx) + (zy * zy) < 4 && i < d->max_i)
	{
		xtemp = zx * zx - zy * zy + d->fract.re;
		zy = zx * zy * 2 + d->fract.im;
		zx = xtemp;
		i++;
	}
	return (void*)i;
}

int				mandelbrot_plot(t_mlx_data *d)
{
	double		xr;
	double		yi;
	double		xtemp;
	int			i;

	xr = 0;
	yi = 0;
	i = 0;
	d->fract.re = 1.5 * (d->fract.x - d->w / 2) / (0.5 * d->zoom * d->w) + d->move_x;
	d->fract.im = (d->fract.y - d->h / 2) / (0.5 * d->zoom * d->h) + d->move_y;
	while ((xr * xr) + (yi * yi) <= 4 && i++ < d->max_i)
	{
		xtemp = (xr * xr) - (yi * yi) + d->fract.re;
		yi = 2 * (xr * yi) + d->fract.im;
		xr = xtemp;
	}
	return (i);
}

int				burning_plot(t_mlx_data *d)
{
	double		xr;
	double		yi;
	double		xtemp;
	int			i;

	xr = 0;
	yi = 0;
	i = 0;
	d->fract.re = 1.5 * (d->fract.x - d->w / 2) / (0.5 * d->zoom * d->w) + d->move_x;
	d->fract.im = (d->fract.y - d->h / 2) / (0.5 * d->zoom * d->h) + d->move_y;
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

	d->fract.y = 0;
	while (d->fract.y++ < d->h)
	{
		d->fract.x = 0;
		while (d->fract.x++ < d->w)
		{
			if (d->selected == burning_ship)
				i = burning_plot(d);
			if (d->selected == mandelbrot)
				i = mandelbrot_plot(d);
			if (d->selected == julia)
				i = (int)julia_plot(d);
			add_pixel(d, d->fract.x, d->fract.y, d->color[i]);
		}
	}
	mlx_put_image_to_window(d->mlx_ptr, d->mlx_win, d->img_ptr, 0, 0);
	return (0);
}
