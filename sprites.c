/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:22 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:22 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_spr_var(t_pars *pars, int i)
{
	pars->sprite_x = pars->sprites[pars->ord_sprite[i]].x - pars->pos_x;
	pars->sprite_y = pars->sprites[pars->ord_sprite[i]].y - pars->pos_y;
	pars->inv_det = 1.0 / (pars->plane_x * pars->dir_y - pars->dir_x
			* pars->plane_y);
	pars->transform_x = pars->inv_det * (pars->dir_y * pars->sprite_x
			- pars->dir_x * pars->sprite_y);
	pars->transform_y = pars->inv_det * (-pars->plane_y * pars->sprite_x
			+ pars->plane_x * pars->sprite_y);
	pars->sprite_screen_x = (int)((pars->d_width / 2) * (1
				+ pars->transform_x / pars->transform_y));
	pars->u_div = 1;
	pars->v_div = 1;
	pars->v_move = 0.0;
	pars->v_move_screen = (int)(pars->v_move / pars->transform_y);
	pars->sprite_height = (int)fabs((pars->d_height / pars->transform_y)
			/ pars->v_div);
	pars->draw_start_y = -pars->sprite_height / 2 + pars->d_height / 2
		+ pars->v_move_screen;
	return (i);
}

void	spr_cmp(t_pars *pars)
{
	if (pars->draw_start_y < 0)
		pars->draw_start_y = 0;
	pars->draw_end_y = pars->sprite_height / 2 + pars->d_height / 2
		+ pars->v_move_screen;
	if (pars->draw_end_y >= pars->d_height)
		pars->draw_end_y = pars->d_height - 1;
	pars->sprite_width = (int)fabs((pars->d_height / pars->transform_y)
			/ pars->u_div);
	pars->draw_start_x = -pars->sprite_width / 2 + pars->sprite_screen_x;
	if (pars->draw_start_x < 0)
		pars->draw_start_x = 0;
	pars->draw_end_x = pars->sprite_width / 2 + pars->sprite_screen_x;
	if (pars->draw_end_x >= pars->d_width)
		pars->draw_end_x = pars->d_width - 1;
}

void	draw_spr(t_pars *pars)
{
	int	y;
	int	color;

	y = pars->draw_start_y;
	while (y < pars->draw_end_y)
	{
		pars->d = (y - pars->v_move_screen) * 256 - pars->d_height
			* 128 + pars->sprite_height * 128;
		pars->tex_y = ((pars->d * TEX_HEIGHT) / pars->sprite_height) / 256;
		color = pars->texture[4][TEX_WID * pars->tex_y + pars->tex_x];
		if ((color & 0x00FFFFFF) != 0)
			pixel_put(pars, pars->stripe, y, color);
		y++;
	}
}

void	place_sprites(t_pars *pars)
{
	pars->stripe = pars->draw_start_x;
	while (pars->stripe < pars->draw_end_x)
	{
		pars->tex_x = (int)((256 * (pars->stripe - (-pars->sprite_width / 2
							+ pars->sprite_screen_x)) * TEX_WID
					/ pars->sprite_width) / 256);
		if (pars->transform_y > 0 && pars->stripe > 0 && pars->stripe
			< pars->d_width && pars->transform_y < pars->z_buffer[pars->stripe])
			draw_spr(pars);
		pars->stripe++;
	}
}

void	draw_sprites(t_pars *pars)
{
	int	i;

	i = 0;
	sprite_order(pars);
	sort_sprites(pars->ord_sprite, pars->sprite_dist, pars->num_sprites);
	while (i < pars->num_sprites)
	{
		i = init_spr_var(pars, i);
		spr_cmp(pars);
		place_sprites(pars);
		i++;
	}
}
