# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 15:21:23 by abakirca          #+#    #+#              #
#    Updated: 2024/11/07 15:32:05 by abakirca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 			+= --no-print-directory
NAME                = cub3d
CC                  = cc
CFLAGS              = -Wall -Werror -Wextra
SRC_DIR             = src/
OBJ_DIR             = obj/
HEADER_DIR          = -I includes/
MLX_DIR             = ./mlx/
GNL_DIR				= get_next_line/
LIBFT               = ./libft/libft.a
MLX				  	= $(MLX_DIR)libmlx_Linux.a
RM                  = rm -rf

SRCS                = $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c $(SRC_DIR)main.c

OBJ                 = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

RED					= \033[31m
GREEN				= \033[32m
YELLOW				= \033[33m
BLUE				= \033[34m
MAGENTA				= \033[35m
CYAN				= \033[36m
RESET				= \033[0m

all:                $(NAME)

$(NAME):           	$(OBJ) $(LIBFT) $(MLX) 
					@$(CC) $(CFLAGS) $(HEADER_DIR) $(OBJ) $(LIBFT) -I $(MLX_DIR) -L $(MLX_DIR) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(OBJ_DIR)%.o:      $(SRC_DIR)%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(HEADER_DIR) -I $(MLX_DIR) -O3 $(INC) -c $< -o $@

$(LIBFT):
					@make -C ./libft

$(MLX):
					@make -C $(MLX_DIR)

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./libft
					@make clean -C $(MLX_DIR)

fclean:             clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFT)

re:                 fclean all

.PHONY:             all clean fclean re