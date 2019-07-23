/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:43:12 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/11 20:21:09 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char	const *s, unsigned int start, size_t len)
{
	char	*new;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(*s))
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (len-- > 0)
	{
		new[i] = s[start];
		i++;
		start++;
	}
	new[i] = '\0';
	return (new);
}
