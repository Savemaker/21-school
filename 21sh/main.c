/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/29 20:17:05 by gbeqqo           ###   ########.fr       */
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

int check_for_redir(tree *ast)
{
	while (ast)
	{
		if (ast->type == 5)
			return (1);
		ast = ast->right;
	}
	return (0);
}

int		redirections(tree *ast, int type)
{
	int fd;
	int count;

	fd = -1;
	while (ast && ast->type != 5)
		ast = ast->right;
	count = count_token_types(ast->current, type);
	while (ast->current)
	{
		if (ast->current->type == type)
		{
			count -= 1;
			if (count == 0)
				break;
		}
		ast->current = ast->current->next;
	}
	if (ast->type == 5)
	{
		fd = open(ast->current->next->buf, O_RDWR | O_CREAT, 0644);
	}
	return (fd);
}

void	other_executions(tree *ast, int fd)
{
	int count;
	int new;

	while (ast && ast->type != 5)
		ast = ast->right;
	count = count_token_types(ast->current, 3) - 1;
	while (ast->current && count != 0)
	{
		if (ast->current->type == 3)
		{
			count -= 1;
			new = open(ast->current->next->buf, O_RDWR, 0644);
			dup2(new, fd);
		}
		ast->current = ast->current->next->next;
	}
}

void	execute_right(tree *ast, int in, int out, int temp)
{
	pid_t p;
	int fd;
	int flag;

	flag = 0;
	if (check_for_redir(ast->right))
	{
		fd = redirections(ast, 3);
		ast->fd = fd;
		flag = 1;
	}
	p = fork();
	if (p == 0)
	{
		dup2(temp, 0);
		close(in);
		if (ast->parent && ast->parent->type == 1)
		{
			if (flag == 0)
				dup2(out, 1);
			if (flag == 1)
				dup2(fd, 1);
		}
		else
			if (flag == 1)
				dup2(fd, 1);
		create_argv(ast->right);
		execvp(ast->right->argv[0], ast->right->argv);
	}
	else
	{
		waitpid(p, NULL, 0);
		if (flag)
			other_executions(ast->right, fd);
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

char	*take_buf(tree *ast, int type)
{
	char *res;
	int count;

	while (ast && ast->type != 5)
		ast = ast->right;
	count = count_token_types(ast->current, type);
	while (ast->current)
	{
		if (ast->current->type == type)
		{
			count -= 1;
			if (count == 0)
			{
				res = ast->current->next->buf;
				break;
			}
		}
		ast->current = ast->current->next;
	}
	return (res);
}

void	execute_tree(tree *ast)
{
	int fd[2];
	int tmp_fd;
	int start;
	int new;
	char *buf;

	start = 0;
	tmp_fd = 0;
	if (ast == NULL)
		return ;
	// printf("%d", ast->type);
	// execute_tree(ast->left);
	// execute_tree(ast->right);
	if (ast->type == 1)
	{
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
			if (check_for_redir(ast->right))
			{
				buf = take_buf(ast->right, 3);
				new = open(buf, O_RDONLY);
				tmp_fd = new;
			}
			else
				tmp_fd = fd[0];
			ast = ast->parent;
		}
		close(tmp_fd);
	}
	else if (ast->type == 2)
	{
		execute_tree(ast->left);
		execute_tree(ast->right);
	}
	else if (ast->type == 3)
	{
		simple_execution(ast);
	}
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

// void	create_tree(tree *ast)
// {
// 	token *left;
// 	token *right;

// 	left = ast->current;
// 	right = NULL;
// 	if (ast == NULL)
// 		return ;
// 	ast->t_pipes = count_token_types(ast->current, 1);
// 	ast->t_semis = count_token_types(ast->current, 2);
// 	if (ast->type == 1)
// 	{
// 		if (ast->t_pipes == 0)
// 			ast->type = 2;
// 		else if (ast->type == 2 && ast->t_semis == 0)
// 			ast->type = 3;
// 		else
// 		{
// 			split_list(&left, &right, ast, 1);
// 			ast->left = create_node(left, 1, ast);
// 			ast->right = create_node(right, 2, ast);
// 			create_tree(ast->left);
// 			create_tree(ast->right);
// 		}
// 	}
// 	if (ast->type == 2)
// 	{
// 		if (ast->t_semis == 0)
// 			ast->type = 3;
// 		else
// 		{
// 			split_semicolomn(&left, &right, ast);
// 			ast->left = create_node(left, 3, ast);
// 			ast->right = create_node(right, 2, ast);
// 			create_tree(ast->left);
// 			create_tree(ast->right);
// 		}
// 	}
// 	if (ast->type == 3)
// 	{
// 		split(&left, &right);
// 		ast->left = create_node(left, 4, ast);
// 		ast->right = create_node(right, 3, ast);
// 		create_tree(ast->right);
// 	}
// }
