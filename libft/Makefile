# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahorker <ahorker@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 23:48:56 by ahorker           #+#    #+#              #
#    Updated: 2019/01/13 22:10:02 by ahorker          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror
OPT = -I $(HEADER)
NAME = libft.a
HEADER = ./includes/libft.h
FUNCS = $(shell cat ./includes/libft.h | grep -Eo "ft_\w+")
SRC = $(FUNCS:=.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	rm -f */*.h.gch*

%.o: %.c
	gcc $(FLAGS) $(OPT) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
