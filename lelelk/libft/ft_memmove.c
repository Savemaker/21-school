/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:11:55 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/13 14:38:04 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	dst_tmp = (unsigned char*)dst;
	src_tmp = (unsigned char*)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (src_tmp > dst_tmp)
		return (ft_memcpy(dst, src, len));
	while (len-- > 0)
		dst_tmp[len] = src_tmp[len];
	return ((void *)dst_tmp);
}
