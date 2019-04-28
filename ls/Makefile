NAME = ft_ls

SRC = test.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

.PHONY: all

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all