/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:44:26 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/10 15:02:40 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mainstr;
	size_t	len;
	char	*str1;
	char	*str2;

	str1 = (char*)s1;
	str2 = (char *)s2;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	mainstr = ft_strnew(len);
	if (!mainstr)
		return (NULL);
	ft_strcpy(mainstr, str1);
	ft_strcat(mainstr, str2);
	return (mainstr);
}
