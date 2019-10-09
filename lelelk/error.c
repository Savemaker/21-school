/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:12:48 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/07 21:12:51 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_error_code_dope(int error_code)
{
	if (error_code == 9)
		return (RED"malloc() error"RESET);
	if (error_code == 10)
		return ("not a directory");
	if (error_code == 11)
		return (RED"chdir() error"RESET);
	if (error_code == 12)
		return (RED"setenv() error"RESET);
	if (error_code == 13)
		return ("no such file or directory");
	if (error_code == 14)
		return ("permission denied");
	if (error_code == 15)
		return (RED"tcgetattr() error"RESET);
	if (error_code == 16)
		return ("\e[91misatty() error:\e[39m not a terminal");
	if (error_code == 17)
		return (RED"tcsetattr() error"RESET);
	if (error_code == 18)
		return ("terminal type is not defined");
	if (error_code == 19)
		return ("could not access the termcap data base");
	if (error_code == 20)
		return ("specify a terminal type with `setenv TERM <yourtype>`");
	if (error_code == 21)
		return (RED"ioctl() error"RESET);
	if (error_code == 22)
		return (RED"open() error"RESET);
	if (error_code == 23)
		return (RED"close() error"RESET);
	if (error_code == 24)
		return (RED"time() error"RESET);
	return (NULL);
}

char	*check_error_code(int error_code)
{
	if (error_code == 1)
		return ("string not in pwd");
	if (error_code == 2)
		return ("too many arguments");
	if (error_code == 3)
		return (RED"getcwd() error"RESET);
	if (error_code == 5)
		return (RED"stat() error"RESET);
	if (error_code == 4)
		return (RED"lstat() error"RESET);
	if (error_code == 6)
		return ("command not found");
	if (error_code == 7)
		return (RED"execve() error"RESET);
	if (error_code == 8)
		return (RED"fork() error"RESET);
	return (check_error_code_dope(error_code));
}

void	perror_cmnd(char *cmnd, char *error_path, int error_code)
{
	g_shell->error = EXIT_FAILURE;
	ft_putstr_fd(cmnd, STDERR_FILENO);
	if (error_code != 0)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr(check_error_code(error_code));
	}
	if (error_path)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(error_path, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
