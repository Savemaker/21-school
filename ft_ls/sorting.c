/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:17:26 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/07/22 15:19:26 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*merge(t_dir *a, t_dir *b, int (f) (t_dir *, t_dir *))
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if ((f(a, b) == 0))
	{
		a->next = merge(a->next, b, f);
		return (a);
	}
	else
	{
		b->next = merge(b->next, a, f);
		return (b);
	}
}

void		divide_list(t_dir **list, t_dir **b)
{
	t_dir *fast;
	t_dir *slow;

	slow = *list;
	fast = (*list)->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*b = slow->next;
	slow->next = NULL;
}

void		merge_sorting(t_dir **list, int (f)(t_dir *, t_dir *))
{
	t_dir *a;
	t_dir *b;

	if (*list == NULL || (*list)->next == NULL)
		return ;
	a = *list;
	b = NULL;
	divide_list(list, &b);
	merge_sorting(&a, f);
	merge_sorting(&b, f);
	*list = merge(a, b, f);
}

int			default_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) > 0)
		return (1);
	return (0);
}

int			reverse_sort(t_dir *dir, t_dir *dira)
{
	if (ft_strcmp(dir->name, dira->name) < 0)
		return (1);
	return (0);
}

int			time_sort(t_dir *dir, t_dir *dira)
{
	struct stat s;
	struct stat sa;
	time_t		d;
	time_t		da;

	lstat(dir->path, &s);
	lstat(dira->path, &sa);
	d = s.st_mtime;
	da = sa.st_mtime;
	if (d < da)
		return (1);
	if (d == da)
		if (ft_strcmp(dir->name, dira->name) > 0)
			return (1);
	return (0);
}

int			time_reverse_sort(t_dir *dir, t_dir *dira)
{
	struct stat s;
	struct stat sa;
	time_t		d;
	time_t		da;

	lstat(dir->path, &s);
	lstat(dira->path, &sa);
	d = s.st_mtime;
	da = sa.st_mtime;
	if (d > da)
		return (1);
	if (d == da)
	{
		if (ft_strcmp(dir->name, dira->name) < 0)
			return (1);
	}
	return (0);
}

void		sorts(t_dir **head, int flags)
{
	if (check_flag('r', flags) && (check_flag('t', flags) == 0))
		merge_sorting(head, reverse_sort);
	else if (check_flag('t', flags) && (check_flag('r', flags) == 0))
	{
		merge_sorting(head, time_sort);
	}
	else if (check_flag('t', flags) && (check_flag('r', flags) == 1))
		merge_sorting(head, time_reverse_sort);
	else
		merge_sorting(head, default_sort);
}
