/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 21:47:22 by ahorker           #+#    #+#             */
/*   Updated: 2019/01/13 22:08:21 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *c)
{
	char	*s;
	char	*out;

	if (c == NULL)
		return (NULL);
	s = (char *)ft_grbclct(1, ft_strlen(c) + 1, NULL);
	if (s == NULL)
		return (s);
	out = s;
	while (*c)
		*s++ = *c++;
	*s = '\0';
	return (out);
}
