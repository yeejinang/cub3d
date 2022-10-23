# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/19 15:59:25 by hyap              #+#    #+#              #
#    Updated: 2022/10/20 21:42:27 by hyap             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ${wildcard srcs/*.c} ${wildcard gnl/*.c} ${wildcard srcs/utils/*.c} ${wildcard srcs/parsing/*.c}

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBMLX = libmlx.dylib

FSANITIZE = -fsanitize=address 

NAME = cub3d

RM = rm -f

all: ${NAME}

${NAME}: ${SRCS}
	${CC} ${CFLAGS} -I includes ${SRCS} ${LIBMLX} -o ${NAME}

clean:
	${RM} ${NAME}

fclean:
	${RM} ${NAME}

re: clean all

.PHONY: all clean re