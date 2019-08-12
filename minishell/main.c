/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:47:55 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/11 15:31:46 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **my_env;

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

char	**action(char *cmd, char **my_env)
{
	int		i;
	int		count;
	char	**parsed_cmd;

	i = 0;
	count = count_words_delim(cmd, ';');
	parsed_cmd = ft_split_delim(cmd, count, ';');
	while (i < count)
	{
		my_env = take_command(parsed_cmd[i], my_env);
		i++;
	}
	free_parse(parsed_cmd, count);
	return (my_env);
}

void	signals()
{
	signal(SIGINT, handle_sig);
}

int		main(int argc, char **argv, char **envp)
{
	char *cmd;

	(void)argv;
	cmd = NULL;
	if (argc == 1)
	{
		my_env = create_env_copy(envp, count_pointers(envp));
		while (my_env != NULL)
		{
			print_shell_name();
			signals();
			if (get_next_line(0, &cmd) == 1)
			{
				my_env = action(cmd, my_env);
				free(cmd);
			}
			else
				break ;
		}
	}
	return (0);
}
