/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:24:01 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/17 15:26:32 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s;
	char *new;

	size++;
	s = (char *)malloc(sizeof(char) * size);
	if (!s)
		return (NULL);
	new = s;
	while (size--)
		*s++ = 0;
	return (new);
}
