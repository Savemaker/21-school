NAME = minishell

SRC =	builtin.c \
		command.c \
		env_copy.c \
		getenv.c \
		main.c \
		parse.c \
		setenv.c \
		split.c \
		stuff.c \
		unsetenv.c \
		ft_cd.c \
		completion.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

LIB_INC = ./libft/includes

LIB_DIR = ./libft

.PHONY: all clean fclean

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) -I ./includes -I $(LIB_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) -o $@ $(OBJ) -I . -L./libft -lft -I $(LIB_INC) -lreadline -ledit

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	rm -rf $(OBJ)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re:	clean all