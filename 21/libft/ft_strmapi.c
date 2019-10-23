/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:17:06 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/11/30 14:18:47 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	unsigned int	j;
	int				len;
	char			*newstr;

	i = 0;
	j = 0;
	if (!(s && f))
		return (NULL);
	len = ft_strlen(s);
	if (!(newstr = (char *)malloc(sizeof(*newstr) * len + 1)))
		return (NULL);
	while (i < len)
	{
		newstr[i] = f(j, s[j]);
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}
