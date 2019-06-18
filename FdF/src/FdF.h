/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 22:19:38 by ahorker           #+#    #+#             */
/*   Updated: 2019/02/06 19:02:05 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/includes/libft.h"

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# define LL long long

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int 			bpp;
	int 			sl;
	int 			en;
	char			*s;
}					t_mlx;


typedef struct		s_vector
{
	double 			*c;
	long int		p;
}					t_vec;

typedef struct		s_fdf
{
	t_mlx			mlx;
	double			**T;
	double			p[14];
	int				**map;
	int 			extra[2];
	t_vec			**img;
	int 			size[2];
	long int 		col[2];
}					t_fdf;

int					rdmap(t_fdf *X, char *filename);

#endif
