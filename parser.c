/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:53:07 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 13:46:38 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_res(t_pars *pars, int x, int y)
{
	if (pars->res_fl)
		error_handler("Duplicate res");
	x++;
	while (pars->info[y][x])
	{
		if (ft_isdigit(pars->info[y][x]))
			x = digit_checker(pars, x, y);
		else if (pars->info[y][x] != ' ' && !ft_isdigit(pars->info[y][x]))
			error_handler("Incorrect resolution");
		else
			x++;
	}
	pars->res_fl = 1;
	return (-1);
}

void	rgb_parser(t_pars *pars)
{
	if (pars->r_c < 0 || pars->r_c > 255)
		error_handler("RGB must be from 0 to 255");
	if (pars->g_c < 0 || pars->g_c > 255)
		error_handler("RGB must be from 0 to 255");
	if (pars->b_c < 0 || pars->b_c > 255)
		error_handler("RGB must be from 0 to 255");
	if (pars->r_f < 0 || pars->r_f > 255)
		error_handler("RGB must be from 0 to 255");
	if (pars->g_f < 0 || pars->g_f > 255)
		error_handler("RGB must be from 0 to 255");
	if (pars->b_f < 0 || pars->b_f > 255)
		error_handler("RGB must be from 0 to 255");
	pars->rgb_c = 65536 * pars->r_c + 256 * pars->g_c + pars->b_c;
	pars->rgb_f = 65536 * pars->r_f + 256 * pars->g_f + pars->b_f;
}

int	letter_checker(t_pars *pars, int x, int y)
{
	while (pars->info[y][x] == ' ')
		x++;
	if (pars->info[y][x] == '\0')
		x = -1;
	if (pars->info[y][x] == 'R')
		x = check_res(pars, x, y);
	if (pars->info[y][x] == 'N')
		x = check_north_text(pars, x, y);
	if (pars->info[y][x] == 'S')
		x = check_south_text(pars, x, y);
	if (pars->info[y][x] == 'W')
		x = check_west_text(pars, x, y);
	if (pars->info[y][x] == 'E')
		x = check_east_text(pars, x, y);
	if (pars->info[y][x] == 'F')
		x = check_floor(pars, x, y);
	if (pars->info[y][x] == 'C')
		x = check_ceil(pars, x, y);
	if (x == -1)
		return (-1);
	else
		error_handler("Undefined symbols");
	return (0);
}

void	res_checker(t_pars *pars)
{
	int	h;
	int	w;

	if (pars->d_width <= 0 || pars->d_width > 16384)
		error_handler("Incorrect format resolution");
	if (pars->d_height <= 0 || pars->d_height > 16384)
		error_handler("Incorrect format resolution");
	mlx_get_screen_size(pars->mlx->mlx_init, &w, &h);
	if (pars->d_height > h && !pars->is_save)
		pars->d_height = h;
	if (pars->d_width > w && !pars->is_save)
		pars->d_width = w;
}

int	info_parser(t_pars *pars)
{
	int	y;
	int	x;

	y = 0;
	init_flags(pars);
	fill_zeroes(pars);
	while (pars->info[y])
	{
		x = 0;
		while (pars->info[y][x])
		{
			x = letter_checker(pars, x, y);
			if (x == -1)
				break ;
			x++;
		}
		y++;
	}
	if ((!pars->d_width && !pars->d_height) || !pars->cl_flag || !pars->fl_flag
		|| !pars->path_e_fl || !pars->path_w_fl || !pars->path_n_fl
		|| !pars->path_s_fl || !pars->path_spr_fl)
		error_handler("No parameter");
	res_checker(pars);
	free_map(pars);
	return (-1);
}
