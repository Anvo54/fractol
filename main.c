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


int	mouse_too(int b, int x, int y, t_mlx_data *d)
{
	if (b == 4)
		d->zoom *= 1.5;
	if (b == 5)
		d->zoom /= (d->zoom / 10 < 0.000002) ? 1 : 10;
	
	if (b == 1)
	{
		if (x > d->width / 2)
			d->move_x += ((double)(x - (d->width / 2)) / d->width * 3) / d->zoom;
		if (x < d->width / 2)
			d->move_x -= -((double)(x - (d->width / 2)) / d->width * 3) / d->zoom;
		if (y > d->height / 2)
			d->move_y += ((double)(y - (d->height / 2)) / d->height * 2) / d->zoom;
		if (y < d->height / 2)
			d->move_y -= -((double)(y - (d->height / 2)) / d->height * 2) / d->zoom;
	}
	return(0);
}
// REFACTOR THIS!
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
		d->rgb[0] = (d->rgb[0] > 254) ? 40 : d->rgb[0];
		d->rgb[1] = (d->rgb[1] > 254) ? 40 : d->rgb[1];
		d->rgb[2] = (d->rgb[2] > 254) ? 40 : d->rgb[2];
		i++;
	}
}

void			format_data(t_mlx_data *data)
{
	data->width = 1080;
	data->height = 720;
	data->max_iterations = 100;
	data->rgb[0] = 164;
	data->rgb[1] = 40;
	data->rgb[2] = 40;
	data->zoom = 0.5;
	data->move_x = 0;
	data->move_y = 0;
	data->pause = 0;
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
		if (data.selected == julia || data.selected == mandelbrot || data.selected == burning_ship)
		{
			mlx_key_hook(data.mlx_win, deal_key, &data);
			mlx_hook(data.mlx_win, 4, (1L<<2), mouse_too, &data);
			mlx_hook(data.mlx_win, 6, (1L<<6), mousething, &data);
			mlx_loop_hook(data.mlx_ptr, count_fractal, &data);
			mlx_loop(data.mlx_ptr);
		}
	}
	else
		ft_putstr(USAGE);
	return (0);
}
