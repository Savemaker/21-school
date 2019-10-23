/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:00:03 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/11/30 18:57:26 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;
	size_t			i;

	i = 0;
	dst_tmp = (unsigned char*)dst;
	src_tmp = (unsigned char*)src;
	while (n--)
	{
		if (src_tmp[i] == (unsigned char)c)
		{
			dst_tmp[i] = src_tmp[i];
			i++;
			return ((void *)dst_tmp + i);
		}
		dst_tmp[i] = src_tmp[i];
		i++;
	}
	return (NULL);
}
