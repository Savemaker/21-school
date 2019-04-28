NAME = fillit
SRC = srcs/board.c \
	srcs/fillit.c \
	srcs/lib.c \
	srcs/listfunc.c \
	srcs/main.c \
	srcs/reading.c \
	srcs/slavastrdup.c \
	srcs/solving.c \
	srcs/validation.c \
	srcs/addone.c \
	srcs/addtwo.c

OBJ  = ${SRC:.c=.o}

FLAGS = -Wall -Werror -Wextra

.PHONY: all
all: ${NAME}

%.o:%.c
	gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all