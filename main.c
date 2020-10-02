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

void			format_data(t_mlx_data *data)
{
	data->w = 1080;
	data->h = 720;
	data->max_i = 100;
	data->rgb[0] = MIN_C;
	data->rgb[1] = MIN_C;
	data->rgb[2] = MIN_C;
	data->zoom = 0.5;
	data->move_x = 0;
	data->move_y = 0;
	data->pause = 0;
	calculate_colors(data);
	if ((data->mlx_ptr = mlx_init()) == (void *)0)
		exit(0);
	if ((data->mlx_win = mlx_new_window(data->mlx_ptr, data->w,
			data->h, "Fractol Hive")) == NULL)
		exit(0);
	data->img_ptr = mlx_new_image(data->mlx_ptr, data->w, data->h);
	data->img_data = mlx_get_data_addr(data->img_ptr, &(data->bpp),
		&(data->size_line), &(data->endian));
}

int				main(int argc, char **argv)
{
	t_mlx_data	data;

	if (argc > 1)
	{
		format_data(&data);
		data.selected = none;
		if (!ft_strcmp(argv[1], "julia"))
			data.selected = julia;
		else if (!ft_strcmp(argv[1], "mandelbrot"))
			data.selected = mandelbrot;
		else if (!ft_strcmp(argv[1], "burning_ship"))
			data.selected = burning_ship;
		if (data.selected != none)
		{
			mlx_key_hook(data.mlx_win, deal_key, &data);
			mlx_hook(data.mlx_win, 4, (1L << 2), mouse_zoom, &data);
			mlx_hook(data.mlx_win, 6, (1L << 6), mouse_motion, &data);
			mlx_loop_hook(data.mlx_ptr, count_fractal, &data);
			mlx_loop(data.mlx_ptr);
		}
	}
	else
		ft_putstr(USAGE);
	return (0);
}
