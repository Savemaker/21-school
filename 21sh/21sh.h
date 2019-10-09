#ifndef SH_21_H
#define SH_21_H
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct s_hash_node{
    char *path;
    char *name;
	struct s_hash_node *next;
}t_hash_node;

typedef struct s_hash{
    int quant;
    t_hash_node **node;
}t_hash;

typedef struct s_tokens{
	int type;                 // 1 = |        2 = ;         3 = redirect         4 = aggregation
	char *buf;
	struct s_tokens *next;
}t_token;

typedef struct s_tree{
	struct s_tree *parent;
	struct s_tree *left;
	struct s_tree *right;
	t_token		*current;
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
}t_tree;

t_hash *g_table;
char **g_my_env;

//main.c
void	action(char *cmd);
void	update_lexer(t_token **list);
int		semantics_semicolomn(t_token *list);
int		semantics(t_token *list);
char	*sub_line_dollar(char *parse);
char	*sub_line(char *parse, char **envp);
char	*sub_line_stuf(char *parse);
//

//lexer.c
int		type(char *buf);
void	append(t_token **head, t_token *new);
int     buf_word_len(char *cmd);
char	*create_buf(char *cmd);
char	*create_token_buf(char *cmd, size_t i, size_t cmd_len);
t_token *create_token_new(char *buf);
t_token	*create_token(char *cmd, size_t i, size_t cmd_len);
t_token	*create_new(char *cmd, size_t i, size_t cmd_len);
size_t	lexer_count_i(char *cmd, int i);
t_token	*lexer(char *cmd);
//

//create_tree.c
void	split(t_token **list, t_token **right);
t_tree	*create_node(t_token *list, int type, t_tree *parent);
void	split_list(t_token **list, t_token **right, t_tree *ast, int type);
void	split_semicolomn(t_token **left, t_token **right);
int		count_token_types(t_token *list, int type);
void	create_tree_type_two(t_tree *ast, t_token *left, t_token *right);
void	create_tree_type_one(t_tree *ast, t_token *left, t_token *right);
void	create_tree(t_tree *ast);
//


//copy_env.c
char	*ft_getenv(const char *name, char **envp);
int		count_pointers(char **envp);
void	copy_env_to(char **envp, char **copy);
char	**create_env_copy(char **envp, int c);
//


//execute_tree.c
int		check_path(char *path);
char	*create_path(char *name, char *path);
char	*get_cmd(char *cmd, int hash);
int		argv_checker(char **argv);
void	execute_start_fork(t_tree *ast, int in, int out, t_tree *redirs);
int		execute_start(t_tree *ast, int in, int out);
void	close_fds(int out, int temp);
void	execute_right_cmd(t_tree *ast, int in, int out, int temp);
int		execute_right(t_tree *ast, int in, int out, int temp);
void	simple_execution_fork(t_tree *ast, int in, int out);
void	simple_execution(t_tree *ast);
void	create_files(t_tree *ast);
int		execute_tree_type_one_start(t_tree *ast, int fd[2]);
void	execute_tree_type_one(t_tree *ast);
void	execute_tree(t_tree *ast);
//

//redirections.c
int		check_type_class(t_token *list, int type, int count);
char	*take_buf(t_token *list, int type, int count);
int		check_for_type(t_token *list, int type);
int		check_for_redir(t_tree *ast, int type);
t_tree	*get_redirs_node(t_tree *ast);
void    aggregation_order(t_token *list, int fd);
int		get_redirections(t_tree *ast, int old, int type, int flag);
//

//create_argv.c
void	args_counter(t_tree *ast, t_tree *tmp);
void	argv_creation(t_tree *ast, t_tree *tmp);
void	create_argv(t_tree *ast);
//

//built_in.c
void	free_parse(char **parse, int w);
int		ft_echo(char **parse);
int     ft_env(char **envp);
int		ft_exit(char **envp);
int     check_builtin(t_tree *ast);
int		builtin_execution(t_tree *ast);
int		execute_builtin(t_tree *ast);
//

//ft_setenv.c
void	copy_index(char **ress, char *name, char *value);
int		test_getenv(const char *name, char *ret);
int		ft_getenv_index(const char *name, char **envp);
void	copy_to_realloc(char **envp, char **res, char *name, char *value);
char	*malloc_line(char *name, char *value);
char	**realloc_envp(int pointers, char *name, char *value, char **envp);
int     ft_setenv(char **parse, char **envp);
//

//ft_unsetenv.c
void	copy_realloc_del(char **res, char **envp, int index);
char	**realloc_envp_del(int p, char *name, char **envp);
int		ft_unsetenv(char **parse, char **envp);
//

//ft_cd.c
void	update_pwd(char *name, char *oldpath);
void	print_no_such(char *s);
void	ft_cd_stuf(char **parse);
int     ft_cd(char **parse);
//

//ft_split.c
int		*create_tab(int words);
void	copy_split_delim(char **res, char *cmd, char delim);
int		*count_each_word_delim(char *cmd, int words, char delim);
int		count_words_delim(char *cmd, char delim);
char	**ft_split_delim(char *cmd, int words, char delim);
//


//create_hash_table.c
int     	count_command(char *path);
int     	counter(void);
int			hashing(char *name, int size);
void		get_bin_fresh(t_hash_node **node, int hash_i, char *name, char *path);
void		get_bin_used(t_hash_node **node, int hash_i, char *name, char *path);
void    	get_bin_from_path(char *path, t_hash *new);
void    	insert_in_table(t_hash *new);
t_hash    *create_table(void);
//


//free.c
void	free_token_list(t_token **list);
void	free_copy_envp(char ***envp);
void	free_tree(t_tree *tree);
void	free_hash_table(t_hash **table);
//
#endif
