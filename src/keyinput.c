/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyinput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	reset_values(t_mlx_data *data)
{
	data->move_x = 0;
	data->move_y = 0;
	data->zoom = 0.5;
}

void	move(int key, t_mlx_data *data)
{
	if (key == 65363)
		data->move_x += 0.01 / data->zoom;
	if (key == 65361)
		data->move_x -= 0.01 / data->zoom;
	if (key == 65362)
		data->move_y += 0.01 / data->zoom;
	if (key == 65364)
		data->move_y -= 0.01 / data->zoom;
}

void	zoom(int key, t_mlx_data *data)
{
	if (key == 44)
		data->zoom *= 1.5;
	if (key == 46)
		data->zoom /= (data->zoom / 10 < 0.000002) ? 1 : 10;
}

int		deal_key(int key, t_mlx_data *data)
{
	if (key == 65307 || key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	if (key == 32)
		data->pause = (data->pause == 0) ? 1 : 0;
	if (key == 65361 || key == 65362 || key == 65363 || key == 65364)
		move(key, data);
	if (key == 44 || key == 46)
		zoom(key, data);
	if (key == 45)
		reset_values(data);
	if (key == 49)
		data->selected = julia;
	if (key == 50)
		data->selected = mandelbrot;
	if (key == 51)
		data->selected = burning_ship;
	return (1);
}
