/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 02:11:51 by ahorker           #+#    #+#             */
/*   Updated: 2019/08/12 20:28:51 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	vec_norm(double *a, double *b, double *c)
{
	double	len;

	len = sqrt(pow(*a, 2.0) + pow(*b, 2.0) + pow(*c, 2.0));
	if (len != 0 && len != 1)
	{
		*a = *a / len;
		*b = *b / len;
		*c = *c / len;
	}
	if (len == 0)
		*a = 1;
}

void	gram_schmidt(double *a, double *b)
{
	double x[2];

	x[0] = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	x[1] = b[0] * b[0] + b[1] * b[1] + b[2] * b[2];
	x[0] /= x[1];
	a[0] = a[0] - b[0] * x[0];
	a[1] = a[1] - b[1] * x[0];
	a[2] = a[2] - b[2] * x[0];
}

void	vec_multiply(double *a, double *b, double *c)
{
	*c = a[1] * b[2] - a[2] * b[1];
	*(c + 1) = a[2] * b[0] - a[0] * b[2];
	*(c + 2) = a[0] * b[1] - a[1] * b[0];
}

void	transformation(t_fdf *fdf)
{
	double	tmp[3];
	int		i[2];

	vec_norm(&(fdf->p[8]), &(fdf->p[9]), &(fdf->p[10]));
	gram_schmidt(&(fdf->p[0]), &(fdf->p[8]));
	vec_norm(&(fdf->p[0]), &(fdf->p[1]), &(fdf->p[2]));
	vec_multiply(&(fdf->p[8]), &(fdf->p[0]), tmp);
	i[0] = -1;
	while (++i[0] < 3)
	{
		ft_bzero(fdf->t[i[0]], sizeof(double) * 4);
		fdf->t[i[0]][0] = tmp[i[0]];
		fdf->t[i[0]][1] = fdf->p[i[0]];
		fdf->t[i[0]][2] = fdf->p[i[0] + 8];
		fdf->t[i[0]][3] = fdf->p[i[0] + 3];
		fdf->t[3][i[0]] = fdf->t[i[0]][2] * fdf->p[6];
	}
	fdf->t[3][3] = fdf->p[7];
	vec_norm(&(fdf->t[0][0]), &(fdf->t[1][0]), &(fdf->t[2][0]));
	vec_norm(&(fdf->t[0][1]), &(fdf->t[1][1]), &(fdf->t[2][1]));
	vec_norm(&(fdf->t[0][2]), &(fdf->t[1][2]), &(fdf->t[2][2]));
}

void	matrix_multiply(t_fdf *fdf)
{
	long long int	i;
	long long int	j;

	i = -1;
	while (++i < fdf->sz[1])
	{
		j = -1;
		while (++j < fdf->sz[0])
		{
			fdf->img[i][j].h = fdf->t[3][3] + fdf->t[3][1] * i +
					fdf->t[3][0] * j + fdf->t[3][2] * fdf->map[i][j];
			fdf->img[i][j].y = round((fdf->t[0][3]
					+ fdf->t[0][0] * fdf->p[11] * (i - fdf->sz[1] / 2)
					+ fdf->t[0][1] * fdf->p[11] * (j - fdf->sz[0] / 2)
					- fdf->t[0][2] * fdf->p[12] * fdf->map[i][j])
					/ (fdf->img[i][j].h)) + 540;
			fdf->img[i][j].x = round((fdf->t[1][3]
					+ fdf->t[1][0] * fdf->p[11] * (i - fdf->sz[1] / 2)
					+ fdf->t[1][1] * fdf->p[11] * (j - fdf->sz[0] / 2)
					- fdf->t[1][2] * fdf->p[12] * fdf->map[i][j])
					/ (fdf->img[i][j].h)) + 360;
		}
	}
}
