/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:06:20 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/09 16:12:57 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int		check_type_class(t_token *list, int type, int count)
{
	while (list)
	{
		if (list->type == type)
		{
			count -= 1;
			if (count == 0)
			{
				if (ft_strcmp(list->buf, ">") == 0)
					return (1);
				if (ft_strcmp(list->buf, ">>") == 0)
					return (2);
			}
		}
		list = list->next;
	}
	return (0);
}

char	*take_buf(t_token *list, int type, int count)
{
	char	*res;
	int		fd;

	res = NULL;
	while (list)
	{
		if (list->type == type)
		{
			count -= 1;
			if (count == 0)
			{
				res = list->next->buf;
				break ;
			}
			else
			{
				fd = open(list->next->buf, O_RDWR | O_CREAT, 0644);
				close(fd);
			}
		}
		list = list->next;
	}
	return (res);
}

int		check_for_type(t_token *list, int type)
{
	while (list)
	{
		if (list->type == type)
			return (1);
		list = list->next;
	}
	return (0);
}

int		check_for_redir(t_tree *ast, int type)
{
	int res;

	res = 0;
	while (ast)
	{
		if (ast->type == 5)
		{
			res = check_for_type(ast->current, type);
		}
		ast = ast->right;
	}
	return (res);
}

t_tree	*get_redirs_node(t_tree *ast)
{
	while (ast)
	{
		if (ast->type == 5)
			return (ast);
		ast = ast->right;
	}
	return (NULL);
}

void	aggregation_order_stuff(t_token *list, int fd, int order)
{
	int num_a;
	int num_b;

	num_a = ft_atoi(list->buf);
	num_b = ft_atoi(list->next->next->buf);
	if (order == 0)
		dup2(num_b, num_a);
	if (order == 1)
		dup2(fd, num_a);
}

void	aggregation_order(t_token *list, int fd)
{
	int order;
	int num_a;

	order = 0;
	while (list)
	{
		if (list->type == 3)
			order = 1;
		if (list->type == 9)
		{
			if (ft_strcmp(list->next->next->buf, "-") == 0)
			{
				num_a = ft_atoi(list->buf);
				close(num_a);
			}
			else
			{
				aggregation_order_stuff(list, fd, order);
				break ;
			}
		}
		list = list->next;
	}
}

int		get_redirections(t_tree *ast, int old, int type, int flag)
{
	int		fd;
	int		count;
	char	*buf;
	t_tree	*redirs;

	if (check_for_redir(ast, type))
	{
		redirs = get_redirs_node(ast);
		count = count_token_types(redirs->current, type);
		buf = take_buf(redirs->current, type, count);
		if (type == 3)
		{
			if (check_type_class(redirs->current, type, count) == 1)
				fd = open(buf, O_RDWR | O_CREAT, 0644);
			if (check_type_class(redirs->current, type, count) == 2)
				fd = open(buf, O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		if (type == 4)
			fd = open(buf, O_RDONLY);
		if (flag == 1)
			close(old);
		return (fd);
	}
	return (old);
}
