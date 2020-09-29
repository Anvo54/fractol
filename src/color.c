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

int		get_color(int a, int r, int g, int b)
{
	(r < 0) ? r = 0: 0;
	(r > 255) ? r = 255: 0;
	(g < 0) ? r = 0: 0;
	(g > 255) ? r = 255: 0;
	(b < 0) ? r = 0: 0;
	(b > 255) ? r = 255: 0;
	return(a << 24 | r << 16 | g << 8 | b);
}
