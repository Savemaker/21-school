/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:53:15 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/11/30 13:56:25 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	int		j;
	int		len;
	char	*newstr;

	i = 0;
	j = 0;
	if (!(s && f))
		return (NULL);
	len = ft_strlen(s);
	if (!(newstr = (char *)malloc(sizeof(*newstr) * len + 1)))
		return (NULL);
	while (i < len)
	{
		newstr[i] = f(s[j]);
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}
