/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolutepath_launch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:10:26 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/08 19:21:01 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch(char *file, char **args, int absolute)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(file, args, g_shell->env) == -1 && (access(file, F_OK)
		&& !access(file, X_OK)))
			perror_cmnd(SHELLNAME, file, PMDND);
		if (!absolute)
			free(file);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror_cmnd(SHELLNAME, NULL, FORKERR);
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	if (!absolute)
		free(file);
	return (1);
}

int		absolute_path_launch(char **cmnd)
{
	struct stat s;

	if (!ft_strcmp(cmnd[0], "/") || !ft_strcmp(cmnd[0], "./")
	|| !ft_strcmp(cmnd[0], "."))
		return (1);
	if (stat(cmnd[0], &s) == -1)
		perror_cmnd(SHELLNAME, NULL, LSTATERR);
	if (S_ISDIR(s.st_mode))
	{
		perror_cmnd(SHELLNAME, cmnd[0], CMNDNTFND);
		return (1);
	}
	if (access(cmnd[0], X_OK))
	{
		if (access(cmnd[0], F_OK) == -1)
			perror_cmnd(SHELLNAME, cmnd[0], CMNDNTFND);
		else
			perror_cmnd(SHELLNAME, cmnd[0], PMDND);
		return (1);
	}
	return (launch(cmnd[0], cmnd, 1));
}
