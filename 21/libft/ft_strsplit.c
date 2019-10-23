/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:52:52 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/14 17:35:05 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_mem(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
}

static int	ft_count_words(char *str, char sign)
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

static char	*ft_split(char **full_s, const char *first_s, char c, int *i)
{
	char	*one_s;
	int		j;

	if (!(one_s = (char *)malloc(sizeof(one_s) * (ft_strlen(first_s)))))
	{
		free_mem(full_s, *i);
		return (NULL);
	}
	j = 0;
	while (first_s[*i] != c && first_s[*i])
	{
		one_s[j] = first_s[*i];
		j++;
		*i += 1;
	}
	one_s[j] = '\0';
	while (first_s[*i] == c && first_s[*i])
		*i += 1;
	return (one_s);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		str_num;
	int		count;
	char	**str;

	i = 0;
	str_num = 0;
	if (!s)
		return (NULL);
	count = ft_count_words((char *)s, c);
	if (!(str = (char **)malloc(sizeof(str) * (count + 1))))
		return (NULL);
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && str_num < count)
	{
		str[str_num] = ft_split(str, (char*)s, c, &i);
		if (str[str_num++] == NULL)
		{
			free(str);
			return (NULL);
		}
	}
	str[str_num] = NULL;
	return (str);
}
