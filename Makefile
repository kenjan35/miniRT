CFLAGS = -g -Wall -Wextra -Werror -O3

CC = cc $(CFLAGS)

OBJ_DIR = objs/

SRC_MAIN = main.c

SRC_SETUP = $(addprefix src/setup/, setup_color.c setup_orientation.c setup_coord.c setup_camera.c)

SRC_CHECKER = $(addprefix src/checker/, check_object.c check_object_utils.c check_obj1.c check_obj2.c)

SRC_INIT = $(addprefix src/init/, set_object.c init_prog.c)

SRC_MOVE = $(addprefix src/move/, rotation.c translation.c set_move.c)

SRC_LIGHT = $(addprefix src/light/, sphere.c cylinder.c hard_shadow.c)

SRC_IMAGE = $(addprefix src/image/, put_image.c ray_shape.c)

SRC_UTILS = $(addprefix src/utils/, open_file.c archer_atof.c free_array.c print_error.c math_utils.c math_operation.c quadrique_operation.c build_objects.c)

SRC_INTER = $(addprefix src/intersection/, intersection.c sphere.c cylinder.c plane.c plane_operation.c)

OBJ_SETUP = $(SRC_SETUP:%.c=$(OBJ_DIR)%.o)

OBJ_MAIN = $(SRC_MAIN:%.c=$(OBJ_DIR)%.o)

OBJ_CHECKER = $(SRC_CHECKER:%.c=$(OBJ_DIR)%.o)

OBJ_INIT = $(SRC_INIT:%.c=$(OBJ_DIR)%.o)

OBJ_MOVE = $(SRC_MOVE:%.c=$(OBJ_DIR)%.o)

OBJ_LIGHT = $(SRC_LIGHT:%.c=$(OBJ_DIR)%.o)

OBJ_IMAGE = $(SRC_IMAGE:%.c=$(OBJ_DIR)%.o)

OBJ_UTILS = $(SRC_UTILS:%.c=$(OBJ_DIR)%.o)

OBJ_INTER = $(SRC_INTER:%.c=$(OBJ_DIR)%.o)

OBJS = $(OBJ_MAIN) $(OBJ_SETUP) $(OBJ_CHECKER) $(OBJ_INIT) $(OBJ_MOVE) $(OBJ_IMAGE) $(OBJ_LIGHT) $(OBJ_UTILS) $(OBJ_INTER)

NAME = miniRT

LIBFT = inc/libft/libft.a

MLX = inc/minilibx-linux

MLXF = -L$(MLX) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@make --no-print-directory bonus -C inc/libft
	@make --no-print-directory -C inc/minilibx-linux
	@$(CC) -o $(NAME) $(OBJS) inc/minilibx-linux/libmlx.a $(LIBFT) -I $(MLXF)
	@clear
	@echo "\n\e[1;91mExecute the program with \e[0m./miniRT \e[1;92m[name.rt]\n"

$(LIBFT):
	@make --no-print-directory -C inc/libft/

$(OBJ_DIR)%.o : %.c
	@mkdir -p '$(@D)'
	$(CC) -o $@ -c $< ${<.c=.o}

clean:
	@rm -rf $(OBJS)
	@make --no-print-directory clean -C inc/libft/
	@clear
	@echo "\033[0;93mAll objects was suppressed\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make --no-print-directory fclean -C inc/libft/
	@clear
	@echo "\033[0;91mminiRT was deleted\033[0m"

re: fclean all

.PHONY: all fclean clean re
