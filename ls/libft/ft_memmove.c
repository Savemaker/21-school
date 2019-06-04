/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:58:57 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/03 18:11:33 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *dest;
	char *source;
	char *final;

	dest = (char *)dst;
	source = (char *)src;
	final = dest;
	if (dest > source)
	{
		source = source + len - 1;
		dest = dest + len - 1;
		while (len-- > 0)
			*dest-- = *source--;
	}
	else
	{
		while (len-- > 0)
			*dest++ = *source++;
	}
	return (final);
}
