/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:18 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:18 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bmp(t_pars *pars, char *bit)
{
	ft_bzero(bit, 54);
	bit[0] = 'B';
	bit[1] = 'M';
	bit[2] = (pars->d_width * pars->d_height * 4 + 54) >> 24;
	bit[3] = (pars->d_width * pars->d_height * 4 + 54) >> 16;
	bit[4] = (pars->d_width * pars->d_height * 4 + 54) >> 8;
	bit[5] = pars->d_width * pars->d_height * 4 + 54;
	bit[10] = 54;
	bit[14] = 40;
	bit[18] = pars->d_width;
	bit[19] = pars->d_width >> 8;
	bit[20] = pars->d_width >> 16;
	bit[21] = pars->d_width >> 24;
	bit[22] = -pars->d_height;
	bit[23] = -pars->d_height >> 8;
	bit[24] = -pars->d_height >> 16;
	bit[25] = -pars->d_height >> 24;
	bit[26] = 1;
	bit[28] = 32;
}

void	screenshot(t_pars *pars)
{
	int		fd;
	int		i;
	int		b;
	char	bit[54];

	i = 0;
	fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd < 0)
		error_handler("Can't read file");
	bmp(pars, bit);
	b = 32 / 8 * pars->d_width;
	write(fd, &bit, 54);
	while (i < pars->d_height)
	{
		write(fd, &pars->mlx->addr[i * pars->mlx->line_length], b);
		i++;
	}
	close(fd);
	exit(0);
}
