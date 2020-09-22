/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

t_coords		render(t_coords *point, t_mlx_data *data, t_coords cord)
{
	point->x = cord.x;
	point->z = cord.z;
	point->y = cord.y;
	point->x += data->translate_x;
	point->y += data->translate_y;
	return (*point);
}

int				print_map(t_map *map, t_mlx_data data)
{
	int			i;
	int			j;
	t_coords	tmp;
	t_coords	tmp1;

	i = 0;
	while (i <= map->height)
	{
		j = 0;
		while (j <= map->width)
		{
			if (j != map->width)
				draw(render(&tmp, &data, map->coords[i][j]),
					render(&tmp1, &data, map->coords[i][j + 1]), &data);
			if (i != map->height)
				draw(render(&tmp, &data, map->coords[i][j]),
					render(&tmp1, &data, map->coords[i + 1][j]), &data);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.img_ptr, 0, 0);
	return (0);
}
