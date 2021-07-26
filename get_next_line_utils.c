/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashley <aashley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 19:39:36 by aashley           #+#    #+#             */
/*   Updated: 2021/04/21 12:30:00 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char *)malloc(sizeof(*dest) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}

int	read_fl(int fd, int flag, char **tmp, char **str)
{
	char		buf[1024];
	int			rs;

	if (!flag)
	{
		rs = read(fd, buf, 1024);
		buf[rs] = '\0';
		*tmp = *str;
		*str = ft_strjoin(*str, buf);
		ft_del(tmp);
	}
	else
	{
		while (ft_strchr(*str, '\n') == NULL && rs > 0)
		{
			rs = read(fd, buf, 1024);
			buf[rs] = '\0';
			*tmp = *str;
			*str = ft_strjoin(*str, buf);
			ft_del(tmp);
		}
	}
	return (rs);
}
