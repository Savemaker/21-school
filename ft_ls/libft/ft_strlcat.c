/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:39:01 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/04 15:25:08 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t original;
	size_t len_final;

	original = ft_strlen(src) + size;
	len_final = 0;
	while (*dst && size > 0)
	{
		dst++;
		size--;
		len_final++;
	}
	if (size < 1)
		return (original);
	while (*src && --size > 0)
	{
		*dst++ = *src++;
		len_final++;
	}
	while (*src++)
		len_final++;
	*dst = '\0';
	return (len_final);
}
