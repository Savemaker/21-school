#ifndef SH_21_H
#define SH_21_H
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

typedef struct tokens{
	int type;                 // 1 = |        2 = ;         3 = redirect         4 = aggregation
	char *buf;
	struct tokens *next;
}token;

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


#endif