/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void			iso(int *x, int *y, int z)
{
	int			previous_x;
	int			previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void			rotate_x(int *y, int *z, t_mlx_data *data)
{
	int			previous_y;
	int			previous_z;

	previous_y = *y;
	previous_z = *z;
	*y = previous_y * cos(data->rotate_x) + previous_z * sin(data->rotate_x);
	*z = -previous_y * sin(data->rotate_x) + previous_z * cos(data->rotate_x);
}

void			rotate_z(int *x, int *y, t_mlx_data *data)
{
	int			previous_x;
	int			previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(data->rotate_z) + -previous_y * sin(data->rotate_z);
	*y = previous_x * sin(data->rotate_z) + previous_y * cos(data->rotate_z);
}

void			rotate_y(int *x, int *z, t_mlx_data *data)
{
	int	previous_x;

	previous_x = *x;
	*x = previous_x * cos(data->rotate_y) + *z * sin(data->rotate_y);
	*z = -previous_x * sin(data->rotate_y) + *z * cos(data->rotate_y);
}

void			perspect(t_coords *out)
{
	float		near;
	float		far;
	float		scale;
	float		w;
	t_coords	*in;

	far = 90;
	near = 1.2;
	scale = 1 / tan(35 * 0.5 * M_PI / 180);
	in = out;
	out->x += in->x * scale;
	out->y += in->y * scale;
	out->z += (in->z -= 10000) * -far / (far - near);
	w = in->z;
	if (w >= near)
	{
		out->x /= w;
		out->y /= w;
		out->z /= w;
	}
}
