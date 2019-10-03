/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/02 21:53:55 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <string.h>

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
	res->fd = 0;
	if (list == NULL)
		res->type = 0;
	else
		res->type = type;
	return (res);
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

void	split_semicolomn(token **left, token **right)
{
	token *list;

	list = *left;
	if (list == NULL)
		return ;
	while (list->next && list->next->type != 2)
		list = list->next;
	if (list->next && list->next->next)
	{
		*right = list->next->next;
	}
	list->next = NULL;
}

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
	if (ast->type == 2)
	{
		if (ast->t_pipes == 0 && ast->t_semis == 0)
			ast->type = 3;
		else if (ast->t_semis == 0 && ast->t_pipes > 0)
			ast->type = 1;
		else
		{
			split_semicolomn(&left, &right);
			ast->left = create_node(left, 2, ast);
			ast->right = create_node(right, 2, ast);
			create_tree(ast->left);
			create_tree(ast->right);
		}
	}
	if (ast->type == 1)
	{
		if (ast->t_pipes == 0)
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
	if (ast->type == 3)
	{
		if (ast->current->type >= 3 && ast->current->type <= 8)
			ast->type = 5;
		else
		{
		split(&left, &right);
		ast->left = create_node(left, 4, ast);
		ast->right = create_node(right, 3, ast);
		create_tree(ast->right);
		}
	}
}

int		type(char *buf)
{
	if (ft_strcmp(buf, "|") == 0)
		return (1);
	if (ft_strcmp(buf, ";") == 0)
		return (2);
	if (ft_strcmp(buf, ">") == 0)
		return (3);
	if (ft_strcmp(buf, "<") == 0)
		return (4);
	if (ft_strcmp(buf, ">>") == 0)
		return (3);
	if (ft_strcmp(buf, "<<") == 0)
		return (6);
	if (ft_strcmp(buf, "<&") == 0)
		return (7);
	if (ft_strcmp(buf, ">&") == 0)
		return (8);
	return (0);
}


void	append(token **head, token *new)
{
	token *tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int buf_word_len(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';' && cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<')
		i++;
	return (i);
}

char *create_buf(char *cmd)
{
	char *res;
	int len;
	int i;

	i = 0;
	len = buf_word_len(cmd);
	res = NULL;
	if (len > 0)
	{
		res = (char *)malloc(sizeof(char) * (len + 1));
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
		{
			res[i] = cmd[i];
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}

token *create_token(char *cmd, int i, size_t cmd_len)
{
	token	*new;
	char	*buf;

	buf = NULL;
	new = NULL;
	if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '>' && cmd[i+1] == '>')
		buf = ft_strdup(">>");
	else if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '<' && cmd[i+1] == '<')
		buf = ft_strdup("<<");
	else if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '<' && cmd[i+1] == '&')
		buf = ft_strdup("<&");
	else if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '>' && cmd[i+1] == '&')
		buf = ft_strdup(">&");
	else if (cmd[i] && cmd[i] == ';')
		buf = ft_strdup(";");
	else if (cmd[i] && cmd[i] == '|')
		buf = ft_strdup("|");
	else if (cmd[i] && cmd[i] == '>')
		buf = ft_strdup(">");
	else if (cmd[i] && cmd[i] == '<')
		buf = ft_strdup("<");
	if (buf != NULL)
	{
		new = (token *)malloc(sizeof(token) * 1);
		new->buf = buf;
		new->type = type(buf);
		new->next = NULL;
	}
	return (new);
}

token *create_new(char *cmd, int i, size_t cmd_len)
{
	token *new;
	char *buf;

	new = NULL;
	buf = create_buf(&cmd[i]);
	if (buf != NULL)
	{
		new = (token *)malloc(sizeof(token) * 1);
		new->buf = buf;
		new->next = NULL;
		new->type = type(buf);
	}
	else
		new = create_token(cmd, i, cmd_len);
	return (new);
}

token *lexer(char *cmd)
{
	token *head;
	token *new;
	int i;
	size_t len;

	len = ft_strlen(cmd);
	i = 0;
	head = NULL;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '"' || cmd[i] == 39))
			i++;
		if (cmd[i] == '\0')
			break ;
		new = create_new(cmd, i, len);
		append(&head, new);
		if (cmd[i + 1] && cmd[i] == '>' && cmd[i+1] == '>')
			i += 2;
		else if (cmd[i + 1] && cmd[i] == '<' && cmd[i+1] == '<')
			i += 2;
		else if (cmd[i + 1] && cmd[i] == '<' && cmd[i+1] == '&')
			i += 2;
		else if (cmd[i + 1] && cmd[i] == '>' && cmd[i+1] == '&')
			i += 2;
		else if (cmd[i] == ';' || cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
			i++;
		else
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';' && cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<')
				i++;
	}
	return (head);
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
		list = list->next;
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
