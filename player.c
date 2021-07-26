/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:24:56 by ilya              #+#    #+#             */
/*   Updated: 2021/04/19 15:25:28 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_pars *pars)
{
	if (pars->map[(int)(pars->pos_x + pars->dir_x * pars->move_speed)][
			(int)(pars->pos_y)] != '1')
		pars->pos_x += pars->dir_x * pars->move_speed;
	if (pars->map[(int)(pars->pos_x)][(int)(pars->pos_y + pars->dir_y *
	pars->move_speed)] != '1')
		pars->pos_y += pars->dir_y * pars->move_speed;
}

void	rotate_right(t_pars *pars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pars->dir_x;
	old_plane_x = pars->plane_x;
	pars->dir_x = pars->dir_x * cos(pars->rot_speed) - pars->dir_y
		* sin(pars->rot_speed);
	pars->dir_y = old_dir_x * sin(pars->rot_speed) + pars->dir_y
		* cos(pars->rot_speed);
	pars->plane_x = pars->plane_x * cos(pars->rot_speed) - pars->plane_y
		* sin(pars->rot_speed);
	pars->plane_y = old_plane_x * sin(pars->rot_speed) + pars->plane_y
		* cos(pars->rot_speed);
}

void	rotate_left(t_pars *pars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pars->dir_x;
	old_plane_x = pars->plane_x;
	pars->dir_x = pars->dir_x * cos(-pars->rot_speed) - pars->dir_y
		* sin(-pars->rot_speed);
	pars->dir_y = old_dir_x * sin(-pars->rot_speed) + pars->dir_y
		* cos(-pars->rot_speed);
	pars->plane_x = pars->plane_x * cos(-pars->rot_speed) - pars->plane_y
		* sin(-pars->rot_speed);
	pars->plane_y = old_plane_x * sin(-pars->rot_speed) + pars->plane_y
		* cos(-pars->rot_speed);
}

void	move_back(t_pars *pars)
{
	if (pars->map[(int)(pars->pos_x - pars->dir_x * pars->move_speed)][
				(int)(pars->pos_y)] != '1')
		pars->pos_x -= pars->dir_x * pars->move_speed;
	if (pars->map[(int)(pars->pos_x)][(int)(pars->pos_y - pars->dir_y
		* pars->move_speed)] != '1')
		pars->pos_y -= pars->dir_y * pars->move_speed;
}

int	key_hook(int key, t_pars *pars)
{
	if (key == 13)
		move_forward(pars);
	if (key == 1)
		move_back(pars);
	if (key == 2)
		move_right(pars);
	if (key == 0)
		move_left(pars);
	if (key == 123)
		rotate_right(pars);
	if (key == 124)
		rotate_left(pars);
	if (key == 53)
		exit(0);
	return (0);
}
