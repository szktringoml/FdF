SRCS = fdf.c \
	   draw.c \
	

OBJS = ${SRCS:.c=.o}

NAME = fdf
LIBFT = libftex/libft.a
MLX = minilibx_macos/libmlx.a
CC	= cc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

${NAME}: $(LIBFT) $(MLX) all ;

$(LIBFT):
	make -C libftex
$(MLX):
	make -C minilibx_macos

.PHONY: all clean fclean re

all: ${OBJS} $(LIBFT) $(MLX);
	${CC} ${CFLAG} -o ${NAME} ${OBJS} $(LIBFT) $(MLX) -framework OpenGL -framework AppKit
clean: 
	rm -rf $(LIBFT)
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean clean all ;
