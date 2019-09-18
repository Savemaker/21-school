/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/14 16:30:32 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <string.h>

//  command: ls | cat - e | grep '21'

typedef struct tree{
	struct tree *left;
	struct tree *right;
	token		*current;
	int t_pipes;
	int t_semis;
	int type;   // 1 = pipe; 2 = command; 3 = suffix; 4 = word;
}tree;

typedef struct eval{
    int args;
    char **argv;
    int cur;
	int in;
	int out;
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

tree *create_node(token *list, int type)
{
	tree *res;

	res = (tree *)malloc(sizeof(tree) * 1);
	res->current = list;
	res->left = NULL;
	res->right = NULL;
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

void    check_tree(tree *pipe, ev *eval)
{
    if (pipe == NULL)
        return ;
    if (pipe->type == 4)
        eval->args += 1;
    check_tree(pipe->left, eval);
    check_tree(pipe->right, eval);
}

void     create_argv(tree *tree, ev *eval)
{
    if (tree == NULL)
        return;
    if (tree->type == 4)
    {
        eval->argv[eval->cur] = strdup(tree->current->buf);
        eval->cur += 1;
    }
    create_argv(tree->left, eval);
    create_argv(tree->right, eval);
}

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

void     execute_tree(tree *tr, ev *eval)
{
	int fd[2];
    if (tr == NULL)
        return ;
    if (tr->type == 3)
    {
		pipe(fd);
        check_tree(tr, eval);
        eval->argv = (char **)malloc(sizeof(char *) * (eval->args + 1));
        create_argv(tr, eval);
        eval->argv[eval->cur] = NULL;
        if (fork() == 0)
		{
			dup2(eval->in, 0);
			if (eval->pipes != 0)
				dup2(fd[1], 1);
			close(fd[0]);
            execvp(eval->argv[0], eval->argv);
		}
		close(fd[1]);
		if (eval->pipes != 0)
		{
			eval->in = fd[0];
			eval->pipes -= 1;
		}
        eval->argv = NULL;
        eval->args = 0;
        eval->cur = 0;
        wait(NULL);
        
    }
    execute_tree(tr->left, eval);
    execute_tree(tr->right, eval);
}

ev *create_eval(token *list)
{
	ev *eval;

	eval = (ev *)malloc(sizeof(ev) * 1);
    eval->args=0;
    eval->cur = 0;
    eval->argv =NULL;
	eval->in = 0;
	eval->out = 1;
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
			ast->left = create_node(left, 1);
			ast->right = create_node(right, 2);
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
			ast->left = create_node(left, 2);
			ast->right = create_node(right, 3);
			create_tree(ast->left);
			create_tree(ast->right);
		}
	}
	if (ast->type == 3)
	{
		split(&left, &right);
		ast->left = create_node(left, 4);
		ast->right = create_node(right, 3);
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
	ast = (tree *)malloc(sizeof(tree) * 1);
	ast->current = list;
	ast->type = 1;
	ast->t_semis = count_token_types(list, 2);
	ast->t_pipes = count_token_types(list, 1);
	create_tree(ast);
	execute_tree(ast, eval);
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