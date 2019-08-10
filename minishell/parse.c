/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:10:01 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 15:10:43 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_words(char *cmd)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ')
			i++;
		if (cmd[i] != '\0')
			w++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i] != ' ')
			i++;
	}
	return (w);
}

int		*create_tab(int words)
{
	int *res;
	int i;

	i = 0;
	words++;
	res = (int *)malloc(sizeof(int) * words);
	while (i < words)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

int		*count_each_word(char *cmd, int words)
{
	int i;
	int len;
	int *tab;
	int j;

	i = 0;
	j = 0;
	len = 0;
	tab = create_tab(words);
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ')
			i++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i] != ' ')
		{
			tab[j]++;
			i++;
		}
		j++;
	}
	return (tab);
}

void	copy_split(char **res, char *cmd)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ')
			i++;
		k = 0;
		if (cmd[i] == '\0')
			break ;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i] != ' ')
			res[j][k++] = cmd[i++];
		res[j][k] = '\0';
		j++;
	}
}

char	**ft_full_split(char *cmd, int words)
{
	char	**res;
	int		*tab;
	int		i;

	i = 0;
	tab = count_each_word(cmd, words);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	while (i < words)
	{
		res[i] = (char *)malloc(sizeof(char) * tab[i] + 1);
		i++;
	}
	free(tab);
	res[i] = NULL;
	copy_split(res, cmd);
	return (res);
}
