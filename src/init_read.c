/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 02:17:59 by ahorker           #+#    #+#             */
/*   Updated: 2019/08/12 20:41:34 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_fdf(t_fdf *fdf)
{
	int i;

	fdf->t = (double **)ft_memalloc(sizeof(double *) * 5);
	fdf->t[4] = NULL;
	i = 0;
	while (i < 4)
		fdf->t[i++] = (double *)ft_memalloc(sizeof(double) * 4);
	fdf->p[0] = 1;
	fdf->p[1] = 0;
	fdf->p[2] = 0;
	fdf->p[3] = 1;
	fdf->p[4] = 1;
	fdf->p[5] = 1;
	fdf->p[6] = -.005;
	fdf->p[7] = 6;
	fdf->p[8] = 0;
	fdf->p[9] = 0;
	fdf->p[10] = 1;
	fdf->p[11] = 10;
	fdf->p[12] = 1;
	fdf->p[13] = 1;
	transformation(fdf);
}

char	**read_map_helper(t_fdf *fdf, char *filename)
{
	int				file;
	long long int	bs;
	char			*big_line;
	char			**lns;

	file = open(filename, O_RDONLY);
	if (file < 0)
		print_usage(1);
	if ((big_line = (char *)malloc(sizeof(char) * 10000000)) == NULL)
		print_usage(2);
	bs = read(file, big_line, 10000000);
	big_line[bs] = '\0';
	fdf->extra[0] = ft_atoi(big_line);
	fdf->extra[1] = fdf->extra[0];
	if ((lns = ft_strsplit(big_line, '\n')) == NULL)
	{
		free(big_line);
		print_usage(2);
	}
	fdf->sz[1] = ft_wrdcount(big_line, '\n');
	fdf->sz[0] = ft_wrdcount(lns[0], ' ');
	free(big_line);
	fdf->map = (int **)ft_memalloc(sizeof(int *) * (fdf->sz[1] + 1));
	fdf->img = (t_vec **)ft_memalloc(sizeof(t_vec *) * (fdf->sz[1] + 1));
	return (lns);
}

int		set_colors(t_fdf *fdf)
{
	long long int	i;
	long long int	j;
	long long int	p;
	t_vec			pnt[4];

	pnt[1].color = fdf->c[0];
	pnt[2].color = fdf->c[1];
	pnt[1].x = fdf->extra[0];
	pnt[2].x = fdf->extra[1];
	pnt[3].y = 0;
	pnt[3].x = pnt[3].y + 1;
	i = -1;
	while (++i < fdf->sz[1])
	{
		j = -1;
		while (++j < fdf->sz[0])
		{
			pnt[0].x = fdf->map[i][j];
			p = get_color(pnt[0], pnt[1], pnt[2], pnt[3]);
			fdf->img[i][j].color = p;
		}
	}
	return (1);
}

void	extra_find(t_fdf *fdf, long long int i[2])
{
	if (fdf->extra[0] > fdf->map[i[0]][i[1]])
		fdf->extra[0] = fdf->map[i[0]][i[1]];
	else if (fdf->extra[1] < fdf->map[i[0]][i[1]])
		fdf->extra[1] = fdf->map[i[0]][i[1]];
}

int		read_map(t_fdf *fdf, char *filename)
{
	long long int	i[2];
	char			**lns[3];
	char			*p;

	lns[0] = read_map_helper(fdf, filename);
	i[0] = -1;
	while (lns[0][++(i[0])])
	{
		fdf->map[i[0]] = ft_memalloc(sizeof(int) * (fdf->sz[0] + 1));
		fdf->img[i[0]] = ft_memalloc(sizeof(t_vec) * (fdf->sz[0] + 1));
		if ((lns[1] = ft_strsplit(lns[0][i[0]], ' ')) == NULL)
			print_usage(2);
		i[1] = -1;
		while (lns[1][++(i[1])])
		{
			fdf->map[i[0]][i[1]] = ft_atoi(lns[1][i[1]]);
			p = ft_strchr(lns[1][i[1]], ',');
			fdf->img[i[0]][i[1]].color = p ?
				strtol(p + 1, NULL, 0) : fdf->c[0];
			extra_find(fdf, i);
		}
		ft_free2d((void ***)(&lns[1]));
	}
	ft_free2d((void ***)&lns[0]);
	return (fdf->c[0] == fdf->c[1] ? 1 : set_colors(fdf));
}
