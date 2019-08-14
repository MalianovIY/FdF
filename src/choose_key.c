/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 02:20:12 by ahorker           #+#    #+#             */
/*   Updated: 2019/08/11 19:03:00 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	rotation(double *x, double *v, int p)
{
	double tmp[3];

	tmp[0] = x[0] * (CO + EC * pow(v[0], 2.0))
			+ x[1] * (EC * v[0] * v[1] - p * SI * v[2])
			+ x[2] * (EC * v[0] * v[2] + p * SI * v[1]);
	tmp[1] = x[0] * (EC * v[0] * v[1] + p * SI * v[2])
			+ x[1] * (CO + EC * pow(v[1], 2.0))
			+ x[2] * (EC * v[1] * v[2] - p * SI * v[0]);
	tmp[2] = x[0] * (EC * v[0] * v[2] - p * SI * v[1])
			+ x[1] * (EC * v[1] * v[2] + p * SI * v[0])
			+ x[2] * (CO + EC * pow(v[2], 2.0));
	x[0] = tmp[0];
	x[1] = tmp[1];
	x[2] = tmp[2];
}

void	choose_rotation(t_fdf *fdf, int key)
{
	double	tmp[3];

	if (key == 123)
		rotation(fdf->p + 8, fdf->p, -1);
	if (key == 124)
		rotation(fdf->p + 8, fdf->p, 1);
	if (key == 12)
		rotation(fdf->p, fdf->p + 8, 1);
	if (key == 14)
		rotation(fdf->p, fdf->p + 8, -1);
	if (key == 125)
		vec_multiply(fdf->p, fdf->p + 8, tmp);
	if (key == 126)
		vec_multiply(fdf->p + 8, fdf->p, tmp);
	if (key == 125 || key == 126)
	{
		rotation(fdf->p, tmp, 1);
		rotation(fdf->p + 8, tmp, 1);
	}
}

void	moving(double *x, double *v, int p)
{
	x[0] += v[0] * p;
	x[1] += v[1] * p;
	x[2] += v[2] * p;
}

void	choose_moving(t_fdf *fdf, int key)
{
	double	tmp[3];

	if (key == 8)
		moving(&(fdf->p[3]), &(fdf->p[8]), 1);
	if (key == 49)
		moving(&(fdf->p[3]), &(fdf->p[8]), -1);
	if (key == 0)
		moving(&(fdf->p[3]), &(fdf->p[0]), 1);
	if (key == 2)
		moving(&(fdf->p[3]), &(fdf->p[0]), -1);
	if (key == 13)
		vec_multiply(&(fdf->p[0]), &(fdf->p[8]), tmp);
	if (key == 1)
		vec_multiply(&(fdf->p[8]), &(fdf->p[0]), tmp);
	if (key == 13 || key == 1)
		moving(&(fdf->p[3]), tmp, 1);
}

void	choose_distortion(t_fdf *fdf, int key)
{
	if (key == 6)
		fdf->p[7] -= 0.1;
	if (key == 7)
		fdf->p[7] += 0.1;
	if (key == 18)
		fdf->p[11] -= 0.1;
	if (key == 19)
		fdf->p[11] += 0.1;
	if (key == 20)
		fdf->p[12] -= 0.1;
	if (key == 21)
		fdf->p[12] += 0.1;
	if (key == 78)
		fdf->p[6] -= 0.001;
	if (key == 69)
		fdf->p[6] += 0.001;
	if (key == 67)
		fdf->p[13] = -fdf->p[13];
}
