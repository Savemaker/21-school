/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slavastrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:38:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/06 17:33:06 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char		*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * n + 1);
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

char		*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if ((str = (char *)malloc(sizeof(const char) * ft_strlen(s1) + 1)))
		str[ft_strlen(s1)] = '\0';
	else
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}

char		*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

int			ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void		freeshape(char **shape)
{
	int i;

	i = 0;
	while (i < 5)
		free(shape[i++]);
	free(shape);
}
