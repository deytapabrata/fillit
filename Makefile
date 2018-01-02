# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tadey <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/02 02:27:45 by tadey             #+#    #+#              #
#    Updated: 2018/01/02 02:27:49 by tadey            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
FLAGS = -Wall -Wextra -Werror
SRC = \
error.c\
main.c\
parse.c\
read.c\
solution.c\
libft.c\

all: $(NAME)

$(NAME): $(SRC)
	gcc $(FLAGS) -c $(SRC)
	gcc $(FLAGS) $(SRC:.c=.o) -o $(NAME)

clean:
	rm -f $(SRC:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all
