/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:35:20 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/07 21:36:45 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"











char	*malloc_line(char *name, char *value)
{
	char	*res;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	if (!(res = (char *)malloc(sizeof(char) * (name_len + value_len + 2))))
	{
		perror_cmnd("setenv", NULL, MLKERR);
		return (NULL);
	}
	return (res);
}

void	copy_realloc_del(char **res, char **env, int index)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (env[i])
	{
		if (i == index)
		{
			i++;
			continue;
		}
		j = 0;
		while (env[i][j])
		{
			res[k][j] = env[i][j];
			j++;
		}
		res[k][j] = '\0';
		k++;
		i++;
	}
}

char	**realloc_envp_del(int p, char *name, char **env)
{
	int		i;
	int		j;
	char	**res;
	int		index;

	index = get_envindex(name);
	i = 0;
	j = 0;
	if (!(res = (char**)malloc(sizeof(char *) * p + 1)))
		perror_cmnd("unsetenv", NULL, MLKERR);
	while (i < p)
	{
		if (index == j)
			j++;
		if (!(res[i] = (char *)malloc(sizeof(char) * (ft_strlen(env[j]) + 1))))
			perror_cmnd("unsetenv", NULL, MLKERR);
		j++;
		i++;
	}
	res[p] = NULL;
	copy_realloc_del(res, env, index);
	return (res);
}

int		unsetenv_cmnd(char *name)
{
	char	**new_env;

	if (!name)
	{
		ft_putstr("usage: unsetenv [name]\n");
		return (1);
	}
	if (getenv_cmnd(name) != NULL)
	{
		new_env = realloc_envp_del(str_quantity(g_shell->env) - 1, name, g_shell->env);
		free_copy_envp(&g_shell->env);
		g_shell->env = new_env;
	}
	return (1);
}
