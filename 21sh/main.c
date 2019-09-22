/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/21 18:41:16 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <string.h>

//  command: ls | cat - e | grep '21'



typedef struct eval{
    int args;
    char **argv;
    int cur;
	int in;
	int out;
	int st_in;
	int st_out;
	int pipes;
	int semis;
}ev;


int		count_token_types(token *list, int type)
{
	int i;

	i = 0;
	while (list)
	{
		if (list->type == type)
			i++;
		list = list->next;
	}
	return (i);
}

void	split_list(token **list, token **right, tree *ast, int type)
{
	token *temp;

	temp = *list;
	if (temp == NULL)
		return ;
	while (temp->next)
	{
		if (temp->next && temp->next->type == type)
		{
			if (type == 1)
			{
				ast->t_pipes -= 1;
				if (ast->t_pipes == 0)
				{
					*right = temp->next->next;
					temp->next = NULL;
					break ;
				}
			}
			if (type == 2)
			{
				ast->t_semis -= 1;
				if (ast->t_semis == 0)
				{
					*right = temp->next->next;
					temp->next = NULL;
					break ;
				}
			}
		}
		temp = temp->next;
	}
}

tree *create_node(token *list, int type, tree *parent)
{
	tree *res;

	res = (tree *)malloc(sizeof(tree) * 1);
	res->parent = parent;
	res->current = list;
	res->left = NULL;
	res->right = NULL;
	res->in = 0;
	res->out = 1;
	res->t_pipes = 0;
	res->t_semis = 0;
	res->argv = NULL;
	res->args = 0;
	res->cur = 0;
	res->exe = 0;
	if (list == NULL)
		res->type = 0;
	else
		res->type = type;
	return (res);
}

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

void	split(token **list, token **right)
{
	token *temp;

	temp = *list;
	*right = NULL;
	if (temp == NULL)
	{
		return ;
	}
	if (temp->next)
	{
		*right = temp->next;
		temp->next = NULL;
	}
}

// void	create_tree(tree *ast, token *list, ev *eval)
// {
// 	token *left;
// 	token *right;

// 	left = list;
// 	right = NULL;
// 	if (ast->type == 1 && eval->t_pipes == 0)
// 	{
// 		ast->type = 2;
// 		return ;
// 	}
// 	if (ast->type == 1 && eval->t_pipes != 0)
// 	{
// 		split_list(&list, &right, eval, 1);
// 		eval->t_pipes -= 1;
// 		eval->pipes = eval->t_pipes;
// 		ast->left = create_node(left, 1);
// 		ast->right = create_node(right, 2);
// 		create_tree(ast->left, left, eval);
// 		create_tree(ast->right, right, eval);
// 	}
// }


// void	create_tree(tree *ast, token *list, ev *eval)
// {
// 	token *left;
// 	token *right;

// 	left = list;
// 	right = NULL;
// 	if (ast->type == 1 && eval->pipes == 0)
// 	{
// 		ast->type = 2;
// 	}
// 	else if (ast->type == 1 && eval->pipes != 0)
// 	{
// 		split_list(&list, &right, eval);
// 		ast->left = create_node(list, 1);
// 		ast->right = create_node(right, 2);
// 		create_tree(ast->left, list, eval);
// 		create_tree(ast->right, right, eval);
// 	}
// 	if (ast->type == 2)
// 	{
// 		if (ast == NULL)
// 			return ;
// 		split(&(ast->current), &right);
// 		ast->left = create_node(ast->current, 4);
// 		ast->right = create_node(right, 2);
// 		create_tree(ast->right, right, eval);
// 	}
// }

// void    check_tree(tree *pipe)
// {
//     if (pipe == NULL)
//         return ;
//     if (pipe->type == 4)
//         pipe->args += 1;
//     check_tree(pipe->left);
//     check_tree(pipe->right);
// }

// void     create_argv(tree *tree)
// {
//     if (tree == NULL)
//         return;
//     if (tree->type == 4)
//     {
//         tree->argv[tree->cur] = strdup(tree->current->buf);
//         tree->cur += 1;
//     }
//     create_argv(tree->left);
//     create_argv(tree->right);
// }

// void	execute_tree(tree *ast, ev *eval)
// {
// 	int fd[2];

// 	if (ast == NULL)
// 		return ;
// 	if (ast->type == 1)
// 	{
// 		pipe(fd);
// 		dup2(eval->in, 0);
// 		dup2(eval->out, 1);
// 		execute_tree(ast->left, eval);
// 		execute_tree(ast->right, eval);
// 	}
// 	if (ast->type == 2)
// 	{
// 		execute_tree(ast->left, eval);
// 		execute_tree(ast->right, eval);
// 	}
// 	if (ast->type == 3)
// 	{
// 		check_tree(ast, eval);
// 		eval->argv = (char **)malloc(sizeof(char *) * (eval->args + 1));
// 		create_argv(ast, eval);
// 		eval->argv[eval->cur] = NULL;
// 		if (fork() == 0)
// 		{
// 			dup2(eval->in, 0);
// 			if (eval->pipes != 0)
// 				dup2(eval->out, 1);
// 			execvp(eval->argv[0], eval->argv);
// 		}
// 		wait(NULL);
// 		eval->args = 0;
// 		eval->argv = NULL;
// 		eval->cur = 0;
// 	}
// }

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

void	execute_right(tree *ast, int in, int out, int temp)
{
	pid_t p;

	p = fork();
	if (p == 0)
	{
		create_argv(ast->right);
		dup2(temp, 0);
		close(in);
		if (ast->parent)
			dup2(out, 1);
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

void	execute_tree(tree *ast)
{
	int fd[2];
	int tmp_fd;
	int start;
	int semi;

	if (ast == NULL)
		return ;
	start = 0;
	tmp_fd = 0;
	if (ast->type == 1)
	{
		while (ast->left->type == 1)
			ast = ast->left;
		while (ast != NULL)
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

ev *create_eval(token *list)
{
	ev *eval;

	eval = (ev *)malloc(sizeof(ev) * 1);
    eval->args = 0;
    eval->cur = 0;
    eval->argv = NULL;
	eval->in = 0;
	eval->out = 1;
	eval->st_in = 0;
	eval->st_out = 0;
	eval->pipes = count_token_types(list, 1);
	eval->semis = count_token_types(list, 2);
	return (eval);
}

void	create_tree(tree *ast)
{
	token *left;
	token *right;

	left = ast->current;
	right = NULL;
	if (ast == NULL)
		return ;
	ast->t_pipes = count_token_types(ast->current, 1);
	ast->t_semis = count_token_types(ast->current, 2);
	if (ast->type == 1)
	{
		if (ast->t_pipes == 0)
			ast->type = 2;
		else if (ast->type == 2 && ast->t_semis == 0)
			ast->type = 3;
		else
		{
			split_list(&left, &right, ast, 1);
			ast->left = create_node(left, 1, ast);
			ast->right = create_node(right, 2, ast);
			create_tree(ast->left);
			create_tree(ast->right);
		}
	}
	if (ast->type == 2)
	{
		if (ast->t_semis == 0)
			ast->type = 3;
		else
		{
			split_list(&left, &right, ast, 2);
			ast->left = create_node(left, 2, ast);
			ast->right = create_node(right, 3, ast);
			create_tree(ast->left);
			create_tree(ast->right);
		}
	}
	if (ast->type == 3)
	{
		split(&left, &right);
		ast->left = create_node(left, 4, ast);
		ast->right = create_node(right, 3, ast);
		create_tree(ast->right);
	}
}


void	action(char *cmd)
{
	token *list;
	tree *ast;
	ev *eval;

	list = lexer(cmd);
	eval = create_eval(list);
	ast = create_node(list, 1, NULL);
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