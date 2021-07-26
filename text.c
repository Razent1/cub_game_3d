/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:31 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:31 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_text(t_pars *pars)
{
	int	i;
	int	j;

	pars->texture = (int **)malloc(sizeof(int *) * 5);
	if (!pars->texture)
		error_handler("Malloc exception");
	i = -1;
	while (++i < 5)
	{
		pars->texture[i] = (int *) malloc(sizeof(int) * (TEX_HEIGHT
					* TEX_WID));
		if (!pars->texture[i])
			error_handler("Malloc exception");
	}
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < TEX_HEIGHT * TEX_WID)
		{
			pars->texture[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	chose_text_dir(t_pars *pars, t_dda *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			pars->text_dir = 'N';
		else
			pars->text_dir = 'S';
		ray->wall_x = pars->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		if (ray->ray_dir_y < 0)
			pars->text_dir = 'W';
		else
			pars->text_dir = 'E';
		ray->wall_x = pars->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	}
}

void	parse_text(t_pars *pars, int *texture, t_img *img, char *path)
{
	int	y;
	int	x;

	img->img = mlx_png_file_to_image(pars->mlx->mlx_init, path,
			&img->img_wid, &img->img_height);
	if (!img->img)
		error_handler("Mlx exception");
	img->info = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->info)
		error_handler("Mlx exception");
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_wid)
		{
			texture[img->img_wid * y + x] = img->info[img->img_wid * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(pars->mlx->mlx_init, img->img);
}

void	init_text_var(t_pars *pars, t_dda *ray)
{
	chose_text_dir(pars, ray);
	ray->wall_x -= floor(ray->wall_x);
	ray->text_x = (int)(ray->wall_x * (double) TEX_WID);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->text_x = TEX_WID - ray->text_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->text_x = TEX_WID - ray->text_x - 1;
	ray->step_t = 1.0 * TEX_HEIGHT / ray->line_height;
	ray->pos_tex = (ray->draw_start - pars->d_height / 2 + ray->line_height
			/ 2) * ray->step_t;
}

void	draw_text(t_pars *pars, int x, t_dda *ray)
{
	int	y;
	int	color;
	int	text_y;

	color = 0;
	init_text_var(pars, ray);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		text_y = (int)ray->pos_tex & (TEX_HEIGHT - 1);
		ray->pos_tex += ray->step_t;
		if (pars->text_dir == 'N')
			color = pars->texture[0][TEX_HEIGHT * text_y + ray->text_x];
		if (pars->text_dir == 'S')
			color = pars->texture[1][TEX_HEIGHT * text_y + ray->text_x];
		if (pars->text_dir == 'W')
			color = pars->texture[2][TEX_HEIGHT * text_y + ray->text_x];
		if (pars->text_dir == 'E')
			color = pars->texture[3][TEX_HEIGHT * text_y + ray->text_x];
		pixel_put(pars, x, y, color);
		y++;
	}
}
