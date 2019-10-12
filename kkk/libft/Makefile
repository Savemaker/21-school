#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/17 14:18:36 by bellyn-t          #+#    #+#              #
#    Updated: 2018/12/21 13:49:02 by bellyn-t         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC = *.c

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDES = libft.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) -c $(SRC) -I $(INCLUDES)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm  -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all