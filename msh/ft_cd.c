/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 16:23:10 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/05 17:44:54 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**update_pwd(char **envp, char *name, char *oldpath)
{
	char **parse;
	char **old;

	old = (char **)malloc(sizeof(char *) * 4);
	old[0] = ft_strdup("setenv");
	old[1] = ft_strdup("OLDPWD");
	old[2] = ft_strdup(oldpath);
	old[3] = NULL;
	parse = (char **)malloc(sizeof(char *) * 4);
	parse[0] = ft_strdup("setenv");
	parse[1] = ft_strdup("PWD");
	parse[2] = ft_strdup(name);
	parse[3] = NULL;
	envp = ft_setenv(old, envp);
	envp = ft_setenv(parse, envp);
	free_parse(parse, 3);
	free_parse(old, 3);
	return (envp);
}

void	print_no_such(char *s)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(s);
}

char	**ft_cd_stuf(char **parse, char **envp)
{
	int		res;
	char	*tmp;
	char	buf[2048];
	char	old_buf[2048];

	tmp = getcwd(old_buf, 2048);
	if (ft_strcmp(parse[1], " ") == 0)
		res = chdir(ft_getenv("HOME", envp));
	else if (ft_strcmp(parse[1], "-") == 0)
		res = chdir(ft_getenv("OLDPWD", envp));
	else
		res = chdir(parse[1]);
	if (res == -1)
	{
		if (access(parse[1], F_OK) == 0)
		{
			ft_putstr("cd: permission denied: ");
			ft_putendl(parse[1]);
		}
		else
			print_no_such(parse[1]);
	}
	if (res == 0)
		envp = update_pwd(envp, getcwd(buf, 2048), tmp);
	return (envp);
}

char	**ft_cd(char **parse, char **envp)
{
	int		i;
	char	*home;
	char	tmp[2048];

	home = ft_getenv("HOME", envp);
	i = 0;
	while (parse[i])
		i++;
	if (i > 2)
	{
		ft_putendl("cd: too many arguments");
		return (envp);
	}
	if (--i == 0)
	{
		if (home != NULL)
		{
			getcwd(tmp, 2048);
			if (chdir(home) == 0)
				envp = update_pwd(envp, home, tmp);
		}
	}
	if (i == 1)
		envp = ft_cd_stuf(parse, envp);
	return (envp);
}

char	*sub_line_stuf(char *parse)
{
	char *res;

	if (ft_strlen(parse) == 1)
		res = ft_strdup("$");
	else
		res = ft_strdup(" ");
	return (res);
}
