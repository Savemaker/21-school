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

OBJ   = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(HEADER) Makefile
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all