/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_smooth_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhagrave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:05:51 by fhagrave          #+#    #+#             */
/*   Updated: 2019/08/05 18:05:51 by fhagrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_smooth_line_with_x_leading_axis(t_fdf *fdf, t_vec start, t_vec end,
				t_vec dlt)
{
	t_vec				current;
	t_vec				d;
	t_pixel_position	supporting_pixel_position;
	t_2pixel_data		pixels;
	long long int		err;

	init_vars(&current, &d, start, end);
	pixels.delta = dlt.x;
	err = 0;
	while (current.x != end.x)
	{
		current.color = get_color(current, start, end, dlt);
		supporting_pixel_position = get_support_pix_posit(start, end, err, dlt);
		pixels.error = err;
		put_2_split_pixels(supporting_pixel_position, fdf, current, pixels);
		err += dlt.y;
		if (2 * err > dlt.x)
		{
			current.y += d.y;
			err -= dlt.x;
		}
		current.x += d.x;
	}
	current.color = get_color(current, start, end, dlt);
	draw_point(fdf, current.x, current.y, (signed)current.color);
}

void	draw_smooth_line_with_y_leading_axis(t_fdf *fdf, t_vec start, t_vec end,
				t_vec dlt)
{
	t_vec				current;
	t_vec				d;
	t_pixel_position	supporting_pixel_position;
	t_2pixel_data		pixels;
	long long int		err;

	init_vars(&current, &d, start, end);
	pixels.delta = dlt.y;
	err = 0;
	while (current.y != end.y)
	{
		current.color = get_color(current, start, end, dlt);
		supporting_pixel_position = get_support_pix_posit(start, end, err, dlt);
		pixels.error = err;
		put_2_split_pixels(supporting_pixel_position, fdf, current, pixels);
		err += dlt.x;
		if (2 * err > dlt.y)
		{
			current.x += d.x;
			err -= dlt.y;
		}
		current.y += d.y;
	}
	current.color = get_color(current, start, end, dlt);
	draw_point(fdf, current.x, current.y, (signed)current.color);
}

void	smooth_line(t_fdf *fdf, t_vec start, t_vec end)
{
	t_vec delta;

	delta.x = ABS_MINUS(start.x, end.x);
	delta.y = ABS_MINUS(start.y, end.y);
	if (delta.y == 0)
		draw_line_with_x_leading_axis(fdf, start, end, delta);
	else if (delta.x == 0 || delta.x == delta.y)
		draw_line_with_y_leading_axis(fdf, start, end, delta);
	else
	{
		if (delta.x > delta.y)
			draw_smooth_line_with_x_leading_axis(fdf, start, end, delta);
		else
			draw_smooth_line_with_y_leading_axis(fdf, start, end, delta);
	}
}
