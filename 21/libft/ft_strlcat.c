/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:35:08 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/14 18:27:12 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t orig;
	size_t res;

	orig = ft_strlen(src) + size;
	res = 0;
	while (*dst && size > 0)
	{
		dst++;
		res++;
		size--;
	}
	if (size <= ft_strlen(dst))
		return (orig);
	while (*src && --size > 0)
	{
		*dst++ = *src++;
		res++;
	}
	while (*src++)
		res++;
	*dst = '\0';
	return (res);
}
