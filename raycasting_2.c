/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:07 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:07 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_distance(t_pars *pars, t_dda *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pars->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - pars->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pars->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - pars->pos_y) * ray->delta_dist_y;
	}
}

void	init_ray_var(t_pars *pars, int x, t_dda *ray)
{
	ray->camera_x = 2 * x / (double) pars->d_width - 1;
	ray->ray_dir_x = pars->dir_x + pars->plane_x * ray->camera_x;
	ray->ray_dir_y = pars->dir_y + pars->plane_y * ray->camera_x;
	ray->map_x = (int)pars->pos_x;
	ray->map_y = (int)pars->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}
