MAKEFLAGS 			+= --no-print-directory
NAME                = miniRT
LIBFT               = ./libft/
LIBFTA              = $(LIBFT)libft.a
SRC_DIR             = src/
OBJ_DIR             = obj/
INC         		= ./includes/
MLX_DIR             = ./mlx/
MLX				   	= $(MLX_DIR)libmlx_Linux.a
CC                  = cc
CFLAGS              = -g
RM                  = rm -f
MAIN_DIR         = $(SRC_DIR)main.c $(SRC_DIR)parse.c $(SRC_DIR)utils.c \
					$(SRC_DIR)frame.c $(SRC_DIR)vector.c $(SRC_DIR)utils2.c \
					$(SRC_DIR)e_sphere.c $(SRC_DIR)vector2.c $(SRC_DIR)e_plane.c \
					$(SRC_DIR)e_cylinder.c $(SRC_DIR)color.c $(SRC_DIR)color2.c \
					$(SRC_DIR)light.c $(SRC_DIR)cylinder_utils.c $(SRC_DIR)set_elements.c \
					$(SRC_DIR)parse_utils.c $(SRC_DIR)parse_utils2.c $(SRC_DIR)ray.c \
					$(SRC_DIR)e_triangle.c $(SRC_DIR)parse_utils3.c $(SRC_DIR)malloc.c\

SRCS                = $(MAIN_DIR)
OBJ                 = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
all:                $(NAME)
$(NAME):           	$(LIBFTA) $(OBJ) $(MLX) 
					@$(CC) $(CFLAGS) $(OBJ) $(LIBFTA) -I $(MLX_DIR) -L $(MLX_DIR) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
$(LIBFTA):
					@make -C $(LIBFT)
$(OBJ_DIR)%.o:      $(SRC_DIR)%.c
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
fclean:             clean
					@$(RM) $(NAME)
					@$(RM) $(LIBFTA)
re:                 fclean all
.PHONY:             all clean fclean re

# https://chatgpt.com/c/67c5d695-f574-800c-8f01-60375da82354