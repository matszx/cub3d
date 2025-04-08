# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 15:29:54 by mcygan            #+#    #+#              #
#    Updated: 2025/04/08 15:07:49 by mcygan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	cub3d
CC 				=	gcc
CFLAGS 			=	-Wall -Wextra -Werror -O3 -ffast-math -fsanitize=address
INC				=	-I/usr/include -Iminilibx
LIB				=	-Lminilibx -lmlx -L/usr/lib/X11 -lX11 -lXext -lm

SRC_FILES 		=	main.c \
					parser/parse.c \
					parser/init.c \
					parser/gnl.c \
					parser/utils.c \
					parser/split.c \
					parser/map.c \
					parser/grid.c \
					raycaster/render.c \
					raycaster/minimap.c \
					raycaster/texture.c \
					raycaster/handlers.c \
					raycaster/move.c \
					raycaster/utils.c
					
SRC_DIR			=	src/
SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR			=	obj/
OBJ				=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

all				:	$(OBJ_DIR) $(NAME)

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)parser/ $(OBJ_DIR)raycaster

$(NAME)			:	$(OBJ)
					@make -C minilibx
					$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) $(LIB)

clean			:
					@make clean -C minilibx
					rm -rf $(OBJ_DIR)

fclean			:	clean
					rm -f $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
