MAKEFLAGS 			+= --no-print-directory
NAME                = cub3d
LIBFT               = ./libft/libft.a
SRC_DIR             = src/
OBJ_DIR             = obj/
HEADER_DIR          = includes/
MLX_DIR             = ./mlx/
MLX				   = $(MLX_DIR)libmlx_Linux.a
CC                  = cc
CFLAGS              = -Wall -Werror -Wextra
RM                  = rm -f
SO_LONG_DIR         = $(SRC_DIR)main.c 

SRCS                = $(SO_LONG_DIR)
OBJ                 = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
all:                $(NAME)
$(NAME):           	$(OBJ) $(LIBFT) $(MLX) 
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -I $(MLX_DIR) -L $(MLX_DIR) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
$(LIBFT):
					@make -C ./libft
$(OBJ_DIR)%.o:      $(SRC_DIR)%.c
					@mkdir -p $(@D)
					@$(CC) -I $(MLX_DIR) -O3 $(INC) -c $< -o $@

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