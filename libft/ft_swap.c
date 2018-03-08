/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 10:40:17 by skamoza           #+#    #+#             */
/*   Updated: 2018/01/31 10:47:23 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	t_byte buff;

	while (size--)
	{
		buff = *(t_byte *)a;
		*(t_byte *)a = *(t_byte *)b;
		*(t_byte *)b = buff;
		a++;
		b++;
	}
}
