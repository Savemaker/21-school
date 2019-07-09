/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:54:44 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/13 16:08:42 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*stepa;

	if (size > 65535)
		return (NULL);
	if (!(stepa = (void *)malloc(sizeof(size))))
		return (NULL);
	ft_bzero(stepa, size);
	return (stepa);
}
