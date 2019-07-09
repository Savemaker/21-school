#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/24 19:23:08 by gbeqqo            #+#    #+#              #
#    Updated: 2019/01/19 18:30:49 by gbeqqo           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC = *.c

OBJ = *.o

HEADER = ./includes

all:	$(NAME)

$(NAME):
	gcc -c -Wall -Werror -Wextra  $(SRC) -I $(HEADER)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f *.o

fclean:	clean
	/bin/rm -f $(NAME)

re:	fclean all