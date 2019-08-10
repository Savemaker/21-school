/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:14:34 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 15:28:45 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

int		count_words(char *cmd);
int		*create_tab(int words);
int		*count_each_word(char *cmd, int words);
void	copy_split(char **res, char *cmd);
char	**ft_full_split(char *cmd, int words);
void	copy_split_delim(char **res, char *cmd, char delim);
int		*count_each_word_delim(char *cmd, int words, char delim);
char	**ft_split_delim(char *cmd, int words, char delim);
int		count_words_delim(char *cmd, char delim);
int		check_path(char *path);
int		count_pointers(char **envp);
void	free_copy_envp(char ***envp);

char	**create_env_copy(char **envp, int c);
void	copy_env_to(char **envp, char **copy);
void	print_shell_name(void);
void	handle_sig(int sig);
char	**take_command(char *cmd, char **envp);
char	**edit_parse(char **parse, char **envp);
int		test_exp(char **parse);
char	**sub_parse(char **parse, char **envp);
char	*ft_getenv(const char *name, char **envp);
int		test_getenv(const char *name, char *ret);
int		check_builtin(char *cmd);
char	**execute_builtin(char **parse, char **envp);
char	**ft_echo(char **parse, char **envp);
char	**ft_cd(char **parse, char **envp);
char	**ft_env(char **envp);
char	**ft_setenv(char **parse, char **envp);
char	**realloc_envp(int pointers, char *name, char *value, char **envp);
char	*malloc_line(char *name, char *value);
void	copy_to_realloc(char **envp, char **res, char *name, char *value);
void	copy_index(char **ress, char *name, char *value);
char	**ft_unsetenv(char **parse, char **envp);
char	**realloc_envp_del(int p, char *name, char **envp);
int		ft_getenv_index(const char *name, char **envp);
void	copy_realloc_del(char **res, char **envp, int index);
char	**ft_exit(char **envp);
char	**execute_command(char **parse, char **envp);
int		absolute_execution(char **parse, char **envp);
int		check_path(char *path);
int		check_command(char **command, char **envp);
int		open_dir(char *path_from_env, char *name);
void	relative_execution(char *path, char **command, char **envp);
char	*create_path(char *name, char *path);
void	free_parse(char **parse, int w);

#endif
