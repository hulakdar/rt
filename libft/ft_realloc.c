/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <skamoza@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:25:22 by skamoza           #+#    #+#             */
/*   Updated: 2018/02/01 12:36:42 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_realloc(void **arr, size_t old, size_t new_size)
{
	void		*newarr;

	newarr = ft_memalloc(new_size);
	if (*arr)
	{
		ft_quickmove(newarr, *arr, old);
		free(*arr);
	}
	*arr = newarr;
}
