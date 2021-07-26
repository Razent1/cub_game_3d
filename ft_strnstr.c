/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashley <aashley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:54:49 by aashley           #+#    #+#             */
/*   Updated: 2021/04/21 12:32:52 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strnstr(const char *str, const char *ptr, size_t size)
{
	unsigned int	i;
	size_t			fnd_size;

	if (*ptr == '\0')
		return ((char *)str);
	fnd_size = ft_strlen(ptr);
	i = 0;
	while (*str)
	{
		if (i + fnd_size > size)
			return (NULL);
		if (ft_strncmp(str, ptr, fnd_size) == 0)
			return ((char *)(str));
		str++;
		i++;
	}
	return (NULL);
}
