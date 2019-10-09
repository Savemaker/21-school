/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:59:09 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/11/30 12:59:35 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *dst;

	dst = (void *)malloc(sizeof(*dst) * size);
	if (!dst)
		return (NULL);
	ft_bzero(dst, size);
	return (dst);
}
