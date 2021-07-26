/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:37 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:37 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_north_text(t_pars *pars, int x, int y)
{
	int	i;

	x++;
	if (pars->info[y][x] == 'O')
		x++;
	else
		error_handler("Can't load tex");
	while (pars->info[y][x] && pars->info[y][x] == ' ')
		x++;
	i = 0;
	ft_bzero(pars->path_n, 1024);
	while (pars->info[y][x] && pars->info[y][x] != ' ')
	{
		pars->path_n[i] = pars->info[y][x];
		i++;
		x++;
	}
	pars->path_n[i] = 0;
	file_reader(pars->path_n);
	if (pars->path_n_fl)
		error_handler("Dublicate north text");
	pars->path_n_fl = 1;
	return (-1);
}

int	check_south_text(t_pars *pars, int x, int y)
{
	int	i;

	x++;
	x = define_dir(pars, x, y);
	while (pars->info[y][x] && pars->info[y][x] == ' ')
		x++;
	i = 0;
	while (pars->info[y][x] && pars->info[y][x] != ' ')
	{
		if (pars->dir == 1)
			pars->path_s[i] = pars->info[y][x];
		else if (pars->dir == 2)
			pars->path_spr[i] = pars->info[y][x];
		i++;
		x++;
	}
	sprite_checker(pars, i, pars->dir);
	duplicate_s_check(pars, pars->dir);
	return (-1);
}

int	check_west_text(t_pars *pars, int x, int y)
{
	int	i;

	x++;
	if (pars->info[y][x] == 'E')
		x++;
	else
		error_handler("Can't load tex");
	while (pars->info[y][x] && pars->info[y][x] == ' ')
		x++;
	i = 0;
	while (pars->info[y][x] && pars->info[y][x] != ' ')
	{
		pars->path_w[i] = pars->info[y][x];
		i++;
		x++;
	}
	pars->path_w[i] = 0;
	file_reader(pars->path_w);
	if (pars->path_w_fl)
		error_handler("Duplicate west text");
	pars->path_w_fl = 1;
	return (-1);
}

void	fill_zeroes(t_pars *pars)
{
	ft_bzero(pars->path_n, 1024);
	ft_bzero(pars->path_s, 1024);
	ft_bzero(pars->path_spr, 1024);
	ft_bzero(pars->path_e, 1024);
	ft_bzero(pars->path_e, 1024);
}

int	check_east_text(t_pars *pars, int x, int y)
{
	int	i;

	x++;
	if (pars->info[y][x] == 'A')
		x++;
	else
		error_handler("Can't load tex");
	while (pars->info[y][x] && pars->info[y][x] == ' ')
		x++;
	i = 0;
	while (pars->info[y][x] && pars->info[y][x] != ' ')
	{
		pars->path_e[i] = pars->info[y][x];
		i++;
		x++;
	}
	pars->path_e[i] = 0;
	file_reader(pars->path_e);
	if (pars->path_e_fl)
		error_handler("Duplicate east text");
	pars->path_e_fl = 1;
	return (-1);
}
