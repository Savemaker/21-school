/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:19:48 by gbeqqo            #+#    #+#             */
/*   Updated: 2018/12/16 17:30:42 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int					flag;
	unsigned long long	res;
	int					i;

	i = 0;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	flag = (*str == '-') ? -1 : 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str == '0')
		str++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res > 9223372036854775807)
		return ((flag == 1) ? -1 : 0);
	return (flag * (int)res);
}
