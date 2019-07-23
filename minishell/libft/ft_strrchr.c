/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:11:12 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/04 17:00:16 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *dubl;
	char q;

	dubl = (char *)s;
	q = (char)c;
	while (*dubl != '\0')
		dubl++;
	if (q == '\0')
		return ((char *)dubl);
	while (*dubl != *s && *dubl != q)
		dubl--;
	if (*dubl == q)
		return ((char *)dubl);
	return (NULL);
}
