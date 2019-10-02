/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:01:35 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/03 18:26:57 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int len;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack && *haystack != '=')
	{
		len = 0;
		while (*haystack == *needle)
		{
			haystack++;
			needle++;
			len++;
			if (!*needle)
				return ((char *)(haystack - len));
		}
		haystack = haystack - len;
		needle = needle - len;
		haystack++;
	}
	return (NULL);
}
