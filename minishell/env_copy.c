/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:37:03 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 16:13:00 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parse(char **parse, int w)
{
	int i;

	i = 0;
	w++;
	while (i < w)
	{
		free(parse[i]);
		i++;
	}
	free(parse);
}

int		count_pointers(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	*sub_line(char *parse, char **envp)
{
	char *seek;
	char *res;

	if (parse[0] == '$')
	{
		seek = ft_getenv(&parse[1], envp);
		if (seek == NULL)
			res = NULL;
		else
			res = ft_strdup(seek);
	}
	else if (parse[0] == '~')
	{
		seek = ft_getenv("HOME", envp);
		if (seek == NULL)
			res = NULL;
		else
			res = ft_strdup(seek);
	}
	else
		res = ft_strdup(parse);
	return (res);
}

char	**sub_parse(char **parse, char **envp)
{
	int		p;
	int		i;
	char	**res;

	i = 0;
	p = count_pointers(parse);
	res = (char **)malloc(sizeof(char *) * (p + 1));
	while (i < p)
	{
		res[i] = sub_line(parse[i], envp);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**edit_parse(char **parse, char **envp)
{
	char **res;

	if (test_exp(parse) == 0)
		return (parse);
	else
	{
		res = sub_parse(parse, envp);
		free_parse(parse, count_pointers(parse));
		return (res);
	}
}
