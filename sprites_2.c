/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:27 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:27 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	sprites = (t_pair *) malloc(sizeof(t_pair) * amount);
	i = 0;
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
}

void	sprite_order(t_pars *pars)
{
	int	x;

	x = 0;
	while (x < pars->num_sprites)
	{
		pars->ord_sprite[x] = x;
		pars->sprite_dist[x] = ((pars->pos_x - pars->sprites[x].x)
				* (pars->pos_x - pars->sprites[x].x) + (pars->pos_y
					- pars->sprites[x].y) * (pars->pos_y - pars->sprites[x].y));
		x++;
	}
}

void	init_arr(t_pars *pars)
{
	pars->sprites = (t_sprite *)malloc(sizeof(t_sprite) * pars->num_sprites);
	if (!pars->sprites)
		error_handler("Malloc exception\n");
	pars->ord_sprite = (int *)malloc(sizeof(int) * pars->num_sprites);
	if (!pars->ord_sprite)
		error_handler("Malloc exception\n");
	pars->sprite_dist = (double *)malloc(sizeof(double) * pars->num_sprites);
	if (!pars->sprite_dist)
		error_handler("Malloc exception\n");
}

void	generate_sprite_arr(t_pars *pars)
{
	int			x;
	int			y;
	int			j;
	t_sprite	spr;

	y = 0;
	j = 0;
	init_arr(pars);
	while (pars->map[++y])
	{
		x = 0;
		while (pars->map[y][++x])
		{
			if (pars->map[y][x] == '2')
			{
				spr.y = x + 0.5;
				spr.x = y + 0.5;
				spr.text = 4;
				pars->sprites[j] = spr;
				j++;
			}
		}
	}
}
