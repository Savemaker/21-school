/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:44:34 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/08 13:45:29 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

char	*nsplit(char *s, int start, int i, char *sub)
{
	char *val;
	char *dupsub;
	char *str;

	if (s[start] == '~')
		return (ft_strjoin(getenv_cmnd("HOME"), &s[start] + 1));
	else if (s[start] == '$' && env_strlen(&s[start]) == 1)
		return (ft_strdup("$"));
	else if (s[start] == '$' && (val = getenv_cmnd(sub)))
		return (ft_strdup(val));
	else if (s[start] == '$' && !val)
		return (ft_strdup(" "));
	else
	{
		dupsub = ft_strsub(s, start, i - start);
		str = ft_strdup(dupsub);
		free(dupsub);
	}
	return (str);
}

char	**split(char **str, char *s, char c, int count)
{
	int		i;
	int		start;
	int		n_mas;
	char	*sub;

	i = 0;
	n_mas = 0;
	while (s[i] != '\0' && n_mas < count)
	{
		if (s[i] != c && s[i] != '\t' && s[i] != '\r' &&
		s[i] != '\v' && s[i] != '"')
		{
			start = i;
			while (s[i] != '\0' && s[i] != c)
				i++;
			sub = ft_strsub(s, start + 1, env_strlen(&s[start + 1]));
			str[n_mas] = nsplit(s, start, i, sub);
			free(sub);
			n_mas++;
		}
		else
			i++;
	}
	str[n_mas] = NULL;
	return (str);
}

int		count_words(char *str, char sign)
{
	int i;
	int i_of_word;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		i_of_word = 0;
		while (str[i] != sign && str[i] != '\0')
		{
			i_of_word++;
			i++;
		}
		if (i_of_word != 0)
			count++;
		i++;
	}
	return (count);
}

char	**split_cmnd(char const *s, char c)
{
	char **str;
	char count;

	if (s)
	{
		count = count_words((char *)s, c);
		if (!(str = (char **)malloc(sizeof(char *) * (count + 1))))
			return (NULL);
		str = split(str, (char *)s, c, count);
		return (str);
	}
	return (NULL);
}
