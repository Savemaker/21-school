/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:35:35 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/11/30 14:36:21 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int i;
	int len;

	i = 0;
	len = 0;
	if (s && f)
	{
		len = ft_strlen(s);
		while (i < len)
		{
			(*f)(i, s);
			i++;
			s++;
		}
	}
}
