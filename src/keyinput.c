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

void	empty_image(t_mlx_data *data)
{
	ft_bzero(data->img_data, data->width * data->height * 4);
}

void	reset_values(t_mlx_data *data)
{
	data->move_x = 0;
	data->move_y = 0;
	data->zoom = 1;
}

int		deal_key(int key, t_mlx_data *data)
{
	ft_putnbr(key);
	write(1, "\n", 1);
	if (key == 65307 || key == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
		exit(0);
	}
	if (key == 65363)
		data->move_x += 0.01 / data->zoom;
	if (key == 65361)
		data->move_x -= 0.01 / data->zoom;
	if (key == 65362)
		data->move_y += 0.01 / data->zoom;
	if (key == 65364)
		data->move_y -= 0.01 / data->zoom;
	if (key == 45)
		reset_values(data);
	if (key == 44)
		data->zoom += 10;
	if (key == 46 && data->zoom > 0)
		data->zoom -= 10;
	if (key == 50)
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img_ptr, 0, 0);
	printf("Keyboard move_x %f move_y %f zoom: %f\n", data->move_x,data->move_y, data->zoom);

	empty_image(data);
	return (1);
}
