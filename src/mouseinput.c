/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouseinput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int		mouse_motion(int x, int y, t_mlx_data *data)
{
	if (!data->pause)
	{
		double perc_x;
		double perc_y;

		perc_x = percent(0, data->w, x);
		perc_y = percent(0, data->h, y);
		data->fract.re = -1 + (2 * perc_x);
		data->fract.im = -1 + (2 * perc_y);
	}
	return   (1);
}

int		mouse_too(int b, int x, int y, t_mlx_data *d)
{
	if (b == 4)
		d->zoom *= 1.5;
	if (b == 5)
		d->zoom /= (d->zoom / 10 < 0.000002) ? 1 : 10;

	if (b == 1)
	{
		if (x > d->w / 2)
			d->move_x += ((double)(x - (d->w / 2)) / d->w * 3) / d->zoom;
		if (x < d->w / 2)
			d->move_x -= -((double)(x - (d->w / 2)) / d->w * 3) / d->zoom;
		if (y > d->h / 2)
			d->move_y += ((double)(y - (d->h / 2)) / d->h * 2) / d->zoom;
		if (y < d->h / 2)
			d->move_y -= -((double)(y - (d->h / 2)) / d->h * 2) / d->zoom;
	}
	return(0);
}
