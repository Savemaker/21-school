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

int		main(int argc, char **argv, char **envp)
{
	pid_t p;
	char *cmd;

	cmd = NULL;
	while (argc)
	{
		print_shell_name();
		if (get_next_line(1, &cmd) == 1)
		{
			cmd = edit_command(cmd, envp);
			if ((p = fork()) == 0)
				execve(cmd, argv, envp);
			else
				waitpid(p, NULL, WUNTRACED);
		}
	}	
	return (0);
}