/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 22:19:38 by ahorker           #+#    #+#             */
/*   Updated: 2019/02/06 19:02:05 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/includes/libft.h"

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define SC_X				1080
# define SC_Y				720
# define EC					0.00015230484
# define CO					0.99984769515
# define SI					0.01745240643
# define ABS_MINUS(a, b)	((a >= b) ? (a - b) : (b - a))
# define ABS(x)				((x >= 0) ? x : -x)

typedef struct				s_mlx
{
	void					*mlx;
	void					*win;
	void					*img;
	int						bpp;
	int						sl;
	int						en;
	char					*s;
}							t_mlx;

typedef struct				s_vector
{
	long long int			x;
	long long int			y;
	double					h;
	unsigned int			color;
}							t_vec;

typedef struct				s_fdf
{
	t_mlx					mlx;
	double					**t;
	double					p[14];
	int						**map;
	int						extra[2];
	t_vec					**img;
	long long int			sz[2];
	unsigned int			c[2];
}							t_fdf;

typedef struct				s_spatial
{
	long long int			start;
	long long int			end;
	long long int			current;
}							t_spatial;

typedef enum				e_pixel_position
{							under_lead, over_lead, before_lead, after_lead
}							t_pixel_position;

typedef struct				s_2pixel_data
{
	long long int			error;
	long long int			delta;
}							t_2pixel_data;

void						draw_point(t_fdf *fdf, int x, int y, int p);

void						line(t_fdf *fdf, t_vec start, t_vec end);

int							get_color(t_vec cur, t_vec st, t_vec end, t_vec dl);

void						transformation(t_fdf *fdf);

void						vec_multiply(double *a, double *b, double *c);

void						matrix_multiply(t_fdf *fdf);

int							read_map(t_fdf *fdf, char *filename);

void						init_fdf(t_fdf *fdf);

void						choose_distortion(t_fdf *fdf, int key);

void						choose_moving(t_fdf *fdf, int key);

void						choose_rotation(t_fdf *fdf, int key);

void						print_param(t_fdf *fdf);

void						print_map(t_fdf *fdf);

void						print_image(t_fdf *fdf);

void						print_usage(int x);

void						smooth_line(t_fdf *fdf, t_vec start, t_vec end);

int							get_light(int start_color, int end_color,
									t_spatial relative_position);

void						init_vars(t_vec *current, t_vec *d,
									t_vec start, t_vec end);

void						draw_line_with_x_leading_axis(t_fdf *fdf,
									t_vec start, t_vec end, t_vec delta);

void						draw_line_with_y_leading_axis(t_fdf *fdf,
									t_vec start, t_vec end, t_vec delta);

void						draw_smooth_line_with_x_leading_axis(t_fdf *fdf,
									t_vec start, t_vec end, t_vec dlt);

void						draw_smooth_line_with_y_leading_axis(t_fdf *fdf,
									t_vec start, t_vec end, t_vec dlt);

unsigned int				get_leading_pixel_color(unsigned int basic_color,
									long long int error, long long int delta);

unsigned int				get_supporting_pixel_color(
									unsigned int basic_color,
									long long int error, long long int delta);

void						put_2_split_pixels(
									t_pixel_position support_pix, t_fdf *fdf,
									t_vec current, t_2pixel_data pixels);

t_pixel_position			get_support_pix_posit(t_vec start,
									t_vec end, long long int err, t_vec delta);

int							line_show(t_vec p0, t_vec p1);

#endif
