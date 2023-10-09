# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 16:07:31 by kousuzuk          #+#    #+#              #
#    Updated: 2023/10/09 16:55:10 by kousuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = fdf.c \
	   draw.c \
	   input_map.c \
	   utils_draw.c \
	   error_message.c \
	   apply_properties.c \
	   #operation.c
	

OBJS = ${SRCS:.c=.o}

NAME = fdf
LIBFT = libftex/libft.a
MLX = minilibx_macos/libmlx.a
CC	= cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) ${NAME} $(MLX) ;

#cflagsは今はいいや
%.o: %.c
	$(CC) -c -g $< -o $@

#gcc *.c libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
#cflagsは今はいいや
${NAME}: $(LIBFT) ${OBJS}
	$(CC) -c $(SRCS) -g
	${CC} -o $@ $(SRCS) $(LIBFT) $(MLX) -g -framework OpenGL -framework AppKit 


$(LIBFT):
	make -C libftex

$(MLX):
	make -C minilibx_macos

clean: 
	rm -rf $(LIBFT)
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean clean all ;

.PHONY: all clean fclean re