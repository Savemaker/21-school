/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:51:43 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/07 20:52:13 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]);
		ft_putchar('\n');
		i++;
	}
}

int		env_cmnd(void)
{
	int i;

	i = 0;
	while (g_shell->env[i])
	{
		if (!(checkenv(g_shell->env[i])))
			return (1);
		i++;
	}
	print_env(g_shell->env);
	return (1);
}

int		exit_cmnd(void)
{
	clean_env(g_shell->env);

	free(g_shell->history->path);
	clean_env(g_shell->history->cmnds);
	return (EXIT_SUCCESS);
}

int		check_builtin(char *cmnd)
{
	if (!ft_strcmp(cmnd, "cd"))
		return (1);
	if (!ft_strcmp(cmnd, "env"))
		return (1);
	if (!ft_strcmp(cmnd, "echo"))
		return (1);
	if (!ft_strcmp(cmnd, "setenv"))
		return (1);
	if (!ft_strcmp(cmnd, "unsetenv"))
		return (1);
	if (!ft_strcmp(cmnd, "exit"))
		return (1);
	if (!ft_strcmp(cmnd, "history"))
		return (1);
	return (0);
}

int		builtin(char **args)
{
	if (!ft_strcmp(args[0], "cd"))
		return (cd_cmnd(args, str_quantity(args)));
	if (!ft_strcmp(args[0], "env"))
		return (env_cmnd());
	if (!ft_strcmp(args[0], "setenv"))
		return (setenv_cmnd(args[1], args[2]));
	if (!ft_strcmp(args[0], "unsetenv"))
		return (unsetenv_cmnd(args[1]));
	if (!ft_strcmp(args[0], "echo"))
		return (echo_cmnd(args));
	if (!ft_strcmp(args[0], "exit"))
		return (exit_cmnd());
	if (!ft_strcmp(args[0], "history"))//put into builtin
		return(display_history(args));
	return (1);
}
