/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 16:47:35 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/07/24 16:18:36 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*create_path(char *name, char *path)
{
	char *new;
	char *res;

	if (ft_strcmp(path, "/") != 0)
		new = ft_strjoin(path, "/");
	else
		new = path;
	res = ft_strjoin(new, name);
	if (ft_strcmp(path, "/") != 0)
		free(new);
	return (res);
}

void	print_shell_name()
{
	ft_putstr("♿  \e[96m\e[1mminishell \e[0m");
}

const char	*ft_getenv(const char *name, char **envp)
{
	int i;
	char *ret;
	int len;

	i = 0;
	len = ft_strlen(name) + 1;
	while (envp[i])
	{
		ret = ft_strstr(envp[i], name);
		if (ret != NULL)
			return (ret + len);
		i++;
	}
	return (NULL);
}

int		check_path(char *path, char *cmd)
{
	DIR *dir;
	struct dirent *d;

	dir = opendir(path);
	while ((d = readdir(dir)) != NULL)
	{
		if (ft_strcmp(d->d_name, cmd) == 0)
			return (1);	
	}
	return (0);
}

char	*edit_command(char *cmd, char **envp)
{
	const char *path;
	char **paths;
	char *res;
	int i;

	i = 0;
	path = ft_getenv("PATH", envp);
	paths = ft_strsplit(path, ':');
	while (paths[i])
	{
		if (check_path(paths[i], cmd) == 1)
		{
			res = create_path(cmd, paths[i]);
			return (res);
		}
		i++;
	}
	return (cmd);
}

int		count_words(char *cmd)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ')
			i++;
		if (cmd[i] != '\0')
			w++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i] != ' ')
			i++;
	}
	return (w);
}

int		*create_tab(char *cmd)
{
	int *res;
	int i;
	int words;

	i = 0;
	words = count_words(cmd);
	res = (int *)malloc(sizeof(int) * words);
	while (i < words)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

int		*count_each_word(char *cmd)
{
	int i;
	int len;
	int *tab;
	int j;

	i = 0;
	j = 0;
	len = 0;
	tab = create_tab(cmd);
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ')
			i++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i] != ' ')
		{
			tab[j]++;
			i++;
		}
		j++;
	}
	return (tab);
}

void	copy_split(char **res, char *cmd)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ')
			i++;
		k = 0;
		if (cmd[i] == '\0')
			break;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i] != ' ')
			res[j][k++] = cmd[i++];
		res[j][k] = '\0';
		j++;
	}
}

char	**ft_full_split(char *cmd)
{
	char **res;
	int words;
	int *tab;
	int i;

	i = 0;
	tab = count_each_word(cmd);
	words = count_words(cmd);
	res = (char **)malloc(sizeof(char *) * words + 1);
	while (i < words)
	{
		res[i] = (char *)malloc(sizeof(char) * tab[i] + 1);
		i++;
	}
	res[i] = NULL;
	copy_split(res, cmd);
	return (res);
}

int		main(int argc, char **argv, char **envp)
{
	char *cmd;
	char **parse;
	pid_t p;

	(void)argv;
	parse = NULL;
	cmd = NULL;
	while (argc)
	{
		print_shell_name();
		if (get_next_line(1, &cmd) == 1)
		{
			parse = ft_full_split(cmd);
			parse[0] = edit_command(parse[0], envp);
			if ((p = fork()) == 0)
				execve(parse[0], parse, envp);
			else
				waitpid(p, NULL, WUNTRACED);
		}
	}	
	return (0);
}