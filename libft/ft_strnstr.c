/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:54:15 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/14 18:56:38 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hayst, const char *need, size_t len)
{
	const char	*lim;
	int			l;

	lim = hayst + len;
	if (!*need)
		return ((char *)hayst);
	while (*hayst && hayst < lim)
	{
		l = 0;
		while (*hayst == *need && hayst < lim)
		{
			hayst++;
			need++;
			l++;
			if (!*need)
				return ((char *)hayst - l);
		}
		hayst = hayst - l;
		need = need - l;
		hayst++;
	}
	return (NULL);
}
