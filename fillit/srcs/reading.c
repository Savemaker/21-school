/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:44:41 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/26 15:54:27 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fillit.h"

t_list		*reading(const int fd)
{
	t_list	*list;
	t_list	*head;
	int		ret;
	char	buf[21];
	char	a;

	a = 'A';
	list = NULL;
	while ((ret = read(fd, buf, 21)) && ret != -1)
	{
		buf[ret] = '\0';
		if (buf[0] == '\n')
			stop();
		if (a > 'Z')
			stop();
		if (buf[ret - 1] != '\n')
			stop();
		head = createtr(buf, a++, ret);
		push_end(&list, head);
	}
	if (list == NULL || buf[20] == '\n')
		stop();
	return (list);
}

void		push_end(t_list **list, t_list *head)
{
	t_list *new;

	new = *list;
	if (new == NULL)
	{
		*list = head;
	}
	else
	{
		while (new->next)
		{
			new = new->next;
		}
		new->next = head;
	}
}

void		ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void		bufchecker(char *buf, char a, int ret)
{
	int n;
	int d;
	int l;
	int i;

	i = 0;
	n = 0;
	d = 0;
	l = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '.')
			d += 1;
		if (buf[i] == '#')
			l += 1;
		i++;
	}
	if (d != 12 || l != 4)
		stop();
	nchecker(buf, ret);
}

void		nchecker(char *buf, int ret)
{
	int flag;

	flag = 0;
	if (buf[4] != '\n')
		flag = 1;
	if (buf[9] != '\n')
		flag = 1;
	if (buf[14] != '\n')
		flag = 1;
	if (buf[19] != '\n')
		flag = 1;
	if (flag == 1)
		stop();
}
