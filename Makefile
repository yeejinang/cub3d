# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yang <yang@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 15:59:25 by hyap              #+#    #+#              #
#    Updated: 2022/10/26 16:13:36 by yang             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRCS = ${wildcard srcs/*.c} ${wildcard gnl/*.c} ${wildcard srcs/utils/*.c} ${wildcard srcs/parsing/*.c}

SRCS = srcs/minimap/*.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBMLX = libmlx.dylib

FSANITIZE = -fsanitize=address 

NAME = cub3d

RM = rm -f

all: ${NAME}

${NAME}: ${SRCS}
	${CC} -I includes ${SRCS} ${LIBMLX} -o ${NAME}

clean:
	${RM} ${NAME}

fclean:
	${RM} ${NAME}

re: clean all

.PHONY: all clean re