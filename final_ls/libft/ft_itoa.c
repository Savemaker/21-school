/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:16:44 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/07/19 11:57:46 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_itoa(int n)
// {
// 	char *str;

// 	if (n == -2147483648)
// 		return (ft_strdup("-2147483648"));
// 	if (!(str = (char *)malloc(sizeof(char) * 2)))
// 		return (NULL);
// 	if (n < 0)
// 	{
// 		str[0] = '-';
// 		str[1] = '\0';
// 		str = ft_strjoin(str, ft_itoa(-n));
// 	}
// 	else if (n >= 10)
// 		str = ft_strjoin(ft_itoa(n / 10), ft_itoa(n % 10));
// 	else if (n < 10 && n >= 0)
// 	{
// 		str[0] = n + '0';
// 		str[1] = '\0';
// 	}
// 	return (str);
// }


static int		get_nb_size(unsigned int nb)
{
	unsigned int	size;

	size = 0;
	while (nb >= 10)
	{
		nb /= 10;
		++size;
	}
	return (size + 1);
}

char			*ft_itoa(int nbr)
{
	char			*str;
	unsigned int	nb;
	unsigned int	index;
	unsigned int	size;

	if (nbr < 0)
		nb = (unsigned int)(nbr * -1);
	else
		nb = (unsigned int)nbr;
	size = (unsigned int)get_nb_size(nb);
	index = 0;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1 + (nbr < 0 ? 1 : 0)))))
		return (0);
	if (nbr < 0 && (str[index] = '-'))
		size++;
	index = size - 1;
	while (nb >= 10)
	{
		str[index--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	str[index] = (char)(nb % 10 + 48);
	str[size] = '\0';
	return (str);
}