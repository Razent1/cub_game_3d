/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:52:21 by ilya              #+#    #+#             */
/*   Updated: 2021/04/21 14:17:47 by ilya             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include "./minilibx_mms_20200219/mlx.h"
# define TEX_WID 64
# define TEX_HEIGHT 64
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_img
{
	void	*img;
	int		*info;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_wid;
	int		img_height;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_init;
	void	*window;
	char	*addr;
	void	*img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		*img_info;
	int		img_wid;
	int		img_height;
}				t_mlx;

typedef struct s_point
{
	int	x;
	int	y;

}	t_point;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		text;

}	t_sprite;

typedef struct s_pars
{
	t_mlx		*mlx;
	char		**map;
	char		**info;
	int			size_i;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			**texture;
	char		text_dir;
	double		*z_buffer;
	int			num_sprites;
	int			*ord_sprite;
	double		*sprite_dist;
	t_sprite	*sprites;
	int			d_width;
	int			d_height;
	char		path_n[1024];
	char		path_s[1024];
	char		path_w[1024];
	char		path_e[1024];
	char		path_spr[1024];
	int			dir;
	int			res_fl;
	int			path_n_fl;
	int			path_s_fl;
	int			path_e_fl;
	int			path_w_fl;
	int			path_spr_fl;
	int			fl_flag;
	int			cl_flag;
	int			r_f;
	int			g_f;
	int			b_f;
	int			r_c;
	int			g_c;
	int			b_c;
	int			rgb_f;
	int			rgb_c;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			stripe;
	int			tex_x;
	int			d;
	int			tex_y;
	int			sprite_screen_x;
	int			u_div;
	int			v_div;
	double		v_move;
	int			v_move_screen;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			scrsh_flag;
	int			is_save;
}	t_pars;

typedef struct s_pair
{
	double	first;
	int		second;
}	t_pair;

typedef struct s_dda
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		text_x;
	double	step_t;
	double	pos_tex;
}	t_dda;

int		get_next_line(int fd, char **line);
void	display(t_pars *pars);
void	pixel_put(t_pars *pars, int x, int y, int color);
void	draw_sprites(t_pars *pars);
void	generate_sprite_arr(t_pars *pars);
void	draw_text(t_pars *pars, int x, t_dda *ray);
int		key_hook(int key, t_pars *pars);
void	map_parser(t_pars *pars);
int		info_parser(t_pars *pars);
void	parse_text(t_pars *pars, int *texture, t_img *img, char *path);
int		error_handler(char *err_code);
void	rgb_parser(t_pars *pars);
int		len_arr(t_pars *pars);
void	png_checker(char *path);
int		check_north_text(t_pars *pars, int x, int y);
int		check_south_text(t_pars *pars, int x, int y);
int		check_west_text(t_pars *pars, int x, int y);
int		check_east_text(t_pars *pars, int x, int y);
int		check_ceil(t_pars *pars, int x, int y);
int		check_floor(t_pars *pars, int x, int y);
int		digit_checker(t_pars *pars, int x, int y);
void	init_flags(t_pars *pars);
void	screenshot(t_pars *pars);
void	fill_zeroes(t_pars *pars);
void	move_left(t_pars *pars);
void	move_right(t_pars *pars);
void	sort_order(t_pair *orders, int amount);
void	sort_sprites(int *order, double *dist, int amount);
void	sprite_order(t_pars *pars);
void	init_arr(t_pars *pars);
void	file_reader(char *path);
int		define_dir(t_pars *pars, int x, int y);
void	sprite_checker(t_pars *pars, int i, int dir);
void	duplicate_s_check(t_pars *pars, int dir);
char	*ft_strnew(size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_del(char **str);
void	ray_casting(t_pars *pars);
void	calc_distance(t_pars *pars, t_dda *ray);
void	init_ray_var(t_pars *pars, int x, t_dda *ray);
void	init_text(t_pars *pars);
void	generate_info(t_list **head, int size, t_pars *pars);
int		fill_map_arr(t_pars *pars, int fd, t_list *head);
int		read_map(char *map);
void	make_map(t_pars *pars);
int		check_first_symb(const char *line);
void	load_texture(t_pars *pars);
void	player_dir_we(t_pars *pars, int x, int y);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnew(size_t size);
char	*ft_strdup(const char *s);
int		read_fl(int fd, int flag, char **tmp, char **str);
int		ft_isdigit(int c);
char	*ft_strnstr(const char *str, const char *ptr, size_t size);
char	*ft_strchr(const char *str, int c);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar(char c);
int		ft_strncmp(const char *string1, const char *string2, size_t num);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_bzero(void *s, size_t size);
void	free_map(t_pars *pars);
int		space_skipping(t_pars *pars, int x, int y);
void	map_arg(const char *str);

#endif
