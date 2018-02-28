#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/28 16:17:11 by lberezyn          #+#    #+#              #
#    Updated: 2018/02/28 16:17:16 by lberezyn         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RT

SRC = src/hooks.c \
	  src/create.c \
	  src/scenes.c \
	  src/scene.c \
	  src/vectors.c \
	  src/draw.c \
	  src/figures.c \
	  src/main.c \
	  src/trace.c \

OFILES = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror -O3

all: $(NAME)

$(NAME):  $(OFILES) include/ft_rtv.h
	@make -C libft
	@clang $(FLAG) -L./libft -lft $(OFILES) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
	@echo "$(NAME) SUCCESSFULLY compiled"

%.o : src/%.c include/ft_rtv.h
	@clang $(FLAG) -o $@ -c $<

clean:
	rm -f $(OFILES)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re
