/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhagrave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:05:51 by fhagrave          #+#    #+#             */
/*   Updated: 2019/08/05 18:05:51 by fhagrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_vars(t_vec *current, t_vec *d, t_vec start, t_vec end)
{
	current->x = start.x;
	current->y = start.y;
	current->color = start.color;
	d->x = (end.x > start.x) ? 1 : -1;
	d->y = (end.y > start.y) ? 1 : -1;
}

void	draw_line_with_x_leading_axis(t_fdf *fdf, t_vec start, t_vec end,
				t_vec delta)
{
	t_vec			current;
	t_vec			d;
	long long int	error;

	init_vars(&current, &d, start, end);
	error = 0;
	while (current.x != end.x)
	{
		current.color = get_color(current, start, end, delta);
		draw_point(fdf, current.x, current.y, current.color);
		error += delta.y;
		if (2 * error > delta.x)
		{
			current.y += d.y;
			error -= delta.x;
		}
		current.x += d.x;
	}
	current.color = get_color(current, start, end, delta);
	draw_point(fdf, current.x, current.y, current.color);
}

void	draw_line_with_y_leading_axis(t_fdf *fdf, t_vec start, t_vec end,
				t_vec delta)
{
	t_vec			current;
	t_vec			d;
	long long int	error;

	init_vars(&current, &d, start, end);
	error = 0;
	while (current.y != end.y)
	{
		current.color = get_color(current, start, end, delta);
		draw_point(fdf, current.x, current.y, current.color);
		error += delta.x;
		if (2 * error > delta.y)
		{
			current.x += d.x;
			error -= delta.y;
		}
		current.y += d.y;
	}
	current.color = get_color(current, start, end, delta);
	draw_point(fdf, current.x, current.y, current.color);
}

void	line(t_fdf *fdf, t_vec start, t_vec end)
{
	t_vec delta;

	delta.x = ABS_MINUS(start.x, end.x);
	delta.y = ABS_MINUS(start.y, end.y);
	if (delta.x >= delta.y)
		draw_line_with_x_leading_axis(fdf, start, end, delta);
	else
		draw_line_with_y_leading_axis(fdf, start, end, delta);
}
