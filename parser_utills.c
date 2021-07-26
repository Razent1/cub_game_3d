/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utills.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:33:48 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:33:48 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	define_dir(t_pars *pars, int x, int y)
{
	if (pars->info[y][x] == 'O')
	{
		pars->dir = 1;
		x++;
	}
	else if (pars->info[y][x] == ' ' || pars->info[y][x] == '.')
		pars->dir = 2;
	else
		error_handler("Can't load tex");
	return (x);
}

void	sprite_checker(t_pars *pars, int i, int dir)
{
	if (dir == 1)
	{
		pars->path_s[i] = 0;
		file_reader(pars->path_s);
	}
	else if (dir == 2)
	{
		pars->path_spr[i] = 0;
		file_reader(pars->path_spr);
	}
}

void	duplicate_s_check(t_pars *pars, int dir)
{
	if (pars->path_s_fl && dir == 1)
		error_handler("Dublicate south text");
	if (pars->path_spr_fl && dir == 2)
		error_handler("Dublicate sprite text");
	if (dir == 1)
		pars->path_s_fl = 1;
	if (dir == 2)
		pars->path_spr_fl = 1;
}
