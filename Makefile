CFLAGS = -Wall -Wextra -Werror

CC = gcc $(CFLAGS)

SRCS = 

OBJS = ${SRCS:.c=.o}

NAME = miniRT

LIBFT = inc/libft/libft.a

MLX = inc/minilibx-linux

MLXF = -L$(MLX) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@make -C inc/minilibx-linux
	$(CC) -o $(NAME) $(OBJ) inc/minilibx-linux/libmlx.a $(LIBFT) -I $(MLXF)

$(LIBFT):
	@make -C inc/libft/

.c.o:
	$(CC) -o $@ -c $< ${<.c=.o}

clean:
	rm -rf $(OBJ)
	@make clean -C inc/libft/

fclean: clean
	rm -rf $(NAME)
	@make fclean -C inc/libft/

re: fclean all

.PHONY: all fclean clean re
