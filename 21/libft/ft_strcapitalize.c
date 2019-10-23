/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 14:52:21 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/17 15:47:51 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *s)
{
	int	i;
	int up;

	i = 0;
	up = 1;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 1 || ft_isalpha(s[i]) == 1)
		{
			if (up && (s[i] >= 'a' && s[i] <= 'z'))
				s[i] = s[i] - 32;
			else if (!up && (s[i] >= 'A' && s[i] <= 'Z'))
				s[i] = s[i] + 32;
			up = 0;
		}
		else
			up = 1;
		i++;
	}
	return (s);
}
