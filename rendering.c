/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 12:34:12 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 12:34:12 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_pars *pars, int x, int y, int color)
{
	char	*dst;

	dst = pars->mlx->addr + (y * pars->mlx->line_length + x
			* (pars->mlx->bits_per_pixel / 8));
	if (!dst)
		error_handler("Mlx exception");
	*(unsigned int *) dst = color;
}

void	load_texture(t_pars *pars)
{
	t_img	img;

	parse_text(pars, pars->texture[0], &img, pars->path_n);
	parse_text(pars, pars->texture[1], &img, pars->path_s);
	parse_text(pars, pars->texture[2], &img, pars->path_w);
	parse_text(pars, pars->texture[3], &img, pars->path_e);
	parse_text(pars, pars->texture[4], &img, pars->path_spr);
}

int	cycle(t_pars *pars)
{
	pars->mlx->img = mlx_new_image(pars->mlx->mlx_init, pars->d_width,
			pars->d_height);
	if (!pars->mlx->img)
		error_handler("Mlx exception");
	pars->mlx->addr = mlx_get_data_addr(pars->mlx->img,
			&pars->mlx->bits_per_pixel,
			&pars->mlx->line_length,
			&pars->mlx->endian);
	if (!pars->mlx->addr)
		error_handler("Mlx exception");
	ray_casting(pars);
	mlx_put_image_to_window(pars->mlx->mlx_init, pars->mlx->window,
		pars->mlx->img, 0, 0);
	mlx_destroy_image(pars->mlx->mlx_init, pars->mlx->img);
	return (1);
}

int	close_window(int keycode, t_pars *pars)
{
	(void)keycode;
	(void)pars;
	exit(0);
}

void	display(t_pars *pars)
{
	mlx_hook(pars->mlx->window, 2, 1L << 0, &key_hook, pars);
	mlx_hook(pars->mlx->window, 17, 0, close_window, pars);
	mlx_loop_hook(pars->mlx->mlx_init, cycle, pars);
	mlx_loop(pars->mlx->mlx_init);
}
