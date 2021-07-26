/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashley <aashley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:54:44 by aashley           #+#    #+#             */
/*   Updated: 2021/04/20 22:08:52 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strncmp(const char *string1, const char *string2, size_t num)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (0);
	while (string1[i] == string2[i] && string1[i] != '\0' && num - 1 > i)
		i++;
	return ((unsigned char)string1[i] - (unsigned char)string2[i]);
}
