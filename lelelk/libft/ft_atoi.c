/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:48:16 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/18 17:58:24 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	nb;

	i = 0;
	nb = 0;
	sign = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10);
		nb += str[i] - '0';
		i++;
	}
	if (nb > 9223372036854775807)
		return ((sign == 1) ? -1 : 0);
	return (sign * (int)nb);
}
