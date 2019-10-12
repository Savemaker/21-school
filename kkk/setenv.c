/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:29:44 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/07 21:30:59 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_value(char **ress, char *name, char *value)
{
	int		i;
	int		j;
	char	*res;

	res = *ress;
	i = 0;
	while (name[i])
	{
		res[i] = name[i];
		i++;
	}
	res[i++] = '=';
	j = 0;
	while (value[j])
	{
		res[i] = value[j];
		i++;
		j++;
	}
	res[i] = '\0';
}

void	copy_to_realloc(char **envp, char **res, char *name, char *value)
{
	int index;
	int i;
	int j;

	index = get_envindex(name);
	i = 0;
	while (envp[i])
	{
		j = -1;
		if (index != i)
		{
			while (envp[i][++j] != '\0')
				res[i][j] = envp[i][j];
			res[i][j] = '\0';
		}
		if (index == i)
			join_value(&res[i], name, value);
		i++;
	}
	if (index == -1)
		join_value(&res[i], name, value);
}

char	**get_new_envp(int pointers, char *name, char *value, int index)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (pointers + 1));
	while (i < pointers)
	{
		if (i == index)
			res[i] = malloc_line(name, value);
		else
		{
			if (!(res[i] = (char *)malloc(sizeof(char) *
				(ft_strlen(g_shell->env[i]) + 1))))
				perror_cmnd("setenv", NULL, MLKERR);
		}
		i++;
	}
	if (index == -1)
		res[i++] = malloc_line(name, value);
	res[i] = NULL;
	return (res);
}

char	**realloc_envp(int pointers, char *name, char *value, char **env)
{
	char	**res;
	int		index;

	if ((index = get_envindex(name)) == -1)
		--pointers;
	res = get_new_envp(pointers, name, value, index);
	copy_to_realloc(env, res, name, value);
	return (res);
}

int		setenv_cmnd(char *name, char *value)
{
	char	**new_env;
	int		p;

	if (!name || !value)
	{
		ft_putstr("usage: setenv [name] [value]\n");
		return (1);
	}
	else
	{
		p = str_quantity(g_shell->env);
		if (getenv_cmnd(name) == NULL)
			p++;
		new_env = realloc_envp(p, name, value, g_shell->env);
		clean_env(g_shell->env);
		g_shell->env = new_env;
	}
	return (1);
}
