#include "cub3d.h"

int	check_first_symb(const char *line)
{
	int	i;

	i = 0;
	if (line[0] == '0' || line[0] == '1')
		return (1);
	while (line[i] && line[i] == ' ' && line[i] != '1' && line[i] != '0')
		i++;
	if (line[i] == '0' || line[i] == '1')
		return (1);
	return (0);
}

int	read_map(char *map)
{
	int		rr;
	int		fd;
	char	buf[1];

	fd = open(map, O_RDONLY);
	if (fd < 0)
		error_handler("Can't read the file");
	rr = read(fd, buf, 0);
	if (rr < 0)
		error_handler("Folder problem");
	close(rr);
	return (fd);
}

void	player_dir(t_pars *pars, int x, int y)
{
	if (pars->map[y][x] == 'N')
	{
		pars->dir_x = -1.0;
		pars->dir_y = 0.0;
		pars->plane_x = 0.0;
		pars->plane_y = 0.66;
	}
	if (pars->map[y][x] == 'S')
	{
		pars->dir_x = 1.0;
		pars->dir_y = 0.0;
		pars->plane_x = 0.0;
		pars->plane_y = -0.66;
	}
	player_dir_we(pars, x, y);
}

void	define_player(t_pars *pars, int x, int y)
{
	pars->pos_x = (double)y + 0.5;
	pars->pos_y = (double)x + 0.5;
	player_dir(pars, x, y);
}

void	make_map(t_pars *pars)
{
	int	x;
	int	y;

	y = 0;
	pars->num_sprites = 0;
	while (pars->map[y])
	{
		x = 0;
		while (pars->map[y][x])
		{
			if ((pars->map[y][x] == 'N' || pars->map[y][x] == 'S'
				 || pars->map[y][x] == 'W' || pars->map[y][x] == 'E')
				&& !pars->pos_x)
				define_player(pars, x, y);
			if (pars->map[y][x] == '2')
				pars->num_sprites++;
			x++;
		}
		y++;
	}
	if (pars->num_sprites > 0)
		generate_sprite_arr(pars);
}
