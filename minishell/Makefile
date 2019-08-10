NAME = minishell

SRC = main.c parse.c split.c setenv.c unsetenv.c builtin.c getenv.c env_copy.c stuff.c command.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

LIB	= libft/

LIBFT = -L./libft -lft

LIB_INC = -I libft/includes

.PHONY: all

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -I . $(LIB_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) -o $(NAME) -I . $(OBJ) $(LIBFT) $(LIB_INC)

$(LIBFT):
	make -C $(LIB)

clean:
	rm -rf $(OBJ)
	make clean -C $(LIB)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB)

re: fclean all