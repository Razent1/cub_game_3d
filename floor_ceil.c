/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceil.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:39:57 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:43:22 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	correct_data_fl(t_pars *pars, int x, int y, char type)
{
	x = space_skipping(pars, x, y);
	if (type == 'r')
	{
		x -= 1;
		while (ft_isdigit(pars->info[y][++x]))
			pars->r_f = pars->r_f * 10 + (pars->info[y][x] - 48);
	}
	else if (type == 'g')
	{
		x -= 1;
		while (ft_isdigit(pars->info[y][++x]))
			pars->g_f = pars->g_f * 10 + (pars->info[y][x] - 48);
	}
	else if (type == 'b')
	{
		x -= 1;
		while (ft_isdigit(pars->info[y][++x]))
			pars->b_f = pars->b_f * 10 + (pars->info[y][x] - 48);
	}
	return (x);
}

int	correct_data_cl(t_pars *pars, int x, int y, char type)
{
	x = space_skipping(pars, x, y);
	if (type == 'r')
	{
		x -= 1;
		while (ft_isdigit(pars->info[y][++x]))
			pars->r_c = pars->r_c * 10 + (pars->info[y][x] - 48);
	}
	else if (type == 'g')
	{
		x -= 1;
		while (ft_isdigit(pars->info[y][++x]))
			pars->g_c = pars->g_c * 10 + (pars->info[y][x] - 48);
	}
	else if (type == 'b')
	{
		x -= 1;
		while (ft_isdigit(pars->info[y][++x]))
			pars->b_c = pars->b_c * 10 + (pars->info[y][x] - 48);
	}
	return (x);
}

int	comma_checker(t_pars *pars, int x, int y)
{
	while (pars->info[y][x] != ',')
	{
		if (pars->info[y][x] != ' ')
			error_handler("Incorrect ceil format");
		x++;
	}
	return (x);
}

int	check_floor(t_pars *pars, int x, int y)
{
	if (pars->fl_flag)
		error_handler("Duplicate floor color");
	x++;
	x = correct_data_fl(pars, x, y, 'r');
	x = comma_checker(pars, x, y);
	x++;
	x = correct_data_fl(pars, x, y, 'g');
	x = comma_checker(pars, x, y);
	x++;
	x = correct_data_fl(pars, x, y, 'b');
	while (pars->info[y][x])
	{
		if (pars->info[y][x] != ' ')
			error_handler("Incorrect floor format");
		x++;
	}
	pars->fl_flag = 1;
	return (-1);
}

int	check_ceil(t_pars *pars, int x, int y)
{
	if (pars->cl_flag)
		error_handler("Duplicate ceil color");
	x++;
	x = correct_data_cl(pars, x, y, 'r');
	x = comma_checker(pars, x, y);
	x++;
	x = correct_data_cl(pars, x, y, 'g');
	x = comma_checker(pars, x, y);
	x++;
	x = correct_data_cl(pars, x, y, 'b');
	while (pars->info[y][x])
	{
		if (pars->info[y][x] != ' ')
			error_handler("Incorrect ceil format");
		x++;
	}
	pars->cl_flag = 1;
	return (-1);
}
