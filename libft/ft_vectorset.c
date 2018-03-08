/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectorset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skamoza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 19:14:36 by skamoza           #+#    #+#             */
/*   Updated: 2018/02/01 12:35:56 by skamoza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_vectorset(t_vector *vect, size_t index, void *content)
{
	size_t		new_size;
	size_t		size;

	if (!vect)
		return (NULL);
	size = vect->size;
	if (index > vect->last)
	{
		new_size = vect->last + 1;
		while (new_size < index + 2)
			new_size <<= 1;
		ft_realloc(&vect->array, (vect->last + 1) * vect->size, new_size);
		vect->last = new_size - 1;
	}
	return (ft_memmove(vect->array + (size * index), content, size));
}
