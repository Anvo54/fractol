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

int		mousething(int x, int y, t_mlx_data *data)
{
	if (!data->pause)
	{
		double perc_x = percent(0, data->width, x);
		double perc_y = percent(0, data->height, y);
		data->fract.cRe = -1 + (2 * perc_x);
		data->fract.cIm = -1 + (2 * perc_y);
	}
	return(1);
}
