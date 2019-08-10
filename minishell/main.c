/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:47:55 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 15:48:08 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_dir(char *path_from_env, char *name)
{
	DIR				*dir;
	struct dirent	*d;

	dir = opendir(path_from_env);
	while ((d = readdir(dir)) != NULL)
	{
		if (ft_strcmp(d->d_name, name) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

int		check_path(char *path)
{
	struct stat s;

	if ((lstat(path, &s)) == -1)
	{
		ft_putstr("minishell: No such file or directory: ");
		ft_putendl(path);
		return (-1);
	}
	if (access(path, X_OK) == -1)
	{
		ft_putstr("minishell: Permission denied: ");
		ft_putendl(path);
		return (-1);
	}
	return (0);
}

void	handle_sig(int sig)
{
	if (sig == 2)
		return ;
}

int		main(int argc, char **argv, char **envp)
{
	char *cmd;
	char **my_env;

	(void)argv;
	cmd = NULL;
	if (argc == 1)
	{
		my_env = create_env_copy(envp, count_pointers(envp));
		while (my_env != NULL)
		{
			print_shell_name();
			signal(SIGINT, handle_sig);
			if (get_next_line(0, &cmd) == 1)
			{
				my_env = take_command(cmd, my_env);
				free(cmd);
			}
			else
				break ;
		}
	}
	return (0);
}
