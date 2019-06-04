/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:30:36 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/04 14:31:34 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *d;
	const unsigned char *f;

	d = (unsigned char*)s1;
	f = (unsigned char*)s2;
	while (n-- > 0)
	{
		if (*d != *f)
			return ((unsigned char)*d - (unsigned char)*f);
		d++;
		f++;
	}
	return (0);
}
