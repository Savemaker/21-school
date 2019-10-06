#ifndef SH_21_H
#define SH_21_H
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <fcntl.h>
#include <dirent.h>

typedef struct hash_node{
    char *path;
    char *name;
	struct hash_node *next;
}hash_node;

typedef struct hash{
    int quant;
    hash_node **node;
}hash;

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
	int fd;         // o;      r;        n;
}tree;

hash *table;
char **my_env;

//parse_split
// int		*create_tab(int words);
// void	copy_split_delim(char **res, char *cmd, char delim);
// int		*count_each_word_delim(char *cmd, int words, char delim);
// char	**ft_split_delim(char *cmd, int words, char delim);
// int		count_words_delim(char *cmd, char delim);
// int		count_words(char *cmd);
// int		*count_each_word(char *cmd, int words);
// void	copy_split(char **res, char *cmd);
// char	**ft_full_split(char *cmd, int words);
// // 

//lexer.c

int		type(char *buf);
void	append(token **head, token *new);
int     buf_word_len(char *cmd);
char	*create_buf(char *cmd);
token	*create_token(char *cmd, size_t i, size_t cmd_len);
token	*create_new(char *cmd, size_t i, size_t cmd_len);
token	*lexer(char *cmd);
//

//create_tree.c
void	split(token **list, token **right);
tree	*create_node(token *list, int type, tree *parent);
void	split_list(token **list, token **right, tree *ast, int type);
void	split_semicolomn(token **left, token **right);
int		count_token_types(token *list, int type);
void	create_tree(tree *ast);
//


//copy_env.c
void	copy_env_to(char **envp, char **copy);
char	**create_env_copy(char **envp, int c);
int		count_pointers(char **envp);
char	*ft_getenv(const char *name, char **envp);
//


//execute_tree.c
void	execute_start(tree *ast, int in, int out);
void	execute_right(tree *ast, int in, int out, int temp);
void	simple_execution(tree *ast);
void	execute_tree_type_one(tree *ast);
void	execute_tree(tree *ast);
//

//redirections.c
int		check_type_class(token *list, int type, int count);
char	*take_buf(token *list, int type, int count);
int		check_for_type(token *list, int type);
int		check_for_redir(tree *ast, int type);
tree	*get_redirs_node(tree *ast);
int		get_redirections(tree *ast, int old, int type, int flag);
void    aggregation_order(token *list, int fd);
//

//create_argv.c
void	args_counter(tree *ast, tree *tmp);
void	argv_creation(tree *ast, tree *tmp);
void	create_argv(tree *ast);
//

//built_in.c
int     check_builtin(tree *ast);
int		execute_builtin(tree *ast);
void	free_copy_envp(char ***envp);
void	free_parse(char **parse, int w);
//

//ft_setenv.c
int     ft_setenv(char **parse, char **envp);
char	**realloc_envp(int pointers, char *name, char *value, char **envp);
char	*malloc_line(char *name, char *value);
void	copy_to_realloc(char **envp, char **res, char *name, char *value);
void	copy_index(char **ress, char *name, char *value);
int		test_getenv(const char *name, char *ret);
int		ft_getenv_index(const char *name, char **envp);
//

//ft_unsetenv.c
int		ft_unsetenv(char **parse, char **envp);
char	**realloc_envp_del(int p, char *name, char **envp);
void	copy_realloc_del(char **res, char **envp, int index);
//

//ft_cd.c
int     ft_cd(char **parse);
void	ft_cd_stuf(char **parse);
void	print_no_such(char *s);
void	update_pwd(char *name, char *oldpath);
//

//ft_split.c
char	**ft_split_delim(char *cmd, int words, char delim);
int		count_words_delim(char *cmd, char delim);
//


//create_hash_table.c
hash    *create_table(void);
unsigned int hashing(char *name, int size);
//
#endif