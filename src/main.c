/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:15:25 by ahorker           #+#    #+#             */
/*   Updated: 2019/08/12 20:41:15 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_point(t_fdf *fdf, int x, int y, int p)
{
	int ind;

	if (y > SC_X - 1 || y <= 0 || x > SC_Y - 1 || x <= 0)
		return ;
	ind = 4 * y + fdf->mlx.sl * 1 * x;
	fdf->mlx.s[ind] = p & 0xFF;
	fdf->mlx.s[ind + 1] = p >> 8 & 0xFF;
	fdf->mlx.s[ind + 2] = p >> 16 & 0xFF;
}

int		draw(t_fdf *fdf, void (*f)(t_fdf *fdf, t_vec start, t_vec end))
{
	long long int	i;
	long long int	j;

	i = 0;
	while (++i < fdf->sz[1])
	{
		j = 0;
		while (++j < fdf->sz[0])
		{
			if (line_show(fdf->img[i][j], fdf->img[i][j - 1]))
				f(fdf, fdf->img[i][j], fdf->img[i][j - 1]);
			if (line_show(fdf->img[i][j], fdf->img[i - 1][j]))
				f(fdf, fdf->img[i][j], fdf->img[i - 1][j]);
		}
	}
	i = 0;
	while (++i < fdf->sz[0])
		if (line_show(fdf->img[0][i], fdf->img[0][i - 1]))
			f(fdf, fdf->img[0][i], fdf->img[0][i - 1]);
	i = 0;
	while (++i < fdf->sz[1])
		if (line_show(fdf->img[i][0], fdf->img[i - 1][0]))
			f(fdf, fdf->img[i][0], fdf->img[i - 1][0]);
	return (1);
}

void	choose_key(t_fdf *fdf, int key)
{
	if (key == 123 || key == 124 || key == 125 || key == 126
			|| key == 12 || key == 14)
		choose_rotation(fdf, key);
	if (key == 53)
	{
		ft_free2d((void ***)&(fdf->t));
		ft_free2d((void ***)&(fdf->map));
		ft_free2d((void ***)&(fdf->img));
		exit(0);
	}
	if (key == 36)
	{
		print_image(fdf);
		print_map(fdf);
		print_param(fdf);
	}
	if (key == 6 || key == 7 || key == 18 || key == 19 || key == 20 || key == 21
			|| key == 78 || key == 69 || key == 67)
		choose_distortion(fdf, key);
	if (key == 76)
		init_fdf(fdf);
	if (key == 0 || key == 1 || key == 2 || key == 13
			|| key == 8 || key == 49)
		choose_moving(fdf, key);
}

int		deal_key(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf*)param;
	choose_key(fdf, key);
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, SC_X, SC_Y);
	fdf->mlx.s = mlx_get_data_addr(fdf->mlx.img, &(fdf->mlx.bpp),
		&(fdf->mlx.sl), &(fdf->mlx.en));
	transformation(fdf);
	matrix_multiply(fdf);
	(fdf->p[13] > 0) ? draw(fdf, line) : draw(fdf, smooth_line);
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 1)
	{
		fdf.c[0] = argc > 2 ? strtol(argv[2], NULL, 0) : 0xFFFFFF;
		fdf.c[1] = argc > 3 ? strtol(argv[3], NULL, 0) : fdf.c[0];
		read_map(&fdf, argv[1]);
		init_fdf(&fdf);
		fdf.mlx.mlx = mlx_init();
		fdf.mlx.win = mlx_new_window(fdf.mlx.mlx, SC_X, SC_Y, "FdF");
		fdf.mlx.img = mlx_new_image(fdf.mlx.mlx, SC_X, SC_Y);
		fdf.mlx.s = mlx_get_data_addr(fdf.mlx.img,
			&(fdf.mlx.bpp), &(fdf.mlx.sl), &(fdf.mlx.en));
		transformation(&fdf);
		matrix_multiply(&(fdf));
		(fdf.p[13] > 0) ? draw(&fdf, line) : draw(&fdf, smooth_line);
		mlx_clear_window(fdf.mlx.mlx, fdf.mlx.win);
		mlx_put_image_to_window(fdf.mlx.mlx, fdf.mlx.win, fdf.mlx.img, 0, 0);
		mlx_destroy_image(fdf.mlx.mlx, fdf.mlx.img);
		mlx_hook(fdf.mlx.win, 2, 5, deal_key, &fdf);
		mlx_loop(fdf.mlx.mlx);
	}
	else
		print_usage(0);
	return (0);
}
