/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:59:38 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/27 15:44:51 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		desksize(t_list *list)
{
	int		i;
	t_tetr	*tetr;
	int		fig_count;

	i = 2;
	fig_count = 0;
	fig_count = listlen(list);
	tetr = list->content;
	if (fig_count == 1)
	{
		if (tetr->width == 4 || tetr->height == 4)
			return (4);
		if (tetr->width == 3 || tetr->height == 3)
			return (3);
		if (tetr->width == 2 || tetr->height == 2)
			return (2);
	}
	while (i * i < fig_count * 4)
		i++;
	return (i);
}

void	default_tet(char **board, t_list *list, int size)
{
	int		i;
	int		j;
	t_tetr	*tetr;

	tetr = list->content;
	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (board[i][j] == tetr->letter)
				board[i][j] = '.';
			j++;
		}
		i++;
	}
}

int		boardchecker(char **board, int size, t_tetr *t, int pos)
{
	int i;

	i = pos / size;
	t->c = 0;
	t->y = 0;
	while (i < size && t->y < t->height)
	{
		t->j = pos % size;
		while (t->j < size && t->x < t->width)
		{
			if (board[i][t->j] == '.' && t->shape[t->y][t->x] == t->letter)
				t->c += 1;
			t->j++;
			t->x++;
			if (t->x > t->width && t->c == 4)
				return (0);
			if (t->x > t->width && t->c != 4)
				return (1);
		}
		i++;
		t->y++;
		t->x = 0;
	}
	t->c = t->c == 4 ? 0 : 1;
	return (t->c);
}

int		addtoboard(char **board, int size, t_tetr *tetr, int pos)
{
	int y;

	y = 0;
	tetr->i = pos / size;
	if (!(boardchecker(board, size, tetr, pos)))
	{
		while (tetr->i < size && y < tetr->height)
		{
			tetr->j = pos % size;
			while (tetr->j < size && tetr->x < tetr->width)
			{
				if (tetr->shape[y][tetr->x] == tetr->letter)
					board[tetr->i][tetr->j] = tetr->shape[y][tetr->x];
				tetr->j++;
				tetr->x++;
				if (tetr->x > tetr->width)
					return (1);
			}
			tetr->i++;
			y++;
			tetr->x = 0;
		}
		return (0);
	}
	return (1);
}

void	emptyboard(char **board, int size)
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
			board[i][j] = '.';
			j++;
		}
		i++;
	}
}
