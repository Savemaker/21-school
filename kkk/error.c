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
	if (error_code == MLKERR)
		return (RED"malloc() error"RESET);
	if (error_code == NOTDIR)
		return ("not a directory");
	if (error_code == CHDIRERR)
		return (RED"chdir() error"RESET);
	if (error_code == GETENVERR)
		return (RED"getenv() error"RESET);
	if (error_code == NOFLODIR)
		return ("no such file or directory");
	if (error_code == PMDND)
		return ("permission denied");
	if (error_code == TCGETATTR)
		return (RED"tcgetattr() error"RESET);
	if (error_code == NOTTERM)
		return ("\e[91misatty() error:\e[39m not a terminal");
	if (error_code == TCSETATTR)
		return (RED"tcsetattr() error"RESET);
	if (error_code == TTYNOTDFND)
		return ("terminal type is not defined");
	if (error_code == NOTERMCAP)
		return ("could not access the termcap data base");
	if (error_code == SPECTTY)
		return ("specify a terminal type with `setenv TERM <yourtype>`");
	if (error_code == IOCTLERR)
		return (RED"ioctl() error"RESET);
	if (error_code == OPENERR)
		return (RED"open() error"RESET);
	if (error_code == CLOSEERR)
		return (RED"close() error"RESET);
	if (error_code == TIMEERR)
		return (RED"time() error"RESET);
	if (error_code == PARSEERR_SEMICOLS)
		return ("parse error near ;;");
	if (error_code == PARSEERR_PIPE)
		return ("parse error near |");
	return (NULL);
}

char	*check_error_code(int error_code)
{
	if (error_code == NOTINPWD)
		return ("string not in pwd");
	if (error_code == MANYARGS)
		return ("too many arguments");
	if (error_code == GETCWDERR)
		return (RED"getcwd() error"RESET);
	if (error_code == STATERR)
		return (RED"stat() error"RESET);
	if (error_code == LSTATERR)
		return (RED"lstat() error"RESET);
	if (error_code == CMNDNTFND)
		return ("command not found");
	if (error_code == EXECVEERR)
		return (RED"execve() error"RESET);
	if (error_code == FORKERR)
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
