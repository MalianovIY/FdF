/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 02:39:39 by ahorker           #+#    #+#             */
/*   Updated: 2019/08/09 02:39:39 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_param(t_fdf *fdf)
{
	printf("\n\n%f\t%f\t%f\t%f\t",
			fdf->t[0][0], fdf->t[0][1], fdf->t[0][2], fdf->t[0][3]);
	printf("\n%f\t%f\t%f\t%f\t",
			fdf->t[1][0], fdf->t[1][1], fdf->t[1][2], fdf->t[1][3]);
	printf("\n%f\t%f\t%f\t%f\t",
			fdf->t[2][0], fdf->t[2][1], fdf->t[2][2], fdf->t[2][3]);
	printf("\n%f\t%f\t%f\t%f\t\n\n",
			fdf->t[3][0], fdf->t[3][1], fdf->t[3][2], fdf->t[3][3]);
	printf("%f %f %f %f %f %f %f %f %f %f %f %f %f\n",
			fdf->p[0], fdf->p[1], fdf->p[2], fdf->p[3], fdf->p[4],
			fdf->p[5], fdf->p[6], fdf->p[7], fdf->p[8], fdf->p[9],
			fdf->p[10], fdf->p[11], fdf->p[12]);
}

void	print_map(t_fdf *fdf)
{
	long long int	i;
	long long int	j;

	printf("========================= M A P =========================\n");
	i = -1;
	while (++i < fdf->sz[0])
	{
		j = -1;
		while (++j < fdf->sz[1])
		{
			printf("%4d ", fdf->map[j][i]);
		}
		printf("\n");
	}
	printf("=========================================================\n");
}

void	print_image(t_fdf *fdf)
{
	long long int	i;
	long long int	j;

	printf("========================= I M G =========================\n");
	i = -1;
	while (++i < fdf->sz[0])
	{
		j = -1;
		while (++j < fdf->sz[1])
			printf("(%3.0lld, %3.0lld, %3.0d) ", fdf->img[j][i].x,
					fdf->img[j][i].y, fdf->img[j][i].color);
		printf("\n");
	}
	printf("=========================================================\n");
}

void	print_usage(int x)
{
	if (x == 0)
		write(1, "Usage:\n$ ./FdF map_filename.fdf color_1 color_2\n\n"
				"Note:\n\tColor format 0x000000 .. 0xFFFFFF\n", 90);
	else if (x == 1)
		write(1, "Error reading, can not open file.\n", 34);
	else if (x == 2)
		write(1, "Error memory allocated.\n", 24);
	exit(0);
}

int		line_show(t_vec p0, t_vec p1)
{
	return ((p0.x <= SC_Y - 1 && p0.x > 0 && p0.y <= SC_X - 1 && p0.y > 0) ||
		(p1.x <= SC_Y - 1 && p1.x > 0 && p1.y <= SC_X - 1 && p1.y > 0));
}
