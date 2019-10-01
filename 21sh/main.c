/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/01 20:34:59 by gbeqqo           ###   ########.fr       */
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

void	execute_start(tree *ast, int in, int out)
{
	pid_t p;

	p = fork();
	if (p == 0)
	{
		if (ast->right)
			dup2(out, 1);
		close(in);
		create_argv(ast->left);
		execvp(ast->left->argv[0], ast->left->argv);
	}
	else
	{
		waitpid(p, NULL, 0);
		close(out);
	}
}

token	*check_for_redir(tree *ast, int type)
{
	while (ast)
	{
		if (ast->type == 5)
		{
			while(ast->current)
			{
				if (ast->current->type == type)
				{
					return (ast->current);
				}
				ast->current = ast->current->next;
			}
		}
		ast = ast->right;
	}
	return (NULL);
}

int		get_input(tree *ast, int old)
{
	token *temp;

	temp = check_for_redir(ast, 4);
	// if (temp != NULL)
	// 	ft_putstr("yikes");
	return (old);
}

int		get_output(tree *ast, int old)
{
	int fd;
	int count;
	token *temp;
	char *buf;

	count = 0;
	temp = check_for_redir(ast, 3);
	if (temp != NULL)
	{
		count = count_token_types(temp, 3);
		buf = take_buf(temp, 3, count);
		ft_putstr(buf);
		fd = open(buf, O_RDWR | O_CREAT, 0644);
		close(old);
		return (fd);
	}
	else
		ft_putstr("yikes");
	return (old);
}

void	execute_right(tree *ast, int in, int out, int temp)
{
	pid_t	p;

	temp = get_input(ast, temp);
	out = get_output(ast, out);	
	p = fork();
	if (p == 0)
	{
		dup2(temp, 0);
		close(in);
		if (check_for_redir(ast, 3) != NULL)
			dup2(out, 1);
		else
		{
			if	(ast->parent && ast->parent->type == 1)
				dup2(out, 1);
		}
		create_argv(ast->right);
		execvp(ast->right->argv[0], ast->right->argv);
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
	pid_t p;

	p = fork();
	if (p == 0)
	{
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
			execute_start(ast, fd[0], fd[1]);
			start = 1;
			tmp_fd = fd[0];
			pipe(fd);
		}
		execute_right(ast, fd[0], fd[1], tmp_fd);
		tmp_fd = fd[0];
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
