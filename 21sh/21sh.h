#ifndef SH_21_H
#define SH_21_H
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <fcntl.h>

typedef struct tokens{
	int type;                 // 1 = |        2 = ;         3 = redirect         4 = aggregation
	char *buf;
	struct tokens *next;
}token;

typedef struct tree{
	struct tree *parent;
	struct tree *left;
	struct tree *right;
	token		*current;
	char		**argv;
	int			args;
	int			cur;
	int t_pipes;
	int t_semis;
	int in;
	int out;
	int type;   // 1 = pipe; 2 = command; 3 = suffix; 4 = word;
	int exe;
	int fd;
}tree;



//parse_split
int		*create_tab(int words);
void	copy_split_delim(char **res, char *cmd, char delim);
int		*count_each_word_delim(char *cmd, int words, char delim);
char	**ft_split_delim(char *cmd, int words, char delim);
int		count_words_delim(char *cmd, char delim);
int		count_words(char *cmd);
int		*count_each_word(char *cmd, int words);
void	copy_split(char **res, char *cmd);
char	**ft_full_split(char *cmd, int words);
// 

//lexer.c

int		type(char *buf);
void	append(token **head, token *new);
int     buf_word_len(char *cmd);
char	*create_buf(char *cmd);
token	*create_token(char *cmd, int i, size_t cmd_len);
token	*create_new(char *cmd, int i, size_t cmd_len);
token	*lexer(char *cmd);
//

//tree_creation.c
void	split(token **list, token **right);
tree	*create_node(token *list, int type, tree *parent);
void	split_list(token **list, token **right, tree *ast, int type);
void	split_semicolomn(token **left, token **right);
int		count_token_types(token *list, int type);
void	create_tree(tree *ast);
//

void	execute_tree(tree *ast);


#endif