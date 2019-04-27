/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addone.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:10:03 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/27 16:11:50 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		checkmoveup(char **shape, char a, int i, int j)
{
	int f;
	int space;

	space = 0;
	f = 0;
	while (i < 4)
	{
		j = 0;
		f = 0;
		while (j < 4)
		{
			if (shape[i][j] == '.')
				f++;
			else if (shape[i][j] == a)
				return (space);
			j++;
		}
		if (f == 4)
			++space;
		i++;
	}
	return (space);
}

void	stop(void)
{
	write(1, "error\n", 6);
	exit(0);
}

int		quantity(char **shape, char a)
{
	int i;
	int	j;
	int c;

	i = 0;
	j = 0;
	c = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

void	moveup(char **shape, char a, int h)
{
	int s;

	s = checkmoveup(shape, a, 0, 0);
	if (s == 3)
	{
		ft_memcpy(shape[0], shape[3], 4);
		default_line(shape[3]);
	}
	else if (s == 2)
	{
		ft_memcpy(shape[0], shape[2], 4);
		ft_memcpy(shape[1], shape[3], 4);
		default_line(shape[2]);
		default_line(shape[3]);
	}
	else if (s == 1)
	{
		ass(shape, h);
	}
}

void	ass(char **shape, int h)
{
	if (h == 1)
	{
		ft_memcpy(shape[0], shape[1], 4);
		default_line(shape[1]);
	}
	else if (h == 2)
	{
		ft_memcpy(shape[0], shape[1], 4);
		default_line(shape[1]);
		ft_memcpy(shape[1], shape[2], 4);
		default_line(shape[2]);
	}
	else if (h == 3)
	{
		ft_memcpy(shape[0], shape[1], 4);
		default_line(shape[1]);
		ft_memcpy(shape[1], shape[2], 4);
		default_line(shape[2]);
		ft_memcpy(shape[2], shape[3], 4);
		default_line(shape[3]);
	}
}
