NAME = ft_ls

SRC = ft_ls.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIB	= libft/

LIBFT = -L./libft -lft

LIB_INC = -I libft/includes

.PHONY: all

all: $(NAME)

%.o:%.c
	gcc $(FLAGS) $(LIB_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIB_INC)

$(LIBFT):
	make -C $(LIB)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all