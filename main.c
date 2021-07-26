/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:41:52 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 13:31:10 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

void	scrab_info(t_pars *pars, char *map)
{
	int		i;
	int		fd;
	char	*line;
	t_list	*head;
	t_list	*head_info;

	fd = read_map(map);
	head = NULL;
	head_info = NULL;
	line = NULL;
	i = 0;
	while (get_next_line(fd, &line) && check_first_symb(line) == 0)
	{
		ft_lstadd_back(&head_info, ft_lstnew(ft_strdup(line)));
		free(line);
		i++;
	}
	ft_lstadd_back(&head, ft_lstnew(ft_strdup(line)));
	free(line);
	generate_info(&head_info, ft_lstsize(head_info), pars);
	fd = fill_map_arr(pars, fd, head);
	close(fd);
}

void	init_var(t_pars *pars)
{
	pars->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!pars->mlx)
		error_handler("Malloc exception\n");
	pars->d_height = 0;
	pars->d_width = 0;
	pars->r_f = 0;
	pars->g_f = 0;
	pars->b_f = 0;
	pars->r_c = 0;
	pars->g_c = 0;
	pars->b_c = 0;
	pars->rgb_c = 0;
	pars->rgb_f = 0;
	pars->is_save = 0;
	pars->scrsh_flag = 0;
	pars->move_speed = 0.2;
	pars->rot_speed = 0.2;
	pars->mlx->mlx_init = NULL;
	pars->mlx->window = NULL;
	pars->mlx->mlx_init = mlx_init();
	if (!pars->mlx->mlx_init)
		error_handler("Mlx exception");
}

int	save_arg(const char *str)
{
	char	*save;
	int		i;

	save = "--save";
	i = 0;
	if (ft_strlen(str) != 6)
		return (0);
	while (str[i])
	{
		if (str[i] != save[i])
			return (0);
		i++;
	}
	return (1);
}

void	arg_checker(t_pars *pars, int argc, char **argv)
{
	if (argc == 2)
	{
		map_arg(argv[1]);
		scrab_info(pars, argv[1]);
	}
	else if (argc == 3 && save_arg(argv[1]))
	{
		pars->is_save = 1;
		map_arg(argv[2]);
		scrab_info(pars, argv[2]);
	}
	else
		error_handler("Args error");
}

int	main(int argc, char **argv)
{
	t_pars	*pars;

	pars = (t_pars *)malloc(sizeof(t_pars));
	if (!pars)
		error_handler("Malloc exception\n");
	init_var(pars);
	arg_checker(pars, argc, argv);
	map_parser(pars);
	info_parser(pars);
	rgb_parser(pars);
	init_text(pars);
	load_texture(pars);
	pars->z_buffer = (double *)malloc(sizeof(double) * pars->d_width);
	if (!pars->z_buffer)
		error_handler("Malloc exception\n");
	make_map(pars);
	pars->mlx->window = mlx_new_window(pars->mlx->mlx_init, pars->d_width,
			pars->d_height, "cub3D");
	if (!pars->mlx->window)
		error_handler("Mlx exception\n");
	display(pars);
	return (0);
}
