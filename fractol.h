/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avornane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 15:33:12 by avornane          #+#    #+#             */
/*   Updated: 2020/06/08 16:57:53 by avornane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define BUFFER 4096
# define USAGE "Available parameters: julia, mandelbrot, burning_ship"
# define MIN_C 40
# define MAX_C 255
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef	enum
{
	none,
	julia,
	mandelbrot,
	burning_ship,
}	t_fractal;

typedef	struct			s_fractol
{
	double				im;
	double				re;
	double				x;
	double				y;
}						t_fractol;

typedef struct			s_mlx_data
{
	void				*mlx_ptr;
	void				*mlx_win;
	void				*img_ptr;
	char				*img_data;
	int					h;
	int					w;
	int					bpp;
	int					size_line;
	int					endian;
	int					pause;
	double				move_x;
	double				move_y;
	double				zoom;
	int					max_i;
	int					*color;
	int					rgb[3];
	t_fractal			selected;
	t_fractol			fract;
}						t_mlx_data;

int						deal_key(int key, t_mlx_data *data);
int						mouse_motion(int x, int y, t_mlx_data *data);
int						mouse_zoom(int b, int x, int y, t_mlx_data *d);
void					add_pixel(t_mlx_data *fractol, int x, int y, int color);
int						get_color(int a, int r, int g, int b);
double					percent(int start, int end, int current);
void					calculate_colors(t_mlx_data *d);
int						count_fractal(t_mlx_data *d);
#endif
