/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split_inplace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 13:08:50 by                   #+#    #+#             */
/*   Updated: 2018/03/08 11:59:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stringview	ft_strsplit_inplace(char *str, char delim)
{
	t_vector		vec;
	t_stringview	string;

	vec = ft_vectornew(sizeof(char *), 16);
	string.data = str;
	while (*str == delim)
		str++;
	while (*str)
	{
		ft_vectorpushback(&vec, &str);
		while (*str && *str != delim)
			str++;
		if (!*str)
			break;
		*str = 0;
		str++;
		while (*str && *str == delim)
			str++;
	}
	str = NULL;
	ft_vectorpushback(&vec, &str);
	string.tab = (char **)vec.array;
	return (string);
}
