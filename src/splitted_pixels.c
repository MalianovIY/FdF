/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitted_pixels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhagrave <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 18:05:51 by fhagrave          #+#    #+#             */
/*   Updated: 2019/08/05 18:05:51 by fhagrave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

unsigned int		get_leading_pixel_color(unsigned int basic_color,
							long long int error, long long int delta)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = (basic_color >> 16u) & 0xffu;
	green = (basic_color >> 8u) & 0xffu;
	blue = (basic_color) & 0xffu;
	error = ABS(error);
	if (error >= delta)
	{
		red = (unsigned char)(red * error / delta);
		green = (unsigned char)(green * error / delta);
		blue = (unsigned char)(blue * error / delta);
	}
	else
	{
		red = red - (unsigned char)(red * error / delta);
		green = green - (unsigned char)(green * error / delta);
		blue = blue - (unsigned char)(blue * error / delta);
	}
	return ((0x0cu << 24u) | (red << 16u) | (green << 8u) | blue);
}

unsigned int		get_supporting_pixel_color(unsigned int basic_color,
							long long int error, long long int delta)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	red = (basic_color >> 16u) & 0xffu;
	green = (basic_color >> 8u) & 0xffu;
	blue = (basic_color) & 0xffu;
	error = ABS(error);
	if (error >= delta)
	{
		red = red - (unsigned char)(red * error / delta);
		green = green - (unsigned char)(green * error / delta);
		blue = blue - (unsigned char)(blue * error / delta);
	}
	else
	{
		red = (unsigned char)(red * error / delta);
		green = (unsigned char)(green * error / delta);
		blue = (unsigned char)(blue * error / delta);
	}
	return ((0x0cu << 24u) | (red << 16u) | (green << 8u) | blue);
}

void				put_2_split_pixels(t_pixel_position support_pix, t_fdf *fdf,
							t_vec current, t_2pixel_data pixels)
{
	unsigned int	splitted_color;

	splitted_color = get_leading_pixel_color(current.color,
			pixels.error, pixels.delta);
	draw_point(fdf, current.x, current.y, (signed)splitted_color);
	splitted_color = get_supporting_pixel_color(current.color,
			pixels.error, pixels.delta);
	if (support_pix == after_lead)
		draw_point(fdf, current.x + 1, current.y, (signed)splitted_color);
	else if (support_pix == before_lead)
		draw_point(fdf, current.x - 1, current.y, (signed)splitted_color);
	else if (support_pix == under_lead)
		draw_point(fdf, current.x, current.y - 1, (signed)splitted_color);
	else if (support_pix == over_lead)
		draw_point(fdf, current.x, current.y + 1, (signed)splitted_color);
}

t_pixel_position	get_support_pix_posit(t_vec start, t_vec end,
							long long int error, t_vec delta)
{
	t_pixel_position supporting_pixel_position;

	if (delta.x > delta.y)
	{
		if (end.y > start.y)
			supporting_pixel_position = (error > 0) ? over_lead : under_lead;
		else
			supporting_pixel_position = (error > 0) ? under_lead : over_lead;
	}
	else
	{
		if (end.x > start.x)
			supporting_pixel_position = (error > 0) ? after_lead : before_lead;
		else
			supporting_pixel_position = (error > 0) ? before_lead : after_lead;
	}
	return (supporting_pixel_position);
}
