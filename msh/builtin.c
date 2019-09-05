/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:32:51 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/03 20:01:07 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_echo(char **parse, char **envp)
{
	int i;

	i = 1;
	while (parse[i])
	{
		if (ft_strcmp(parse[i], " ") == 0)
		{
			i++;
			continue;
		}
		ft_putstr(parse[i]);
		if (parse[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (envp);
}

char	**ft_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putendl(envp[i]);
		i++;
	}
	return (envp);
}

char	**ft_exit(char **envp)
{
	free_copy_envp(&envp);
	return (NULL);
}

char	**execute_builtin(char **parse, char **envp)
{
	if (ft_strcmp(parse[0], "echo") == 0)
		return (ft_echo(parse, envp));
	if (ft_strcmp(parse[0], "cd") == 0)
		return (ft_cd(parse, envp));
	if (ft_strcmp(parse[0], "setenv") == 0)
		return (ft_setenv(parse, envp));
	if (ft_strcmp(parse[0], "unsetenv") == 0)
		return (ft_unsetenv(parse, envp));
	if (ft_strcmp(parse[0], "env") == 0)
		return (ft_env(envp));
	if (ft_strcmp(parse[0], "exit") == 0)
		return (ft_exit(envp));
	return (envp);
}
