/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void			add_pixel(t_mlx_data *fractol, int x, int y, int color)
{
	int			i;

	if (x <= fractol->w && x >= 0 && y <= fractol->h && y >= 0)
	{
		i = (x * fractol->bpp / 8) + (y * fractol->size_line);
		fractol->img_data[i] = color;
		fractol->img_data[++i] = color >> 8;
		fractol->img_data[++i] = color >> 16;
	}
}
