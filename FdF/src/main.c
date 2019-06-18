/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:15:25 by ahorker           #+#    #+#             */
/*   Updated: 2019/04/09 17:24:52 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
//mars 0.802851 1.815144 -3.944445 -30.000000 -70.000000 60.000000 0.000000 -0.001200 0.000330 -0.001310
void	initP(t_fdf *X)
{
	X->p[0] = 0;// - 1.57;//-0.261800;//1.867503;							//tetta
	X->p[1] = M_PI;// - 1.57;// 0.2618000;//0.558506;							//phi
	X->p[2] = M_PI;// + 1.57;//-1.570796;//-2.356194;//-1.832596;					//psi
	X->p[3] = X->size[1];//-.0012;;;									//l
	X->p[4] = X->size[0];											//m
	X->p[5] = X->extra[1] * 2;													//n
	X->p[6] = 1;// -0.002 * (X->size[0] > X->size[1] ? X->size[0] : X->size[1]);//s
	X->p[7] = 0;//-.0012;														//p
	X->p[8] = 0;//.00033;//0;													//q
	X->p[9] = -1/X->p[5];//-.00131;//0;											//r
	X->p[10] = 0;																//tetta_2
	X->p[11] = 0;//.00033;//0;													//phi_2
	X->p[12] = 0;//-.0012;;														//psi_2
	X->p[13] = 1;																// hight maps
}

void	initX(t_fdf *X)
{
	int i;

	X->T = (double **)ft_memalloc(sizeof(double *) * 4);
	i = 0;
	while (i < 5)
		X->T[i++] = (double *)ft_memalloc(sizeof(double) * 4);
	initP(X);
}
										//	0		1		2		3	4	5	6	7	8	9	10		11		12		13
void	trotateX(double ***tx, double a) 	//	tetta,	phi,	psi,	l,	m,	n,	s,	p,	q,	r	tetta2	phi2	psi2	hight
{
	double **T;

	T = *tx;

	T[0][0] = cos(a[1]) * cos(a[2]);
	T[0][1] = cos(a[1]) * sin(a[2]);
	T[0][2] = -sin(a[1]);

	T[1][0] = -cos(a[2]) * sin(a[0]) * sin(a[1]) - cos(a[0]) * sin(a[2]);
	T[1][1] = cos(a[0]) * cos(a[2]) - sin(a[0]) * sin(a[1]) * sin(a[2]);
	T[1][2] = cos(a[1]) * sin(a[0]);

	T[2][0] = sin(a[0]) * sin(a[2]) - cos(a[0]) * cos(a[2]) * sin(a[1]);
	T[2][1] = -cos(a[2]) * sin(a[0]) - cos(a[0]) * sin(a[1]) * sin(a[2]);
	T[2][2] = cos(a[0]) * cos(a[1]);

	T[3][0] = 0;//T[0][0][0] * a[3] + T[0][1][0] * a[4] + T[0][2][0] * a[5];
	T[3][1] = 0;//T[0][0][1] * a[3] + T[0][1][1] * a[4] + T[0][2][1] * a[5];
	T[3][2] = 0;//T[0][0][2] * a[3] + T[0][1][2] * a[4] + T[0][2][2] * a[5];

	T[0][3] = 0;//T[0][0][2] * a[9] + T[0][0][1] * a[8] + T[0][0][0] * a[7];
	T[1][3] = 0;//T[0][1][2] * a[9] + T[0][1][1] * a[8] + T[0][1][0] * a[7];
	T[2][3] = 0;//T[0][2][2] * a[9] + T[0][2][1] * a[8] + T[0][2][0] * a[7];

	T[3][3] = a[6];// + a[5] * a[9] + a[4] * a[8] + a[3] * a[7];
}

void	ttranslate(double ***T, double a[3])
{
	;
}

void	matrixmultiply(t_fdf *X)
{
	int		i, j = 0;

	i = 0;
	while (i < X->size[1])
	{
		j = -1;
		while (++j < X->size[0])
		{
			X->img[i][j].h = X->T[0][3] * (i) +
					X->T[1][3] * (j) + X->T[2][3]
					* (X->p[13] * X->map[i][j]) + X->T[3][3];
			if (X->img[i][j].h < 0.0001)
				continue ;
			X->img[i][j].x = round((X->T[0][0] * (i)
					+ X->T[1][0] * (j) + X->T[2][0]
					* (X->p[13] * X->map[i][j]) + X->T[3][0])
							/ (X->img[i][j].h)) + 0;//- X->img[i][j].z;
			X->img[i][j].y = round((X->T[0][1] * (i)
					+ X->T[1][1] * (j) + X->T[2][1]
					* (X->p[13] * X->map[i][j]) + X->T[3][1])
							/ (X->img[i][j].h)) + 0;//- X->img[i][j].z;
			X->img[i][j].z = round((X->T[0][2] * (i)
					+ X->T[1][2] * (j) + X->T[2][2]
					* (X->p[13] * X->map[i][j]) + X->T[3][2])
							/ (X->img[i][j].h)) + 0;
		}
		i++;
	}
}

int		rdmap(t_fdf *X, char *filename)
{
	int		i, j, file, p;
	LL int	bs;
	char	big_line[7000001];
	char	**lns[3];

	file = open(filename, O_RDONLY);
	bs = read(file, big_line, 7000000);
	big_line[bs] = '\0';
	X->extra[0] = ft_atoi(big_line);
	X->extra[1] = X->extra[0];
	lns[0] = ft_strsplit(big_line, '\n');
	X->size[1] = 0;
	while (lns[0][X->size[1]])
		X->size[1]++;
	lns[1] = ft_strsplit(lns[0][0], ' ');
	X->size[0] = 0;
	while (lns[1][X->size[0]])
		X->size[0]++;
	X->map = (int **)ft_memalloc(sizeof(int *) * (X->size[1] + 1));
	X->img = (t_vec **)ft_memalloc(sizeof(t_vec *) * (X->size[1] + 1));
	i = -1;
	while (lns[0][++i])
	{
		X->map[i] = ft_memalloc(sizeof(int) * (X->size[0] + 1));
		X->img[i] = ft_memalloc(sizeof(t_vec) * (X->size[0] + 1));
		lns[1] = ft_strsplit(lns[0][i], ' ');
		j = -1;
		while (lns[1][++j])
		{
			lns[2] = ft_strsplit(lns[1][j], ',');
			p = ft_strchr(lns[1][j], ',') != NULL;
			X->img[i][j].p = p ? strtol(lns[2][1], NULL, 0) : 0xFFFFFF;
			X->map[i][j] = ft_atoi(lns[2][0] == NULL ? lns[1][j] : lns[2][0]);
			if (X->extra[0] > X->map[i][j])
				X->extra[0] = X->map[i][j];
			else if (X->extra[1] < X->map[i][j])
				X->extra[1] = X->map[i][j];
		}
	}
	if (!p)
	{
		i = -1;
		while (++i < X->size[1])
		{
			j = -1;
			while (++j < X->size[0])
			{
				p = 255 * (16 - (X->map[i][j] - X->extra[0]) /
						(X->extra[1] - X->extra[0] + 0.0));
				p = p > 255 ? 255 : p;
				//printf("%d\n",p);
				X->img[i][j].p = (p << 16) | (p << 8) | (p);
			}
		}
	}
	return (1);
}

int		draw(t_fdf *X)
{
	int		i, j, ind;

	i = 0;
	while (i < X->size[1])
	{
		j = -1;
		while (++j < X->size[0])
		{
			if (X->img[i][j].y >= 999 || X->img[i][j].y <= 0
			        || X->img[i][j].x >= 999 || X->img[i][j].x <= 0)
				continue ;
			ind = 4 * X->img[i][j].y + X->mlx.sl * 1 * X->img[i][j].x;
			X->mlx.s[ind] = X->img[i][j].p & 0xFF;
			X->mlx.s[ind + 1] = X->img[i][j].p >> 8 & 0xFF;
			X->mlx.s[ind + 2] = X->img[i][j].p >> 16 & 0xFF;
		}
		//printf("\n");
		i++;
	}
	printf("tet\t\t\t phi\t\t  psi\t\t   l\t\t\t m\t\t\t   n\t\t    s\t\t\t p\t\t\t  q\t\t\t   r\t\t\t x\t\t\t  y\t\t\t   z\n");
	printf("%e %e %e %e %e %e %e %e %e %e %e %e %e\n", X->p[0], X->p[1], X->p[2], X->p[3], X->p[4], X->p[5], X->p[6], X->p[7], X->p[8], X->p[9], X->p[10], X->p[11], X->p[12]);
	return (1);
}
									//	  0		 1		 2		3	4	5	6	7
void	choosekey(t_fdf *X, int key)//	tetta,	phi,	psi,	l,	m,	n,	s,	r
{
	double x[4];

	if (key == 53)
		exit(0);
	if (key == 71)
		X->p[9] = 0;
	if (key == 36)
		initP(X);
	if (key == )
//	if (key == 43)	//psi +
//		X->p[2] -= 0.0174533;
//	if (key == 47)	//psi -
//		X->p[2] += 0.0174533;
//	if (key == 123)	//tetta +
//		X->p[0] += 0.0174533;
//	if (key == 124)	//tetta -
//		X->p[0] -= 0.0174533;
//	if (key == 126) //phi -
//		X->p[1] += 0.0174533;
//	if (key == 125)	//phi +
//		X->p[1] -= 0.0174533;
//	if (key == 116)	//l +
//		X->p[3] += 10;
//	if (key == 121)	//l -
//		X->p[3] -= 10;
//	if (key == 86)	//m -
//		X->p[4] -= 10;
//	if (key == 88)	//m +
//		X->p[4] += 10;
//	if (key == 87)	//n +
//		X->p[5] += 10;
//	if (key == 91)	//n -
//		X->p[5] -= 10;
//	if (key == 115)	//x +
//	{
//		x[3] = 1 * X->T[0][3];//X->T[3][3];
//		x[2] = 1 * X->T[0][2];//X->T[3][2];
//		x[1] = 1 * X->T[0][1];//X->T[3][1];
//		x[0] = 1 * X->T[0][0];//X->T[3][0];
//		X->p[10] +=  x[0];
//		X->p[11] +=  x[1];
//		X->p[12] +=  x[2];
//
//	}
//	if (key == 119)	//x -
//	{
//		x[3] = 1 * X->T[0][3];//X->T[3][3];
//		x[2] = 1 * X->T[0][2];//X->T[3][2];
//		x[1] = 1 * X->T[0][1];//X->T[3][1];
//		x[0] = 1 * X->T[0][0];//X->T[3][0];
//		X->p[10] -=  x[0];
//		X->p[11] -=  x[1];
//		X->p[12] -=  x[2];
//	}
//	if (key == 2)	//y -
//	{
//		x[3] = 1 * X->T[1][3];//X->T[3][3];
//		x[2] = 1 * X->T[1][2];//X->T[3][2];
//		x[1] = 1 * X->T[1][1];//X->T[3][1];
//		x[0] = 1 * X->T[1][0];//X->T[3][0];
//		X->p[10] +=  x[0];
//		X->p[11] +=  x[1];
//		X->p[12] +=  x[2];
//	}
//	if (key == 0)	//y +
//	{
//		x[3] = 1 * X->T[1][3];//X->T[3][3];
//		x[2] = 1 * X->T[1][2];//X->T[3][2];
//		x[1] = 1 * X->T[1][1];//X->T[3][1];
//		x[0] = 1 * X->T[1][0];//X->T[3][0];
//		X->p[10] -=  x[0];
//		X->p[11] -=  x[1];
//		X->p[12] -=  x[2];
//	}
//	if (key == 13)	//z +
//	{
//		x[3] = 1 * X->T[2][3];//X->T[3][3];
//		x[2] = 1 * X->T[2][2];//X->T[3][2];
//		x[1] = 1 * X->T[2][1];//X->T[3][1];
//		x[0] = 1 * X->T[2][0];//X->T[3][0];
//		X->p[10] +=  x[0];
//		X->p[11] +=  x[1];
//		X->p[12] +=  x[2];
//	}
//	if (key == 1)	//z -
//	{
//		x[3] = 1 * X->T[2][3];//X->T[3][3];
//		x[2] = 1 * X->T[2][2];//X->T[3][2];
//		x[1] = 1 * X->T[2][1];//X->T[3][1];
//		x[0] = 1 * X->T[2][0];//X->T[3][0];
//		X->p[10] -=  x[0];
//		X->p[11] -=  x[1];
//		X->p[12] -=  x[2];
//	}
////	if (key == 86)	//p -
////		X->p[7] -=0.00001;				//perspective transform: mb add move? check zoom in perspective
////	if (key == 89)	//p +
////		X->p[7] +=0.00001;
////	if (key == 87)	//q -
////		X->p[8] -=0.00001;
////	if (key == 91)	//q +
////		X->p[8] +=0.00001;
//	if (key == 25)	//r -
//		X->p[13] += 1;
//	if (key == 29)	//r +
//		X->p[13] -= 1;
//	if (key == 78)	//r -
//		X->p[9] -=0.00001;
//	if (key == 69)	//r +
//		X->p[9] +=0.00001;
//	if (key == 7)	//s -
//	{
//		if (X->p[6] - .1 > X->p[6] || X->p[6] - .1 == 0)
//			return ;
//		X->p[6] -= 0.1;
//		X->p[3] -= 0;
//		X->p[4] -= 0;
//	}
//	if (key == 6)	//s +
//	{
//		if (X->p[6] + .1 < X->p[6] || X->p[6] + .1 == 0)
//			return ;
//		X->p[6] += 0.1;
//		X->p[3] += 0;
//		X->p[4] += 0;
//	}
}

int	deal_key(int key, void *param)
{
	t_fdf	*X;

	X = (t_fdf*)param;
	choosekey(X, key);

	X->mlx.img = mlx_new_image(X->mlx.mlx, 1000, 1000);
	X->mlx.s = mlx_get_data_addr(X->mlx.img, &(X->mlx.bpp), &(X->mlx.sl), &(X->mlx.en));

	tr(&(X->T), X->p);
	matrixmultiply(X);
	draw(X);
	mlx_clear_window(X->mlx.mlx, X->mlx.win);
	mlx_put_image_to_window(X->mlx.mlx, X->mlx.win, X->mlx.img, 0, 0);
	mlx_destroy_image(X->mlx.mlx, X->mlx.img);
	return (0);
}

int main(int argc, char *argv[])
{
	t_fdf	X;

	if (argc != 1)
	{
		X.col[0] = argc > 2 ? strtol(argv[2], NULL, 0) : -1;
		X.col[1] = argc > 3 ? strtol(argv[3], NULL, 0) : -1;
		rdmap(&X, argv[1]);
		initX(&X);
		X.mlx.mlx = mlx_init();
		X.mlx.win = mlx_new_window(X.mlx.mlx, 1000, 1000, "FdF");
		mlx_hook(X.mlx.win, 2, 5, deal_key, &X);
		mlx_loop(X.mlx.mlx);
	}
	return (0);
}