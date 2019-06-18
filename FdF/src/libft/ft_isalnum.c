/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 21:23:58 by ahorker           #+#    #+#             */
/*   Updated: 2018/12/16 06:35:18 by ahorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c <= 'Z') && (c >= 'A'))
		return (1);
	else if ((c >= 'a') && (c <= 'z'))
		return (1);
	else if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}
