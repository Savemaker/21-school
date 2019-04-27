/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:07:00 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/27 16:08:35 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		fillit(t_list *list, char **desk, int size, int a)
{
	while (list->pos < size * size)
	{
		a = adding(desk, size, list);
		if (a == 1)
			return (0);
		else
		{
			a = addtoboard(desk, size, list->content, list->pos);
			if (list->next != NULL)
			{
				a = fillit(list->next, desk, size, 0);
				if (a == 0)
				{
					default_tet(desk, list, size);
					list->pos += 1;
					list->next->pos = 0;
				}
				else
					return (1);
			}
			else
				return (1);
		}
	}
	return (0);
}

int		count(char **shape, int *y, int *x, char a)
{
	int t;

	t = 0;
	if (shape[*y][*x] == a)
	{
		if (*y == 3)
		{
			if ((shape[*y - 1][*x] == a) || (shape[*y][*x + 1] == a))
				t += 1;
			if (*x > 0 && shape[*y][*x - 1] == a)
				t += 1;
		}
		else
		{
			if (shape[*y][*x + 1] == a)
				t += 1;
			if (*x > 0 && shape[*y][*x - 1] == a)
				t += 1;
			if (*y > 0 && shape[*y - 1][*x] == a)
				t += 1;
			if (shape[*y + 1][*x] == a)
				t += 1;
		}
	}
	return (t);
}

int		touch(char **shape, char a)
{
	int i;
	int j;
	int t;
	int y;

	y = 0;
	i = 0;
	j = 0;
	t = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			y = count(shape, &i, &j, a);
			t = y + t;
			j++;
		}
		i++;
	}
	return (t);
}
