/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 21:12:10 by ahorker           #+#    #+#             */
/*   Updated: 2019/05/02 21:12:10 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

double		vec_len(t_vec *V)
{
	double	len;
	int		i;

	len = 0;
	i = -1;
	while (++i < 3)
		len += V->c[i] * V->c[i];
	return (sqrt(len));
}

double		vec_scalarmultiply(t_vec V, t_vec U)
{
	double	s;
	int		i;

	s = 0;
	i = -1;
	while (++i < 3)
		s += V.c[i] * U.c[i];
	return (s);
}

t_vec		*vec_normalize(t_vec **V1)
{
	double	len;
	int		i;
	t_vec	*V;

	V = *V1;
	len = vec_len(V);
	i = -1;
	while (++i < 3)
		V->c[i] = V->c[i] / len;
	V->c[3] = V->c[3];
	return (V);
}

t_vec		*vec_subtract(t_vec **V1, t_vec *V2)
{
	t_vec	*V;
	int		i;

	V = *V1;
	i = -1;
	while (++i < 3)
		V->c[i] -= V2->c[i];
	V->c[3] = (V->c[3] + V2->c[3]) >= 1;
	return (V);
}

t_vec		*vec_add(t_vec **V, t_vec *V2)
{
	int		i;
	t_vec	*V1;

	V1 = *V;
	i = -1;
	while (++i < 3)
		V1->c[i] += V2->c[i];
	V1->c[3] = (V1->c[3] + V2->c[3]) >= 1;
	return (V1);
}

t_vec		*vec_multiply(t_vec *V1, t_vec *V2)
{
	t_vec	*V;

	V = (t_vec *)ft_grbclct(1, sizeof(t_vec), NULL);
	V->c[0] = V1->c[1] * V2->c[2] - V1->c[2] * V2->c[1];
	V->c[1] = V1->c[2] * V2->c[0] - V1->c[0] * V2->c[2];
	V->c[2] = V1->c[0] * V2->c[1] - V1->c[1] * V2->c[0];
	V->c[3] = 0;
	return (V);
}

double		***mat_multiply(double **T1, double **T2)
{
	double	**T;
	int		i[3];

	T = (double **)ft_grbclct(1, 4 * sizeof(double *), NULL);
	i[0] = -1;
	while (++i[0] < 4)
	{
		T[i[0]] = (double *)ft_grbclct(1, 4 * sizeof(double), NULL);
		i[1] = -1;
		while (++i[1] < 4)
		{
			T[i[0]][i[1]] = 0;
			i[2] = -1;
			while (++i[2] < 4)
				T[i[0]][i[1]] += T1[i[0]][i[2]] * T2[i[2]][i[1]];
		}
	}
	return (T);
}

t_vec		*mat_pnt_multiply(t_vec *V, double **T)
{
	double	x[4];
	int		i;

	i = -1;
	while (++i < 4)
		x[i] = V->c[0] * T[i][0] + V->c[1] * T[i][1] + V->c[2] * T[i][2] + V->c[3] * T[i][3];
	i = -1;
	while (++i < 4)
		V->c[i] = x[i];
	return (V);
}

t_vec		*vec_mat_multiply(t_vec **V1, double **T)
{
	double	x[4];
	int		i;
	t_vec	*V;

	V = *V1;
	i = -1;
	while (++i < 4)
		x[i] = V->c[0] * T[0][i] + V->c[1] * T[1][i] + V->c[2] * T[2][i] + V->c[3] * T[3][i];
	i = -1;
	while (++i < 4)
		V->c[i] = x[i];
	return (V);
}

t_vec		*vec_alp_multiply(t_vec **V1, LL int alpha)
{
	int		i;
	t_vec	*V;

	V = *V1;
	i = -1;
	while (++i < 3)
		V->c[i] = V->c[i] * alpha;
	return (V);
}

double		**mat_identity()
{
	double	**T;
	int 	i;

	T = (double **)ft_grbclct(1, 4 * sizeof(double *), NULL);
	i = -1;
	while (++i < 4)
	{
		T[i] = (double *)ft_grbclct(1, 4 * sizeof(double), NULL);
		ft_bzero(T[i], 4 * sizeof(double));
		T[i][i] = 1;
	}
	return (T);
}

double		**mat_transpose(double ***T)
{
	int 	i[2];
	double	x;
	double	**T0;

	T0 = *T;
	i[0] = -1;
	while (++i[0] < 4)
	{
		i[1] = -1;
		while (++i[1] < 4)
		{
			x = T0[i[0]][i[1]];
			T0[i[0]][i[1]] = T0[i[1]][i[0]];
			T0[i[1]][i[0]] = x;
		}
	}
	return (T0);
}
static void	*mat_invhlp(double ***T0, double ***T)
{
	double	temp;
	int		i[3];

	i[2] = -1;
	while (++i[2] < 4)
	{
		temp = T0[0][i[2]][i[2]];
		i[1] = -1;
		while (++i[1] < 4)
		{
			T0[0][i[2]][i[1]] /= temp;
			T[0][i[2]][i[1]] /= temp;
		}
		i[0] = i[2];
		while (++i[0] < 4)
		{
			temp = T0[0][i[0]][i[2]];
			while (++i[1] < 4)
			{
				T0[0][i[0]][i[1]] -= T0[0][i[2]][i[1]] * temp;
				T[0][i[0]][i[1]] -= T[0][i[2]][i[1]] * temp;
			}
		}
	}
}

double		**mat_inversion(double ***T0)
{
	double	temp;
	double	**T;
	int		i[3];

	T = mat_identity();
	mat_invhlp(&T0, &T);
	i[2] = 4;
	while (--i[2] > 0)
	{
		i[0] = i[2];
		while (--i[0] >= 0)
		{
			temp = T0[i[0]][i[2]];
			i[1] = -1;
			while (++i[1] < 4)
			{
				T0[i[0]][i[1]] -= T0[i[2]][i[1]] * temp;
				T[i[0]][i[1]] -= T[i[2]][i[1]] * temp;
			}
		}
	}
	return (T);
}

double		**inscene(t_vec posit, t_vec orien)									//result: MODEL matrix
{
	double	**T;
	int		i;

	T = mat_identity();
	i = -1;
	while (++i < 3)
		T[i][3] = posit.c[i];
}

double		**lookat(t_vec *eye, t_vec *center, t_vec *up)						//result: VIEW matrix;
{
	t_vec	*t[4];
	double	**M[2];
	int		i;

	t[3] = vec_subtract(eye, center);
	t[2] = vec_normalize(t[3]);
	ft_grbclct(2, 0, t[3]);
	t[3] = vec_multiply(up, t[2]);
	t[0] = vec_normalize(t[3]);
	ft_grbclct(2, 0, t[3]);
	t[3] = vec_multiply(t[2], t[0]);
	t[1] = vec_normalize(t[3]);
	ft_grbclct(2, 0, t[3]);
	M[0] = mat_identity();
	M[1] = mat_identity();
	i = -1;
	while (++i < 3)
	{
		M[0][i] = t[i];
		M[1][i][3] = -center->c[i];
	}
	return(mat_multiply(M[0], M[1]));
}

double		**project(double r)													//resault: PROJECTION matrix
{
	double	**T;

	T = mat_identity();
	T[3][2] = r;
	return (T);
}

t_vec	*prj4D_3D(t_vec **V)
{
	int		i;

	i = -1;
	while (++i < 3)
		(*V)->c[i] /= (*V)->c[3];
}

double	**toscreen(int scr[5])													//result: VIEWPORT matrix
{
	double	**m;

	m = mat_identity();
	m[0][3] = scr[0] + scr[2] / 2;
	m[1][3] = scr[1] + scr[3] / 2;
	m[2][3] = scr[4] / 2;
	m[0][0] = scr[2] / 2;
	m[1][1] = scr[3] / 2;
	m[2][2] = scr[4] / 2;
	return (m);
}
                                                                                                                                           