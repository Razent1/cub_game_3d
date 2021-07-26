/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aashley <aashley@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 19:39:20 by aashley           #+#    #+#             */
/*   Updated: 2021/04/21 11:53:02 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_del(char **str)
{
	if (str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	ft_join(char **str, char **buf)
{
	char	*tmp_s;

	tmp_s = *str;
	if (str != NULL && buf != NULL)
		*str = ft_strjoin(*str, *buf);
	else if (str != NULL && buf == NULL)
		*str = ft_strnew(0);
	ft_del(&tmp_s);
}

static int	set_rm(char **rm, char **line, char **str, int rs)
{
	char	*tmp;

	if (rs > 0)
	{
		tmp = *rm;
		*rm = ft_strjoin(*rm, ft_strchr(*str, '\n') + 1);
		ft_del(&tmp);
		*ft_strchr(*str, '\n') = '\0';
		*line = ft_strdup(*str);
		ft_del(str);
		return (1);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_del(str);
		ft_del(rm);
		return (0);
	}
}

static int	upd_line(char **str, char **remainder, char **line)
{
	char	*tmp;

	ft_join(str, remainder);
	ft_join(remainder, NULL);
	if (ft_strchr(*str, '\n') != NULL)
	{
		tmp = *remainder;
		*remainder = ft_strjoin(*remainder, ft_strchr(*str, '\n') + 1);
		*ft_strchr(*str, '\n') = '\0';
		ft_del(&tmp);
		*line = ft_strdup(*str);
		ft_del(str);
		return (1);
	}
	else
		return (0);
}

int	get_next_line(int fd, char **line)
{
	int			rs;
	static char	*remainder;
	char		*str;
	char		*tmp;
	static int	flag;

	if (line == 0 || fd < 0)
		return (-1);
	str = ft_strnew(0);
	if (remainder && upd_line(&str, &remainder, line))
		return (1);
	ft_join(&remainder, NULL);
	if (!flag)
	{
		rs = read_fl(fd, 0, &tmp, &str);
		flag = 1;
	}
	else
		rs = read_fl(fd, 1, &tmp, &str);
	if (rs >= 0)
		return (set_rm(&remainder, line, &str, rs));
	ft_del(&str);
	return (-1);
}
