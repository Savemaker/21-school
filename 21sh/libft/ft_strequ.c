/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:18:35 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/13 18:33:57 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int i;
	int j;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (i == j)
	{
		i = 0;
		while (s1[i] != '\0')
		{
			if (s1[i] == s2[i])
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}
