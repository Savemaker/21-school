/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:40:47 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/10/15 18:32:49 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELLNAME "21sh"

# include "libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/dir.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <setjmp.h>
# include <termios.h>
# include <termcap.h>
# include <pwd.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include <time.h>








# define BIT(N) (1 << N)
# define SET_BIT(X,N) ((X) |= (BIT(N)))
# define CHECK_FLAG(X,N) ((X) & (BIT(N)))



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



# define TYPE_PIPE 1
# define TYPE_CMND 2
# define TYPE_SUFFIX 3
# define TYPE_WORD 4
# define TYPE_REDIR 5


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
char	*sub_line(char *parse);
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
void	splitterok(t_token **list, t_token **right);
t_tree	*create_node(t_token *list, int type, t_tree *parent);
void	split_list(t_token **list, t_token **right, t_tree *ast, int type);
void	split_semicolomn(t_token **left, t_token **right);
int		count_token_types(t_token *list, int type);
void	create_tree_type_two(t_tree *ast, t_token *left, t_token *right);
void	create_tree_type_one(t_tree *ast, t_token *left, t_token *right);
void	create_tree(t_tree *ast);
//


//copy_env.c
//char	*ft_getenv(const char *name, char **envp);
char	*ft_getenv(char *name);
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
//int     ft_setenv(char **parse, char **envp);

int     ft_setenv(char *name, char *value);
//

//ft_unsetenv.c
void	copy_realloc_del(char **res, char **envp, int index);
char	**realloc_envp_del(int p, char *name, char **envp);
//int		ft_unsetenv(char **parse, char **envp);
int		ft_unsetenv(char *name);
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


















/*
** Termcaps
*/

# define TUP tputs(tgetstr("up", NULL), 1, &ft_putchar_int)
# define TLEFT_BORDER tputs(tgetstr("cr", NULL), 1, &ft_putchar_int)
# define TDOWN tputs(tgetstr("sf", NULL), 1, &ft_putchar_int)
# define TRIGHT tputs(tgetstr("nd", NULL), 1, &ft_putchar_int)
# define TLEFT tputs(tgetstr("le", NULL), 1, &ft_putchar_int)
# define TBELL tputs(tgetstr("bl", NULL), 1, &ft_putchar_int)
# define TCLEAR_STR tputs(tgetstr("cd", NULL), 1, &ft_putchar_int)
# define TDEL_CHAR tputs(tgetstr("dc", NULL), 1, &ft_putchar_int)


/*
** Modes
*/

# define DEFAULT_INPUT 0
# define HISTORY_INPUT 1
# define HISTORY_INPUT_STOP 2
# define QUOTE_INPUT 3
# define AUTOCOM_INPUT 4
# define HEREDOC_INPUT 5

/*
** History
*/
# define HISTSIZE 500
# define HISTFILESIZE 500
# define HISTFILE "/.21sh_history"



/*
** Error
*/
# define NOTINPWD 1
# define MANYARGS 2
# define GETCWDERR 3
# define LSTATERR 4
# define STATERR 5
# define CMNDNTFND 6
# define EXECVEERR 7
# define FORKERR 8
# define MLKERR 9
# define NOTDIR 10
# define CHDIRERR 11
# define GETENVERR 12
# define NOFLODIR 13
# define PMDND 14
# define TCGETATTR 15
# define NOTTERM 16
# define TCSETATTR 17
# define TTYNOTDFND 18
# define NOTERMCAP 19
# define SPECTTY 20
# define IOCTLERR 21
# define OPENERR 22
# define CLOSEERR 23
# define TIMEERR 24
# define PARSEERR_SEMICOLS 25
# define PARSEERR_PIPE 26

/*
**
*/
# define MAXDIR 4095
# define MAXLINE 2048
# define MAXHOSTNAME 64
# define MAXREAD 5





/*
** Symbs
*/
# define EOT '\004' //^D end of transmission
# define EOL "\n" //\n
# define CTRL_G '\007' //bell
#define CTRL_A "\001"
#define CTRL_E "\005"//
#define CTRL_F "\006"
#define CTRL_B "\002"
#define DEL "\177"
#define CTRL_L "\012"

#define FN_LEFT "\E[H"
#define FN_RIGHT "\E[F"

#define FN_UP "\E[5~"
#define FN_DOWN "\E[6~"
#define FN_DEL "\E[3~"

# define RIGHT_KEY "\E[C"
# define LEFT_KEY "\E[D"
# define UP_KEY "\E[A"
# define DOWN_KEY "\E[B"

/*
** Reset Color
*/
# define RESET "\033[0m"

/*
** Regular
*/
# define BLACK  	"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"

/*
** Bold
*/
# define BBLACK 	"\033[1;30m"
# define BRED		"\033[1;31m"
# define BGREEN		"\033[1;32m"
# define BYELLOW	"\033[1;33m"
# define BBLUE		"\033[1;34m"
# define BMAGENTA	"\033[1;35m"
# define BCYAN		"\033[1;36m"
# define BWHITE		"\033[1;37m"

/*
** Underline
*/
# define UBLACK  	"\033[4;30m"
# define URED		"\033[4;31m"
# define UGREEN		"\033[4;32m"
# define UYELLOW	"\033[4;33m"
# define UBLUE		"\033[4;34m"
# define UMAGENTA	"\033[4;35m"
# define UCYAN		"\033[4;36m"
# define UWHITE		"\033[4;37m"

/*
** Background
*/
# define BGBLACK 	"\033[40m"
# define BGRED		"\033[41m"
# define BGGREEN	"\033[42m"
# define BGYELLOW	"\033[43m"
# define BGBLUE		"\033[44m"
# define BGMAGENTA	"\033[45m"
# define BGCYAN		"\033[46m"
# define BGWHITE	"\033[47m"


//# define SHELL_NAME "\e[95m\e[1mminishell\e[0m🌚  "







typedef struct		s_autocom
{
	char			*content;
	size_t			content_size;
	int rows;
	int cols;
	int				select;
	struct s_autocom	*next;
}					t_autocom;

typedef struct		s_readline
{
	char			*line;
	char			*clipboard;
	unsigned short	maxwidth;
	unsigned short	maxheight;
	int				size;
	int				x;
	int				y;
	int				prompt_end;
	int				prompt_size;
//	int 	    	mode;
}					t_readline;


typedef struct		s_history
{
	char 			**cmnds;
	int 			index;
	char 			*path;
	int 			size; //кол-во команд в списке
//	int 			filesize; //кол-во строк в баффе
}					t_history;

typedef struct	s_shell
{
//	char		**env;
    char        *main_cmnd;
	t_readline	*input;
	int			error;
	int			sig;
	t_history 	*history;
	int 	    inputmode;


int emacs_on;
int emacs_off;
	char *autocom_buf;
int autocom_index;
int auto_quantity;
int auto_cols;
int auto_rows;
int max_request_width;
char *old_request;
}				t_shell;


struct termios g_saved_attributes;
t_shell			*g_shell;

int		launch(char *file, char **args, int absolute);
int		absolute_path_launch(char **cmnd);
void	print_env(char **env);
int		env_cmnd(void);
int		exit_cmnd(void);
//int		check_builtin(char *cmnd);
int		builtin(char **args);
void	launch_cd(char *path);
//int		cd_cmnd(char **args, int argc);
int		echo_cmnd(char **args);
char	*check_error_code(int error_code);
char	*check_error_code_dope(int error_code);
void	perror_cmnd(char *cmnd, char *error_path, int error_code);
int		find_bin(char *cmnd_name, char *path);
char	*path(char *name, char *path);
char	*check_extern_command(char **cmnd, int i);
int		external_launch(char **cmnd, char *paths);
void	clean_env(char **env_cp);
void	free_parse(char **parse, int w);
void	free_copy_envp(char ***envp);
int		str_quantity(char **env);
int		check_existenv(const char *name, char *request);
int		get_envindex(const char *name);
int		checkenv(char *envstr);
//char	*getenv_cmnd(char *name);
int		execute_cmnd(char **cmnd);
char	**make_env_cp(char **env_origin);
void	print_usage(void);
int		main(int argc, char **argv, char **env);
void	join_value(char **ress, char *name, char *value);
void	copy_to_realloc(char **envp, char **res, char *name, char *value);
char	**realloc_envp(int pointers, char *name, char *value, char **env);
//int		setenv_cmnd(char *name, char *value);
//void	cmnd_loop(void);
//void	signals(void);
void	handler_interrupt(int signal);
char	*check_sig_code(int sig_code);
char	**split(char **str, char *s, char c, int count);
int		count_words(char *str, char sign);
char	**split_cmnd(char const *s, char c);
void	copy_realloc_del(char **res, char **env, int index);
char	**realloc_envp_del(int p, char *name, char **env);
//int		unsetenv_cmnd(char *name);
int		env_strlen(char *s);
char	*cmnd_generator(const char *text, int state);
char	**cmnd_completion(const char *text, int start, int end);
int		getenv_strlen(char *str);
char	*malloc_line(char *name, char *value);
int		execute_cmnd(char **cmnd);
int		exe_multcmnds(char *line);
int		exe_cmnds(char *line);
int		execution(char *line);
void	check_cd(int argc, char **args, int cwderr);


//int		execution(char *line, t_history *history);
//void readline_cmnd(char **line, int prompt_size);

void readline_cmnd(char **line, int prompt_size);

void	cmnd_loop();
int display_history(char **cmnd);
int ft_nbrlen(int nb);
//void init_readline(t_readline *input, int prompt_size);
void	handler_win(int sig);
t_readline *init_readline(int prompt_size);
void	signals(int exe);
int ft_check_char(char *str, char c);


int		cd_cmnd(char **args);

/*
** quotes
*/
void quote_output(char *line, int q_type);
void quote_readline(int quote_type);
char	*skip_quotes(const char *src, char q_type);
char *change_last_char(char *str, char c);
int repeat_check_quote(char *line, char c);
int check_quote(char *line);
int display_added_prompt(int  prompt_type);

/*
** prompt
*/
int display_prompt(void);
int display_ordinary_prompt();
int display_cwd(void);
int display_host(void);
int display_user(void);





int ft_putchar_int(int c);


/*
** cursor move
*/
void	cursor_down(t_readline *input);
void	goto_lastsymb(t_readline *input);
void	cursor_up(t_readline *input);
void cursor_left(t_readline *input);
void cursor_right(t_readline *input);


/*
** goto
*/
void goto_inputstart(t_readline *input);
void goto_linestart(t_readline *input);
void goto_start(t_readline *input);
void goto_end(t_readline *input);
void goto_next_word(t_readline *input);
void goto_prev_word(t_readline *input);

/*
** cut copy
*/
void cut_after_cursor(t_readline *input);
void copy_before_cursor(t_readline *input);
void copy_after_cursor(t_readline *input);

/*
** enter del char
*/
void	del_leftchar(t_readline *input);
void	del_rightchar(t_readline *input);
void	char_enter(char *buf, t_readline *input);

/*
** clearing
*/
void clear_input(t_readline *input);
void clear_screen(t_readline *input);
void clear_visible_line(t_readline *input);


/*
** history
*/
void		his_search();
int display_his_prompt();
char *get_hiscmnd(char *line, t_history *history);
void scroll_his_forward(t_readline *input, t_history *history);
void scroll_his_back(t_readline *input, t_history *history);


/*
** init term
*/
t_history *init_history();
void set_input_tmode(void);
void init_term(void);
void exit_clean(void);
void reset_input_tmode(void);

/*
** custom prompt
*/

int display_custom_prompt(char *ps1);
int	prompt_time(unsigned int parsed);
int	get_time_format(unsigned int parsed, struct tm *local);
int	prompt_path(unsigned int parsed);
int	prompt_rights(unsigned int parsed);
int	prompt_his(unsigned int parsed, int his_size);
int display_dir(int tilde);
int	prompt_user_host(unsigned int parsed);

/*
** parse_ps1
*/
int	check_parsed(unsigned int parsed, char receivedchar);
unsigned int parse_ps1(char *str);
unsigned int	define_ctlcmnd(unsigned int parsed, char receivedchar);

/*
** autocom
*/
void autocom(t_readline *input);

#endif
