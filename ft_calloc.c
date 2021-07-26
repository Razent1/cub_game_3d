/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashley <aashley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:51:51 by aashley           #+#    #+#             */
/*   Updated: 2021/04/20 21:45:11 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	s;
	char	*new_mem;

	i = 0;
	s = count * size;
	new_mem = malloc(s);
	if (new_mem == NULL)
		return (NULL);
	while (s--)
	{
		new_mem[i] = 0;
		i++;
	}
	return ((void *)new_mem);
}
