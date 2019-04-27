/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:30:54 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/27 16:24:23 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int			main(int argc, char **argv)
{
	int		fd;
	t_list	*list;
	int		e;

	e = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		list = reading(fd);
		e = solver(list);
		deletelist(&list);
	}
	else
		write(1, "usage: ./fillit source_file\n", 28);
	return (0);
}

int			solver(t_list *list)
{
	char	**desk;
	int		size;
	int		i;

	i = 0;
	size = desksize(list);
	desk = createboard(size);
	while (!(fillit(list, desk, size, 0)))
	{
		emptyboard(desk, size);
		freeboard(desk, size);
		size += 1;
		if (!(desk = createboard(size)))
			return (0);
		restorepos(list);
	}
	printdesk(desk, size);
	freeboard(desk, size);
	return (1);
}

int			adding(char **board, int size, t_list *list)
{
	int		a;
	t_tetr	*tetr;

	tetr = list->content;
	a = 0;
	a = boardchecker(board, size, tetr, list->pos);
	if (a == 0)
		return (0);
	if (a == 1)
	{
		while (boardchecker(board, size, tetr, list->pos) == 1)
		{
			list->pos += 1;
			if (list->pos == size * size - 1)
				return (1);
		}
	}
	return (0);
}

size_t		factorial(size_t n)
{
	if (n == 0)
		return (1);
	return (n * factorial(n - 1));
}

void		restorepos(t_list *list)
{
	while (list != NULL)
	{
		list->pos = 0;
		list = list->next;
	}
}
