/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/08/03 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include "../libft/libft.h"

void			get_z_value(t_coords *coord, char *val, t_mlx_data *data)
{
	char		**str;
	int			i;

	i = 0;
	str = ft_strsplit(val, ',');
	coord->z = ft_atoi(str[0]);
	coord->color = (str[1]) ? ft_hextoint(str[1]) : -1;
	data->min = (data->min > coord->z) ? coord->z : data->min;
	data->max = (data->max < coord->z) ? coord->z : data->max;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_coords		*convert(char **line, int y, int x, t_mlx_data *data)
{
	int			i;
	int			j;
	t_coords	*map_line;

	i = 0;
	j = 0;
	while (line[i])
		i++;
	if (i - 1 != x)
	{
		write(1, "Map width error!\n", 17);
		exit(0);
	}
	map_line = (t_coords*)malloc(i * sizeof(t_coords));
	while (j < i)
	{
		map_line[j].y = y * 10;
		map_line[j].x = (j - ((i - 1) / 2)) * 10;
		get_z_value(&map_line[j], line[j], data);
		free(line[j]);
		j++;
	}
	free(line);
	return (map_line);
}

void			read_coords(int fd, t_mlx_data *data, t_map *map)
{
	char		**charmap;
	char		*count;
	int			y;
	int			i;

	y = 0;
	i = 0;
	charmap = (char**)malloc(sizeof(char*) * BUFFER);
	while (get_next_line(fd, &charmap[y]))
		y++;
	map->height = y - 1;
	count = ft_strtrim(charmap[0]);
	map->width = ft_count_char(count, ' ');
	free(count);
	map->coords = (t_coords**)malloc(y * sizeof(t_coords*));
	while (i < y)
	{
		map->coords[i] = convert(ft_strsplit(charmap[i], ' '),
			i - ((y - 1) / 2), map->width, data);
		free(charmap[i]);
		i++;
	}
	free(charmap);
}
