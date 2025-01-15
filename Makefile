CFLAGS = -g -Wall -Wextra -Werror

CC = cc $(CFLAGS)

SRCS = main.c \
	   open_file.c \
	   archer_atof.c \
	   check_object.c \
	   check_object_utils.c \
	   setup_color.c \
	   setup_orientation.c \
	   setup_coord.c \
	   check_obj1.c \
	   check_obj2.c \
	   free_array.c \
	   print_error.c \

OBJS = ${SRCS:.c=.o}

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

.c.o:
	$(CC) -o $@ -c $< ${<.c=.o}

clean:
	rm -rf $(OBJS)
	@make clean -C inc/libft/

fclean: clean
	rm -rf $(NAME)
	@make fclean -C inc/libft/

re: fclean all

.PHONY: all fclean clean re
