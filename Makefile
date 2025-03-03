# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abakirca <abakirca@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/25 14:38:20 by abakirca          #+#    #+#              #
#    Updated: 2025/03/03 19:41:16 by abakirca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS			+= --no-print-directory
NAME				= miniRT
LIBFT				= ./libft/
LIBFTA				= $(LIBFT)libft.a
SRC_DIR				= src/
OBJ_DIR				= obj/
INC					= ./includes/
MLX_DIR				= ./mlx/
MLX					= $(MLX_DIR)libmlx_Linux.a
CC					= cc
CFLAGS				= -g
RM					= rm -f
MAIN_DIR			=	$(SRC_DIR)main.c $(SRC_DIR)parse.c $(SRC_DIR)utils.c \
						$(SRC_DIR)frame.c $(SRC_DIR)vector.c $(SRC_DIR)utils2.c \
						$(SRC_DIR)e_sphere.c $(SRC_DIR)vector2.c $(SRC_DIR)e_plane.c \
						$(SRC_DIR)e_cylinder.c $(SRC_DIR)color.c $(SRC_DIR)color2.c \
						$(SRC_DIR)light.c $(SRC_DIR)cylinder_utils.c $(SRC_DIR)set_elements.c \
						$(SRC_DIR)parse_utils.c $(SRC_DIR)parse_utils2.c $(SRC_DIR)ray.c \
						$(SRC_DIR)parse_utils3.c $(SRC_DIR)malloc.c\

SRCS				= $(MAIN_DIR)
OBJ					= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

COLOR_YELLOW	=	\033[0;33m \033[1m
COLOR_GREEN		=	\033[0;32m \033[1m
COLOR_RED		=	\033[0;31m \033[1m
COLOR_END		=	\033[0m

all:				$(NAME)
					

$(NAME):			$(LIBFTA) $(OBJ) $(MLX) 
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFTA) -I $(MLX_DIR) -L $(MLX_DIR) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
					@echo "$(COLOR_YELLOW)$(NAME)		$(COLOR_GREEN)[is ready]$(COLOR_END)"
$(LIBFTA):
					@make -C $(LIBFT)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -I $(MLX_DIR) -I $(LIBFT) -I $(INC) -c $< -o $@

$(MLX):
					@make -C $(MLX_DIR)

norm:
					@norminette  $(INC) $(SRC_DIR) $(LIBFT)

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C $(LIBFT)
					@make clean -C $(MLX_DIR)
					@echo "$(COLOR_YELLOW)objects	$(COLOR_RED)[are cleaned!]$(COLOR_END)"

fclean:				clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFTA)
					@echo "$(COLOR_YELLOW)$(NAME)		$(COLOR_RED)[is cleaned]$(COLOR_END)"

re:					fclean all

.PHONY:				all clean fclean re
