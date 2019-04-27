/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:48:41 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/27 16:13:15 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

int		height(char **shape, char a)
{
	int i;
	int j;
	int h;

	i = 0;
	h = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
			{
				h++;
				j++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (h);
}

int		width(char **shape, char a)
{
	int i;
	int j;
	int c;
	int t;

	t = 0;
	c = 0;
	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (shape[i][j] == a)
				c = j + 1;
			j++;
		}
		if (c >= t)
			t = c;
		i++;
	}
	return (t);
}

void	val(t_tetr *tetr)
{
	int t;
	int q;

	t = 0;
	q = 0;
	t = touch(tetr->shape, tetr->letter);
	q = quantity(tetr->shape, tetr->letter);
	if (q == 4 && t == 8)
	{
		if (tetr->height != 2 && tetr->height != 2)
			stop();
	}
	else if (q == 4 && t != 6)
		stop();
}

void	trim(char **bufnew, char *buf, char a)
{
	char	*new;
	int		i;
	int		j;
	int		c;

	j = 0;
	i = 0;
	c = 0;
	new = *bufnew;
	while (j < 16)
	{
		if (buf[c] == '#')
		{
			new[i++] = a;
			j++;
		}
		else if (buf[c] == '.')
		{
			new[i++] = '.';
			j++;
		}
		c++;
	}
	new[i] = '\0';
}
