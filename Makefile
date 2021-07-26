# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilya <ilya@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/21 12:28:35 by ilya              #+#    #+#              #
#    Updated: 2021/04/21 12:49:19 by ilya             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS =ft_isdigit.c ft_strlen.c ft_isalpha.c ft_strchr.c ft_strnstr.c ft_lstadd_back.c ft_calloc.c\
ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_strncmp.c ft_bzero.c ft_strdup.c\
get_next_line.c get_next_line_utils.c \
main.c player.c player_2.c screenshot.c sprites.c sprites_2.c rendering.c raycasting.c data_generator.c\
parser.c text_dir.c map_corr.c text.c floor_ceil.c parser_utills.c utills_cub.c utills_cub_2.c analyze_map.c\
raycasting_2.c\

LIBNAME = cub3d.a

FLAGS = -Wall -Wextra -Werror -MMD

MLXLIB = minilibx_mms_20200219

MLX = libmlx.dylib


DEP = $(SRCS:.c=.d)

MLXFLAGS = -framework OpenGL -framework AppKit

OBJECTS = $(patsubst %.c,%.o,$(SRCS))

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJECTS)
	make -C $(MLXLIB)
	mv minilibx_mms_20200219/$(MLX) ./
	gcc -L. -lmlx $(MLXFLAGS) $(OBJECTS) -o $(NAME)

%.o:%.c
	gcc $(FLAGS) -I cub.h -I $(MLXLIB) -c $< -o $@

norme:
			@norminette  $(SRCS) cube.h

clean:
		rm -f $(OBJECTS)
		rm -f $(MLX)
		rm -f $(DEP)

fclean: clean
	rm -rf $(NAME)
	/bin/rm -f $(LIBNAME)
	/bin/rm -f screenshot.bmp

re: fclean all