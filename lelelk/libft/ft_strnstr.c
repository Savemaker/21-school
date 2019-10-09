/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:48:45 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/13 17:15:51 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *nee, size_t len)
{
	size_t little_len;

	if (*nee == '\0')
		return ((char *)hay);
	little_len = ft_strlen(nee);
	while (*hay != '\0' && little_len <= len--)
	{
		if (*hay == *nee &&
			ft_strncmp(hay, nee, little_len) == 0)
			return ((char *)hay);
		hay++;
	}
	return (NULL);
}
