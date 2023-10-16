# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 16:07:31 by kousuzuk          #+#    #+#              #
#    Updated: 2023/10/16 13:38:45 by kousuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fdf.c \
	   draw.c \
	   input_map.c \
	   utils_draw.c \
	   error_message.c \
	   apply_properties.c \
	   operations.c \
	   routation.c \
	   main.c
	

OBJS = ${SRCS:.c=.o}

NAME = fdf
LIBFT = libftex/libft.a
MLX = minilibx_macos/libmlx.a
CC	= cc
CFLAGS = -Wall -Wextra -Werror

all: ${NAME} ${MLX} ;

${OBJS}: ${SRCS}
	${CC} ${CFLAGS} -c $< -o $@

#gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
${NAME}: ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} -c ${SRCS}
	${CC} ${CFLAGS} -o $@ ${SRCS} ${LIBFT} ${MLX} -framework OpenGL -framework AppKit 


${LIBFT}:
	make -C libftex

${MLX}:
	make -C minilibx_macos

clean: 
	make fclean -C libftex
	rm -rf ${LIBFT}
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean clean all ;

.PHONY: all clean fclean re