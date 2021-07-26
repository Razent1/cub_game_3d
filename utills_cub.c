/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 23:06:20 by ilya              #+#    #+#             */
/*   Updated: 2021/04/20 16:36:27 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	len_arr(t_pars *pars)
{
	int	y;
	int	len;

	y = 0;
	len = 0;
	while (pars->map[y])
	{
		len++;
		y++;
	}
	return (len);
}

void	png_checker(char *path)
{
	if (!(ft_strnstr(path, ".png", ft_strlen(path))))
		error_handler("Can't load tex");
}

int	digit_checker(t_pars *pars, int x, int y)
{
	int	num;

	num = 0;
	while (ft_isdigit(pars->info[y][x]))
	{
		num = num * 10 + (pars->info[y][x] - 48);
		x++;
	}
	if (pars->d_width == 0)
		pars->d_width = num;
	else if (pars->d_height == 0)
		pars->d_height = num;
	else
		error_handler("Dublicate resolution\n");
	return (x);
}

void	init_flags(t_pars *pars)
{
	pars->path_spr_fl = 0;
	pars->path_s_fl = 0;
	pars->path_n_fl = 0;
	pars->path_e_fl = 0;
	pars->path_w_fl = 0;
	pars->res_fl = 0;
	pars->cl_flag = 0;
	pars->fl_flag = 0;
}

void	file_reader(char *path)
{
	int		fd;
	char	b[1];
	int		rr;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_handler("Can't load tex");
	rr = read(fd, b, 0);
	if (rr < 0)
		error_handler("Folder problem");
	png_checker(path);
	close(fd);
	close(rr);
}
