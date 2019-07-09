/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:12:40 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/03 18:14:56 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char	*dest;
	char	*source;
	char	ch;

	source = (char *)src;
	dest = (char *)dst;
	ch = (char)c;
	while (n-- > 0)
	{
		if ((*dest++ = *source++) == ch)
			return ((void *)dest);
	}
	return (0);
}
