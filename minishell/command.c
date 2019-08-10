/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:42:43 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 15:44:08 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		absolute_execution(char **parse, char **envp)
{
	int		test;
	pid_t	p;
	int		stat;

	test = check_path(parse[0]);
	if (test == 0)
	{
		p = fork();
		if (p == -1)
		{
			ft_putendl("Can't fork");
			return (1);
		}
		if (p == 0)
		{
			execve(parse[0], parse, envp);
		}
		else
		{
			wait(&stat);
		}
	}
	return (1);
}

char	**execute_command(char **parse, char **envp)
{
	int check;

	if (parse[0][0] == '.' || parse[0][0] == '/')
	{
		check = absolute_execution(parse, envp);
	}
	else
	{
		check = check_command(parse, envp);
	}
	return (envp);
}

char	**take_command(char *cmd, char **envp)
{
	int		words;
	char	**parse;

	words = count_words(cmd);
	parse = ft_full_split(cmd, words);
	if (parse[0])
	{
		parse = edit_parse(parse, envp);
		if (parse[0] != NULL)
		{
			if (check_builtin(parse[0]) == 1)
				envp = execute_builtin(parse, envp);
			else
				envp = execute_command(parse, envp);
			if (envp == NULL)
			{
				free_parse(parse, words);
				return (NULL);
			}
		}
	}
	free_parse(parse, words);
	return (envp);
}

int		check_command(char **command, char **envp)
{
	char	**split;
	char	*env_path;
	int		i;
	int		words;

	i = 0;
	env_path = ft_getenv("PATH", envp);
	words = count_words_delim(env_path, ':');
	split = ft_split_delim(env_path, words, ':');
	while (split[i])
	{
		if (open_dir(split[i], command[0]) == 1)
		{
			relative_execution(split[i], command, envp);
			free_parse(split, words);
			return (1);
		}
		i++;
	}
	ft_putstr("minishell: No such file or directory: ");
	ft_putendl(command[0]);
	free_parse(split, words);
	return (0);
}

void	relative_execution(char *path, char **command, char **envp)
{
	char	*exe_path;
	pid_t	p;
	int		w;

	exe_path = create_path(command[0], path);
	if (check_path(exe_path) == 0)
	{
		p = fork();
		if (p == -1)
		{
			ft_putendl("Can't fork");
			free(exe_path);
		}
		if (p == 0)
		{
			execve(exe_path, command, envp);
		}
		else
		{
			wait(&w);
			free(exe_path);
		}
	}
}
