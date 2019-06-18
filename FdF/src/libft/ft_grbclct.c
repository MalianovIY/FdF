/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_grbclct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:23:58 by ahorker           #+#    #+#             */
/*   Updated: 2018/12/19 20:56:12 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	cmp(void *data, t_list elem)
{
	if (data == elem.content)
		return (1);
	else
		return (0);
}

static void	*mal(t_list **mlc, size_t size)
{
	t_list	*f;

	if (size == 0)
		return (NULL);
	if (!(f = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!(f->content = (void *)malloc(size)))
		return (NULL);
	f->content_size = size;
	f->next = NULL;
	ft_lstadd(mlc, f);
	return (f->content);
}

void		*ft_grbclct(int act, size_t size, void *ptr)
{
	static t_list	*mlc = NULL;
	t_list			*f;

	f = NULL;
	if (act == 1)
		return (mal(&mlc, size));
	else if (act == 2)
	{
		if (ptr != NULL)
		{
			ft_free(&((f = ft_lstsearch(mlc, cmp, (void *)ptr))->content));
			ft_lstdelemp(&mlc, f);
		}
		return (ptr);
	}
	else if (act == 0)
		while (mlc)
		{
			ft_free(mlc->content);
			ft_lstdelemp(&mlc, mlc);
		}
	return ((void *)mlc);
}
