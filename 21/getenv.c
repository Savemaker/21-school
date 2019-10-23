/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:13:53 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/07 21:16:11 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_existenv(const char *name, char *request)
{
	size_t len;

	len = 0;
	while (request[len] && request[len] != '=')
		len++;
	if (ft_strlen(name) != len)
		return (0);

	return (1);
}

int		get_envindex(const char *name)
{
	int		i;
	char	*request;

	i = 0;
	while (g_shell->env[i])
	{
		if ((request = ft_strstr(g_shell->env[i], name)))
			if ((check_existenv(name, request)))
				return (i);
		i++;
	}
	return (-1);
}

int		checkenv(char *envstr)
{
	if (!(ft_strchr(envstr, '=')))
	{
		perror_cmnd(SHELLNAME, NULL, SETENVERR);
		return (0);
	}
	return (1);
}

int		getenv_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*getenv_cmnd(char *name)
{
	int		i;
	char	*request;

	i = 0;
	while (g_shell->env[i])
	{
		if ((checkenv(g_shell->env[i])))
			if ((request = ft_strnstr(g_shell->env[i], name, getenv_strlen(name))))
				if ((check_existenv(name, request)))
					return (request + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}
