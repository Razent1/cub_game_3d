/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:33:57 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:33:57 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	move_left(t_pars *pars)
{
	if (pars->map[(int)(pars->pos_x - pars->dir_y * pars->move_speed)][
				(int)(pars->pos_y)] != '1')
		pars->pos_x -= pars->dir_y * pars->move_speed;
	if (pars->map[(int)(pars->pos_x)][(int)(pars->pos_y + pars->dir_x
			* pars->move_speed)] != '1')
		pars->pos_y += pars->dir_x * pars->move_speed;
}

void	move_right(t_pars *pars)
{
	if (pars->map[(int)(pars->pos_x + pars->dir_y * pars->move_speed)][
				(int)(pars->pos_y)] != '1')
		pars->pos_x += pars->dir_y * pars->move_speed;
	if (pars->map[(int)(pars->pos_x)][(int)(pars->pos_y - pars->dir_x
			* pars->move_speed)] != '1')
		pars->pos_y -= pars->dir_x * pars->move_speed;
}
