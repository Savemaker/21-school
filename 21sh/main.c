/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/02 20:01:44 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <string.h>

//  command: ls | cat - e | grep '21'

int     list_len(token *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int		check_type_class(token *list, int type, int count)
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
	}
	return (0);
}

char	*take_buf(token *list, int type, int count)
{
	char *res;

	while (list)
	{
		if (list->type == type)
		{
			count -= 1;
			if (count == 0)
			{
				res = list->next->buf;
				break;
			}
		}
		list = list->next;
	}
	return (res);
}

void	args_counter(tree *ast, tree *tmp)
{
	if (ast == NULL)
		return ;
	if (ast->type == 4)
		tmp->args += 1;
	args_counter(ast->left, tmp);
	args_counter(ast->right, tmp);
}

void	argv_creation(tree *ast, tree *tmp)
{
	if (ast == NULL)
		return ;
	if (ast->type == 4)
	{
		tmp->argv[tmp->cur] = ft_strdup(ast->current->buf);
		tmp->cur += 1;
	}
	argv_creation(ast->left, tmp);
	argv_creation(ast->right, tmp);
}

void	create_argv(tree *ast)
{
	tree *tmp;

	tmp = ast;
	args_counter(ast, tmp);
	ast->argv = (char **)malloc(sizeof(char *) * (ast->args + 1));
	argv_creation(ast, tmp);
	ast->argv[ast->cur] = NULL;
}

int		check_for_type(token *list, int type)
{
	while (list)
	{
		if (list->type == type)
			return (1);
		list = list->next;
	}
	return (0);
}

int		check_for_redir(tree *ast, int type)
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

tree	*get_redirs_node(tree *ast)
{
	while (ast)
	{
		if (ast->type == 5)
			return (ast);
		ast = ast->right;
	}
	return (NULL);
}

int		get_redirections(tree *ast, int old, int type, int flag)
{
	int fd;
	int count;
	char *buf;
	tree *redirs;

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

void	execute_start(tree *ast, int in, int out)
{
	pid_t p;

	in = get_redirections(ast, in, 4, 0);
	out = get_redirections(ast, out, 3, 1);
	p = fork();
	if (p == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		close(in);
		create_argv(ast);
		execvp(ast->argv[0], ast->argv);
	}
	else
	{
		waitpid(p, NULL, 0);
		close(out);
	}
}

void	execute_right(tree *ast, int in, int out, int temp)
{
	pid_t	p;

	temp = get_redirections(ast, temp, 4, 1);
	out = get_redirections(ast, out, 3, 1);
	p = fork();
	if (p == 0)
	{
		dup2(temp, 0);
		close(in);
		if (check_for_redir(ast, 3) == 1)
		{
			dup2(out, 1);
		}
		else if (ast->parent && ast->parent->parent && ast->parent->parent->type == 1)
			dup2(out, 1);
		create_argv(ast);
		execvp(ast->argv[0], ast->argv);
	}
	else
	{
		waitpid(p, NULL, 0);
		close(out);
		close(temp);
	}
}

void	simple_execution(tree *ast)
{
	pid_t	p;
	int		in;
	int		out;

	in = 0;
	out = 1;
	out = get_redirections(ast, out, 3, 0);
	in = get_redirections(ast, in, 4, 0);
	p = fork();
	if (p == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		create_argv(ast);
		execvp(ast->argv[0], ast->argv);
	}
	else
	{
		waitpid(p, NULL, 0);
	}
}


void	execute_tree_type_one(tree *ast)
{
	int fd[2];
	int start;
	int tmp_fd;

	start = 0;
	while (ast->left->type == 1)
		ast = ast->left;
	while (ast != NULL && ast->type == 1)
	{
		pipe(fd);
		if (start == 0)
		{
			execute_start(ast->left, fd[0], fd[1]);
			start = 1;
			tmp_fd = fd[0];
			pipe(fd);
		}
		execute_right(ast->right, fd[0], fd[1], tmp_fd);
		if (check_for_redir(ast->right, 3) == 0)
			tmp_fd = fd[0];
		else
			tmp_fd = get_redirections(ast->right, fd[1], 3, 1);
		ast = ast->parent;
	}
	close(tmp_fd);
}

void	execute_tree(tree *ast)
{
	if (ast == NULL)
		return ;
	if (ast->type == 1)
		execute_tree_type_one(ast);
	else if (ast->type == 2)
	{
		execute_tree(ast->left);
		execute_tree(ast->right);
	}
	else if (ast->type == 3)
		simple_execution(ast);
}

void	action(char *cmd)
{
	token *list;
	token *feed;
	tree *ast;
	int br;

	br = 0;
	list = lexer(cmd);
	ast = create_node(list, 2, NULL);
	create_tree(ast);
	execute_tree(ast);
}

int main()
{
	char *cmd;

	while (1)
	{
		cmd = readline("-> ");
		action(cmd);
	}
}
