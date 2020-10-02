/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

double		percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int			get_color(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int			get_shade(int min, int max, int cur)
{
	return (MIN_C + (MAX_C - MIN_C) * percent(min, max, cur));
}

void		calculate_colors(t_mlx_data *d)
{
	int		i;
	double	p;

	if (!(d->color = (int*)malloc(sizeof(int) * d->max_i)))
		exit(0);
	i = 0;
	while (i++ <= d->max_i)
	{
		p = percent(0, d->max_i, i);
		if (p <= 0.2)
			d->rgb[0] = get_shade(0, d->max_i * 0.2, i);
		else if (p <= 0.4)
			d->rgb[1] = get_shade(d->max_i * 0.2, d->max_i * 0.4, i);
		else if (p <= 0.6)
			d->rgb[2] = get_shade(d->max_i * 0.4, d->max_i * 0.6, i);
		else if (p <= 0.8)
			d->rgb[0] = MAX_C - get_shade(d->max_i * 0.6, d->max_i * 0.8, i);
		else if (p <= 1.0)
		{
			d->rgb[1] = MAX_C - get_shade(d->max_i * 0.8, d->max_i * 1.0, i);
			d->rgb[2] = MAX_C - get_shade(d->max_i * 0.8, d->max_i * 1.0, i);
		}
		d->color[i] = get_color(MAX_C, d->rgb[0], d->rgb[1], d->rgb[2]);
	}
}
