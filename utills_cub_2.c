/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utills_cub_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:50 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 13:34:06 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_handler(char *err_code)
{
	printf("%s%s", "Error! ", err_code);
	exit(0);
}

void	player_dir_we(t_pars *pars, int x, int y)
{
	if (pars->map[y][x] == 'W')
	{
		pars->dir_x = 0.0;
		pars->dir_y = -1.0;
		pars->plane_x = -0.66;
		pars->plane_y = 0.0;
	}
	if (pars->map[y][x] == 'E')
	{
		pars->dir_x = 0.0;
		pars->dir_y = 1.0;
		pars->plane_x = 0.66;
		pars->plane_y = 0.0;
	}
}

void	free_map(t_pars *pars)
{
	int	y;

	y = 0;
	while (y <= pars->size_i)
	{
		free(pars->info[y]);
		y++;
	}
}

int	space_skipping(t_pars *pars, int x, int y)
{
	while (!(ft_isdigit(pars->info[y][x])))
	{
		if (pars->info[y][x] != ' ')
			error_handler("Incorrect floor format");
		x++;
	}
	return (x);
}

void	map_arg(const char *str)
{
	char	*map_name;
	int		i;

	map_name = "map.cub";
	i = 0;
	if (ft_strlen(str) != 7)
		error_handler("Incorrect file cub name");
	while (str[i])
	{
		if (str[i] != map_name[i])
			error_handler("Incorrect file cub name");
		i++;
	}
}
