NAME = 21sh

SRC =error.c\
	free.c\
	readline.c\
	shell_loop.c\
	signals.c\
	completion.c\
	get_next_line/get_next_line.c\
	quotes.c\
	prompt.c\
	cursor.c\
	goto.c\
	cut_copy.c\
	enter_del_char.c\
	clearing.c\
	history.c\
	init_term.c\
	main.c


OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a

LIB_INC = ./libft/includes

LIB_DIR = ./libft

GNL_INC = ./get_next_line/get_next_line.h

GREEN = \033[0;32m

.PHONY: all clean fclean

all: $(NAME)

%.o:%.c
	@gcc $(FLAGS) -I ./includes -I $(LIB_INC) -I $(GNL_INC) -o $@ -c $<

$(NAME): $(LIBFT) $(OBJ)
	@gcc $(FLAGS) -o $@ $(OBJ) -I . -L./libft -lft -I $(LIB_INC) -I $(GNL_INC) -lreadline -ledit -ltermcap
	@echo "$(GREEN)Co︎mpiled $(NAME) successfully!"
$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	@echo "Clean object files"
	@rm -rf $(OBJ)
	@make clean -C $(LIB_DIR)

fclean: clean
	@echo "Clean $(NAME)"	
	@rm -rf $(NAME)
	@make fclean -C $(LIB_DIR)

re:	clean all