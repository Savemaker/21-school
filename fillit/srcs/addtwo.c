/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addtwo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:09:16 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/27 16:23:31 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

void		moveleft(char **shape, char a)
{
	int		i;
	int		j;
	int		move;
	char	temp;

	i = 0;
	j = 0;
	move = 0;
	move = needtomove(shape, a, 0, 0);
	if (move == 0)
		return ;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
			{
				shape[i][j - move] = shape[i][j];
				shape[i][j] = '.';
			}
			j++;
		}
		i++;
	}
}

int			needtomove(char **shape, char a, int i, int j)
{
	int n;
	int space;

	i = 0;
	j = 0;
	n = 0;
	space = 0;
	while (j < 4)
	{
		i = 0;
		n = 0;
		while (i < 4)
		{
			if (shape[i][j] == '.')
				n++;
			else if (shape[i][j] == a)
				return (space);
			i++;
		}
		if (n == 4)
			++space;
		j++;
	}
	return (space);
}

void		default_line(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		line[i] = '.';
		i++;
	}
}

void		printdesk(char **desk, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			write(1, &desk[i][j++], 1);
		}
		i++;
		write(1, "\n", 1);
	}
}
