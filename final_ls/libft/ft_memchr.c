/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 18:58:10 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/04 14:36:44 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char			to_find;
	const unsigned char		*cs;

	to_find = (unsigned char)c;
	cs = (const unsigned char*)s;
	while (n-- > 0)
	{
		if (*cs++ == to_find)
			return ((void*)(cs - 1));
	}
	return (NULL);
}
