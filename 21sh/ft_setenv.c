/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:03:37 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/09 16:04:21 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	copy_index(char **ress, char *name, char *value)
{
	int		i;
	int		j;
	char	*res;

	res = *ress;
	i = 0;
	j = 0;
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
			if (test_getenv(name, envp[i]) == 1)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	copy_to_realloc(char **envp, char **res, char *name, char *value)
{
	int index;
	int i;
	int j;

	index = ft_getenv_index(name, envp);
	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		if (index != i)
		{
			while (envp[i][j] != '\0')
			{
				res[i][j] = envp[i][j];
				j++;
			}
			res[i][j] = '\0';
		}
		if (index == i)
			copy_index(&res[i], name, value);
		i++;
	}
	if (index == -1)
		copy_index(&res[i], name, value);
}

char	*malloc_line(char *name, char *value)
{
	char	*res;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	res = (char *)malloc(sizeof(char) * (name_len + value_len + 2));
	if (res == NULL)
		return (NULL);
	return (res);
}

char	**realloc_envp(int pointers, char *name, char *value, char **envp)
{
	char	**res;
	int		index;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (pointers + 1));
	index = ft_getenv_index(name, envp);
	if (index == -1)
		--pointers;
	while (i < pointers)
	{
		if (i == index)
			res[i] = malloc_line(name, value);
		else
			res[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		i++;
	}
	if (index == -1)
		res[i++] = malloc_line(name, value);
	res[i] = NULL;
	copy_to_realloc(envp, res, name, value);
	return (res);
}

int		ft_setenv(char **parse, char **envp)
{
	char	**new_env;
	int		p;

	new_env = NULL;
	p = count_pointers(parse);
	if (p == 3 && parse[1] != NULL && parse[2] != NULL)
	{
		p = count_pointers(envp);
		if (ft_getenv(parse[1], envp) == NULL)
			p++;
		new_env = realloc_envp(p, parse[1], parse[2], envp);
		free_copy_envp(&envp);
		g_my_env = new_env;
		if (ft_strcmp("PATH", parse[1]) == 0)
		{
			free_hash_table(&g_table);
			g_table = create_table();
		}
		return (1);
	}
	return (1);
}
