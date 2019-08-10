/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:39:24 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 16:12:22 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shell_name(void)
{
	ft_putstr("♿  \e[96m\e[1mminishell \e[0m");
}

int		check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "setenv") == 0)
		return (1);
	if (ft_strcmp(cmd, "unsetenv") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int		test_exp(char **parse)
{
	int i;

	i = 0;
	while (parse[i])
	{
		if (parse[i][0] == '$')
			return (1);
		if (parse[i][0] == '~')
			return (1);
		i++;
	}
	return (0);
}

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

void	free_copy_envp(char ***envp)
{
	int		p;
	char	**ref;

	ref = *envp;
	p = count_pointers(ref);
	free_parse(ref, p);
	envp = NULL;
}
