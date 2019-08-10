/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:34:38 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 15:41:48 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_getenv_index(const char *name, char **envp)
{
	int		i;
	char	*ret;
	int		len;

	i = 0;
	len = ft_strlen(name) + 1;
	while (envp[i])
	{
		ret = ft_strstr(envp[i], name);
		if (ret != NULL)
		{
			if (test_getenv(name, ret) == 1)
				return (i);
		}
		i++;
	}
	return (-1);
}

int		test_getenv(const char *name, char *ret)
{
	size_t i;

	i = 0;
	while (ret[i] && ret[i] != '=')
		i++;
	if (ft_strlen(name) != i)
		return (0);
	return (1);
}

char	*ft_getenv(const char *name, char **envp)
{
	int		i;
	char	*ret;
	int		len;

	i = 0;
	len = ft_strlen(name) + 1;
	while (envp[i])
	{
		ret = ft_strstr(envp[i], name);
		if (ret != NULL)
		{
			if (test_getenv(name, ret) == 1)
				return (ret + len);
		}
		i++;
	}
	return (NULL);
}

void	copy_env_to(char **envp, char **copy)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '\0')
		{
			copy[i][j] = envp[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
}

char	**create_env_copy(char **envp, int c)
{
	char	**copy;
	int		i;

	i = 0;
	copy = (char **)malloc(sizeof(char *) * (c + 1));
	while (i < c)
	{
		copy[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		i++;
	}
	copy[i] = NULL;
	copy_env_to(envp, copy);
	return (copy);
}
