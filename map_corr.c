/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_corr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 01:14:05 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 11:53:02 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_correctness(t_pars *pars, int x, int y, int len)
{
	if ((y == 0 || y == len) && (pars->map[y][x] == '0' || pars->map[y][x] ==
	'2' || pars->map[y][x] == 'N' || pars->map[y][x] == 'W' ||
	pars->map[y][x] == 'E' || pars->map[y][x] == 'S'))
		error_handler("Map Error\n");
	if ((pars->map[y][x] == '0' || pars->map[y][x] == '2' ||
		 pars->map[y][x] == 'N' || pars->map[y][x] == 'W' || pars->map[y][x]
		 =='E' || pars->map[y][x] == 'S') && y > 0 && y < len && (
		 		(pars->map[y - 1][x] == ' ') || (pars->map[y -
		 1][x] != '1')) && (pars->map[y - 1][x] != '2') && (pars->map[y -
		 1][x] != 'N') && (pars->map[y - 1][x] != 'E') && (pars->map[y -
		 1][x] != '0') && (pars->map[y - 1][x] != 'W') && (pars->map[y -
		 1][x] != 'S'))
		error_handler("Map Error\n");
	if ((pars->map[y][x] == '0' || pars->map[y][x] == '2' ||
		 pars->map[y][x] == 'N' || pars->map[y][x] == 'W' || pars->map[y][x]
		 == 'E' || pars->map[y][x] == 'S') && y > 0 && y < len && (pars->map[y
		 + 1][x] != '1') && (pars->map[y + 1][x] != '2') && (pars->map[y +
		 1][x] != 'N') && (pars->map[y + 1][x] != 'E') && (pars->map[y +
		 1][x] != '0') && (pars->map[y + 1][x] != 'W') && (pars->map[y +
		 1][x] != 'S'))
		error_handler("Map Error\n");
}

void	after_space_check(t_pars *pars, int y, int x)
{
	if (pars->map[y][x] == ' ')
	{
		if (pars->map[y][x - 1] == '0' || pars->map[y][x + 1] == '0' ||
			pars->map[y][x - 1] == '2' || pars->map[y][x + 1] == '2' ||
			pars->map[y][x - 1] == 'N' || pars->map[y][x + 1] == 'N' ||
			pars->map[y][x - 1] == 'W' || pars->map[y][x + 1] == 'W' ||
			pars->map[y][x - 1] == 'E' || pars->map[y][x + 1] == 'E' ||
			pars->map[y][x - 1] == 'S' || pars->map[y][x + 1] == 'S')
			error_handler("Map Error\n");
	}
}

void	line_correctness(t_pars *pars, int y)
{
	int	x;

	x = 0;
	while (pars->map[y][x] == ' ')
		x++;
	if (pars->map[y][x] == '0' || pars->map[y][x] == '2' || pars->map[y][x] ==
	'N' || pars->map[y][x] == 'W' || pars->map[y][x] == 'E' ||
	pars->map[y][x] == 'S')
		error_handler("Map Error\n");
	while (pars->map[y][x])
	{
		after_space_check(pars, y, x);
		x++;
	}
	if (pars->map[y][0] != 0 && (pars->map[y][x - 1] == '0' ||
	pars->map[y][x - 1] == '2' || pars->map[y][x - 1] == 'N' ||
	pars->map[y][x - 1] == 'W' ||
	pars->map[y][x - 1] == 'E' || pars->map[y][x - 1] == 'S'))
		error_handler("Map Error\n");
}

int	map_corr(t_pars *pars, int x, int y, int count_plr)
{
	if (ft_strchr("WESN", pars->map[y][x]))
	{
		if (count_plr == 1)
			error_handler("Dublicate players\n");
		count_plr++;
	}
	if (ft_strchr("012WESN ", pars->map[y][x]) == NULL)
		error_handler("Undefined symb in map\n");
	return (count_plr);
}

void	map_parser(t_pars *pars)
{
	int	x;
	int	y;
	int	len;
	int	count_plr;

	y = 0;
	count_plr = 0;
	len = len_arr(pars) - 1;
	while (pars->map[y])
	{
		line_correctness(pars, y);
		x = 0;
		while (pars->map[y][x])
		{
			count_plr = map_corr(pars, x, y, count_plr);
			map_correctness(pars, x, y, len);
			x++;
		}
		y++;
	}
	if (count_plr == 0)
		error_handler("No player");
}
