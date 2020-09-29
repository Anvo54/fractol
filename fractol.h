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
# define USAGE "Available parameters: julia, mandelbrot, burning_ship \
	\n\nExample: ./fractol julia\n"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>
#include <stdio.h>

typedef	enum
{
	julia,
	mandelbrot,
	burning_ship,
}		fractal;

typedef	struct 			s_fractol
{
	double				cIm;
	double				cRe;
	double				x;
	double				y;
}						t_fractol;

typedef struct			s_mlx_data
{
	void				*mlx_ptr;
	void				*mlx_win;
	void				*img_ptr;
	char				*img_data;
	int					height;
	int					width;
	int					bpp;
	int					size_line;
	int					endian;
	int					pause;
	double				move_x;
	double				move_y;
	double				zoom;
	int					max_iterations;
	int					*color;
	int					rgb[3];
	fractal				selected;
	t_fractol			fract;
}						t_mlx_data;


int						deal_key(int key, t_mlx_data *data);
void					add_pixel(t_mlx_data *fractol, int x, int y, int color);
double					percent(int start, int end, int current);
int						get_color(int a, int r, int g, int b);
int						get_light(int start, int end, double percentage);
int						point_color(int minz, int maxz, int curz);
void					*julia_plot(void *args);
int						mandelbrot_plot(t_mlx_data *d);
int						burning_plot(t_mlx_data *d);
int						count_fractal(t_mlx_data *d);
int						mousething(int x, int y, t_mlx_data *data);
#endif
