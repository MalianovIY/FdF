/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhagrave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:05:51 by fhagrave          #+#    #+#             */
/*   Updated: 2019/08/05 18:05:51 by fhagrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	get_light(int start_color, int end_color, t_spatial relative_position)
{
	if (relative_position.end - relative_position.start != 0)
		return (start_color + (relative_position.current -
		relative_position.start) * (end_color - start_color) /
		(relative_position.end - relative_position.start));
	else
		return (start_color / 2 + end_color / 2);
}

int	get_color(t_vec current, t_vec start, t_vec end, t_vec delta)
{
	int			red;
	int			green;
	int			blue;
	t_spatial	relative_position;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
	{
		relative_position.start = start.x;
		relative_position.end = end.x;
		relative_position.current = current.x;
	}
	else
	{
		relative_position.start = start.y;
		relative_position.end = end.y;
		relative_position.current = current.y;
	}
	red = get_light((start.color >> 16) & 0xff, (end.color >> 16) & 0xff,
	relative_position);
	green = get_light((start.color >> 8) & 0xff, (end.color >> 8) & 0xff,
	relative_position);
	blue = get_light(start.color & 0xff, end.color & 0xff, relative_position);
	return ((0x0 << 24) | (red << 16) | (green << 8) | blue);
}
