CFLAGS = -g -Wall -Wextra -Werror

CC = cc $(CFLAGS)

OBJ_DIR = objs/

SRC_MAIN = main.c

SRC_SETUP = $(addprefix src/setup/, setup_color.c setup_orientation.c setup_coord.c)

SRC_CHECKER = $(addprefix src/checker/, check_object.c check_object_utils.c check_obj1.c check_obj2.c)

SRC_INIT = $(addprefix src/init/, init_prog.c)

SRC_UTILS = $(addprefix src/utils/, open_file.c archer_atof.c free_array.c print_error.c)

OBJ_SETUP = $(SRC_SETUP:%.c=$(OBJ_DIR)%.o)

OBJ_MAIN = $(SRC_MAIN:%.c=$(OBJ_DIR)%.o)

OBJ_CHECKER = $(SRC_CHECKER:%.c=$(OBJ_DIR)%.o)

OBJ_INIT = $(SRC_INIT:%.c=$(OBJ_DIR)%.o)

OBJ_UTILS = $(SRC_UTILS:%.c=$(OBJ_DIR)%.o)

OBJS = $(OBJ_MAIN) $(OBJ_SETUP) $(OBJ_CHECKER) $(OBJ_INIT) $(OBJ_UTILS)

NAME = miniRT

LIBFT = inc/libft/libft.a

MLX = inc/minilibx-linux

MLXF = -L$(MLX) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@make bonus -C inc/libft
	@make -C inc/minilibx-linux
	$(CC) -o $(NAME) $(OBJS) inc/minilibx-linux/libmlx.a $(LIBFT) -I $(MLXF)

$(LIBFT):
	@make -C inc/libft/

$(OBJ_DIR)%.o : %.c
	@mkdir -p '$(@D)'
	$(CC) -o $@ -c $< ${<.c=.o}

clean:
	rm -rf $(OBJS)
	@make clean -C inc/libft/

fclean: clean
	rm -rf $(NAME)
	@make fclean -C inc/libft/

re: fclean all

.PHONY: all fclean clean re
