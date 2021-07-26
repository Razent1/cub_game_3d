/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:02 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:02 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil(t_pars *pars)
{
	int	y;
	int	x;

	y = 0;
	while (++y < pars->d_height / 2)
	{
		x = 0;
		while (++x < pars->d_width)
			pixel_put(pars, x, y, pars->rgb_c);
	}
}

void	draw_floor(t_pars *pars, int x, t_dda *ray)
{
	int	y;

	y = ray->draw_end + 1;
	if (ray->draw_end < 0)
		ray->draw_end = pars->d_height;
	while (++y < pars->d_height)
		pixel_put(pars, x, y, pars->rgb_f);
}

void	draw3d(t_pars *pars, t_dda *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - pars->pos_x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - pars->pos_y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
	ray->line_height = (int)(pars->d_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + pars->d_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + pars->d_height / 2;
	if (ray->draw_end >= pars->d_height)
		ray->draw_end = pars->d_height - 1;
}

void	draw_ray(t_pars *pars, t_dda *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (pars->map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}

void	ray_casting(t_pars *pars)
{
	t_dda	ray;
	int		x;

	x = 0;
	draw_ceil(pars);
	while (x < pars->d_width)
	{
		init_ray_var(pars, x, &ray);
		calc_distance(pars, &ray);
		draw_ray(pars, &ray);
		draw3d(pars, &ray);
		draw_text(pars, x, &ray);
		draw_floor(pars, x, &ray);
		pars->z_buffer[x] = ray.perp_wall_dist;
		x++;
	}
	if (pars->num_sprites > 0)
		draw_sprites(pars);
	if (pars->scrsh_flag == 0 && pars->is_save)
	{
		screenshot(pars);
		pars->scrsh_flag = 1;
	}
}
