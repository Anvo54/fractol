# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avornane <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/18 14:42:01 by avornane          #+#    #+#              #
#    Updated: 2019/12/18 16:24:51 by avornane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
LIB = libft/libft.a 
CFLAGS = -Wall -Werror -Wextra
SRCS = main.c src/keyinput.c src/draw.c src/color.c src/fractals.c \
	src/mouseinput.c

OBJ = ${SRCS:.c=.o}

GCC = gcc -I /usr/X11/include -L /usr/X11/lib -lX11 -lmlx -lXext

all:	$(NAME)

$(NAME): $(OBJ) $(LIB)
	$(GCC) $(SRCS) $(LIB) -o $(NAME)

$(LIB): buildlib

buildlib:
	make -C libft

clean:
	/bin/rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
