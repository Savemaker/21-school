/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:17:33 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/08 16:18:39 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//
//void	launch_cd(char *path)
//{
//	struct stat s;
//
//	if (path[0] == ' ')
//		path = getenv_cmnd("HOME");
//	if (path && !access(path, F_OK))
//	{
//		if ((stat(path, &s)) == -1)
//			perror_cmnd("minishell", NULL, STATERR);
//		else if (!S_ISDIR(s.st_mode))
//			perror_cmnd("cd", path, NOTDIR);
//		else if (access(path, X_OK))
//			perror_cmnd("minishell", path, PMDND);
//		else
//		{
//			if (chdir(path) == -1)
//				perror_cmnd("cd", path, CHDIRERR);
//		}
//	}
//	else
//		perror_cmnd("cd", path, NOFLODIR);
//}
//
//char	*get_true_path(int argc, char **args)
//{
//	if (!ft_strcmp(args[1], " ") && argc == 3)
//		return (args[2]);
//	return (args[1]);
//}
//
//void	check_cd(int argc, char **args, int cwderr)
//{
//	char *path;
//
//	if (argc == 1 || !ft_strcmp(args[1], "--") || cwderr)
//	{
//		if (!(path = getenv_cmnd("HOME")))
//			return ;
//	}
//	else if (!ft_strcmp(args[1], "."))
//		path = getenv_cmnd("PWD");
//	else if (!ft_strcmp(args[1], "-"))
//	{
//		path = getenv_cmnd("OLDPWD");
//		ft_putstr_fd(path, STDOUT_FILENO);
//		ft_putchar_fd('\n', STDOUT_FILENO);
//	}
//	else
//		path = get_true_path(argc, args);
//	launch_cd(path);
//}
//
//void	cd_three_args(char **args, int argc)
//{
//	if (!ft_strcmp(args[1], " "))
//		check_cd(argc, args, 0);
//	else
//		perror_cmnd("cd", args[1], NOTINPWD);
//}
//
//int		cd_cmnd(char **args, int argc)
//{
//	char	dir_path[MAXDIR];
//	char	*pwd_path;
//	int		cwderr;
//
//	cwderr = 0;
//	if (argc == 3)
//		cd_three_args(args, argc);
//	else if (argc > 3)
//		perror_cmnd("cd", NULL, MNARGS);
//	else
//	{
//		if (!(getcwd(dir_path, MAXDIR)))
//		{
//			perror_cmnd("cd", args[1], GETCWDERR);
//			cwderr = 1;
//		}
//		check_cd(argc, args, cwderr);
//	}
//	if ((pwd_path = getenv_cmnd("PWD")))
//	{
//		setenv_cmnd("OLDPWD", pwd_path);
//		setenv_cmnd("PWD", dir_path);
//	}
//	return (1);
//}
