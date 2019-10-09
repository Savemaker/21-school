/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:36:00 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/14 12:52:32 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*newsub;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(newsub = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		newsub[i] = (char)s[start + i];
		i++;
	}
	newsub[i] = '\0';
	return (newsub);
}
