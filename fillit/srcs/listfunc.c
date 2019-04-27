/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:03:43 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/27 16:12:39 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content = malloc(content_size);
		if (new->content == NULL)
			return (NULL);
		ft_memmove(new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}

int			listlen(t_list *list)
{
	int n;

	n = 0;
	while (list)
	{
		list = list->next;
		n++;
	}
	return (n);
}

t_list		*createtr(char *buf, char a, int ret)
{
	t_list	*head;
	t_tetr	tetrimino;
	int		i;
	int		t;
	int		c;

	c = 0;
	bufchecker(buf, a, ret);
	tetrimino.letter = a;
	tetrimino.shape = createshape(buf, a, ret);
	moveleft(tetrimino.shape, a);
	tetrimino.height = height(tetrimino.shape, a);
	moveup(tetrimino.shape, a, tetrimino.height);
	tetrimino.width = width(tetrimino.shape, a);
	val(&tetrimino);
	tetrimino.i = 0;
	tetrimino.j = 0;
	tetrimino.x = 0;
	tetrimino.c = 0;
	tetrimino.y = 0;
	head = ft_lstnew(&tetrimino, sizeof(tetrimino));
	head->pos = 0;
	head->content_size = 0;
	return (head);
}

char		**createshape(char *buf, char a, int ret)
{
	char	*newbuf;
	char	**shape;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	newbuf = (char *)malloc(sizeof(char) * 17);
	trim(&newbuf, buf, a);
	if (!(shape = (char**)malloc(sizeof(char *) * 5)))
		return (NULL);
	shape[4] = NULL;
	while (i < 4)
	{
		if (!(shape[i] = (char*)malloc(5)))
			return (NULL);
		j = 0;
		while (j < 4)
			shape[i][j++] = newbuf[k++];
		shape[i++][j] = '\0';
	}
	free(newbuf);
	return (shape);
}

void		deletelist(t_list **headref)
{
	t_list	*current;
	t_list	*next;
	char	**shape;
	t_tetr	*a;
	int		i;

	i = 0;
	current = *headref;
	while (current != NULL)
	{
		a = current->content;
		shape = a->shape;
		freeshape(shape);
		next = current->next;
		free(a);
		free(current);
		current = next;
	}
	*headref = NULL;
}
