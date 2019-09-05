/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:45:19 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/05 18:07:45 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_names(char **names)
{
	int i;

	i = 0;
	while (i < 10)
	{
		free(names[i]);
		i++;
	}
	free(names);
}

char	**setup_names(void)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * 10);
	res[i++] = ft_strdup("emacs");
	res[i++] = ft_strdup("echo");
	res[i++] = ft_strdup("env");
	res[i++] = ft_strdup("setenv");
	res[i++] = ft_strdup("unsetenv");
	res[i++] = ft_strdup("exit");
	res[i++] = ft_strdup("cd");
	res[i++] = ft_strdup("pwd");
	res[i++] = ft_strdup("ls");
	res[i] = (char *)NULL;
	return (res);
}

char	*name_gen(const char *text, int state)
{
	static int	list;
	static int	len;
	char		*name;
	char		**char_names;
	char		*res;

	char_names = setup_names();
	if (!state)
	{
		list = 0;
		len = ft_strlen(text);
	}
	while ((name = char_names[list++]))
	{
		if (ft_strncmp(name, text, len) == 0)
		{
			res = ft_strdup(name);
			free_names(char_names);
			return (res);
		}
	}
	free_names(char_names);
	return (NULL);
}

char	**name_compl(const char *text, int start, int end)
{
	(void)end;
	(void)start;
	rl_attempted_completion_over = 1;
	return (rl_completion_matches(text, name_gen));
}
