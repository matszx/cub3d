# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcygan <mcygan@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 15:29:54 by mcygan            #+#    #+#              #
#    Updated: 2025/03/13 11:06:11 by mcygan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	cub3d
CC 				=	gcc
CFLAGS 			=	-Wall -Wextra -Werror -O3 -ffast-math -fsanitize=address
INC				=	-I/usr/include -Iminilibx
LIB				=	-Lminilibx -lmlx -L/usr/lib/X11 -lX11 -lXext -lm

SRC_FILES 		=	main.c \
					init.c \
					minimap.c \
					render.c \
					texture.c \
					move.c \
					handlers.c \
					utils.c

SRC_DIR			=	src/
SRC				=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR			=	obj/
OBJ				=	$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					$(CC) $(CFLAGS) $(INC) -c $< -o $@

all				:	$(OBJ_DIR) $(NAME)

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)

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
