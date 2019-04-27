/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:36:48 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/24 17:38:13 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

char	**createboard(int s)
{
	int		i;
	int		j;
	char	**board;

	i = 0;
	j = 0;
	if (!(board = (char **)malloc(sizeof(char *) * s)))
		return (NULL);
	while (i < s)
	{
		board[i] = (char *)malloc(sizeof(char) * s + 1);
		i++;
	}
	i = 0;
	while (i < s)
	{
		j = 0;
		while (j < s)
		{
			board[i][j++] = '.';
		}
		board[i][j] = '\0';
		i++;
	}
	return (board);
}

void	freeboard(char **board, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(board[i]);
		i++;
	}
	free(board);
}
