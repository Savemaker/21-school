/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 15:13:47 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/08/10 15:14:02 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_split_delim(char **res, char *cmd, char delim)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		k = 0;
		if (cmd[i] == '\0')
			break ;
		while (cmd[i] != '\0' && cmd[i] != delim)
			res[j][k++] = cmd[i++];
		res[j][k] = '\0';
		j++;
	}
}

int		*count_each_word_delim(char *cmd, int words, char delim)
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
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		while (cmd[i] != '\0' && cmd[i] != delim)
		{
			tab[j]++;
			i++;
		}
		j++;
	}
	return (tab);
}

char	**ft_split_delim(char *cmd, int words, char delim)
{
	char	**res;
	int		*tab;
	int		i;

	i = 0;
	tab = count_each_word_delim(cmd, words, delim);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	while (i < words)
	{
		res[i] = (char *)malloc(sizeof(char) * tab[i] + 1);
		i++;
	}
	free(tab);
	res[i] = NULL;
	copy_split_delim(res, cmd, delim);
	return (res);
}

int		count_words_delim(char *cmd, char delim)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		if (cmd[i] != '\0')
			w++;
		while (cmd[i] != '\0' && cmd[i] != delim)
			i++;
	}
	return (w);
}
