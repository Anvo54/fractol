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
# define USAGE "Example usage: ./fractol julia\nValid arguments\n\nmandelbrot \
	\njulia"
# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <pthread.h>

typedef	struct 			s_fractol
{
	double				cIm;
	double				cRe;
	double				old_r_n;
	double				old_im_n;
	double				new_real_n;
	double				new_im_n;
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
	int					prev_x;
	int					prev_y;
	double				move_x;
	double				move_y;
	char				*selected_f;
	int					max_iterations;
	int					*reds;
	int					*greens;
	int					*blues;
	t_fractol			fract;
}						t_mlx_data;


int						deal_key(int key, t_mlx_data *data);
void					add_pixel(t_mlx_data *fractol, int x, int y, int color);
/*void					draw(t_coords p1, t_coords p2, t_mlx_data *data);*/
double					percent(int start, int end, int current);
int						get_light(int start, int end, double percentage);
int						point_color(int minz, int maxz, int curz);
/*int						get_color(t_coords cur, t_coords start, t_coords end, t_line del);*/
#endif
