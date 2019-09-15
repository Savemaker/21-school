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

int		*create_tab(int words)
{
	int *res;
	int i;

	i = 0;
	words++;
	res = (int *)malloc(sizeof(int) * words);
	while (i < words)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

void	copy_split_delim(char **res, char *cmd, char delim)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		k = 0;
		if (cmd[i] == '\0')
			break ;
		while (cmd[i] != '\0' && cmd[i] != delim)
			res[j][k++] = cmd[i++];
		res[j][k] = '\0';
		j++;
	}
}

int		*count_each_word_delim(char *cmd, int words, char delim)
{
	int i;
	int len;
	int *tab;
	int j;

	i = 0;
	j = 0;
	len = 0;
	tab = create_tab(words);
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		while (cmd[i] != '\0' && cmd[i] != delim)
		{
			tab[j]++;
			i++;
		}
		j++;
	}
	return (tab);
}

char	**ft_split_delim(char *cmd, int words, char delim)
{
	char	**res;
	int		*tab;
	int		i;

	i = 0;
	tab = count_each_word_delim(cmd, words, delim);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	while (i < words)
	{
		res[i] = (char *)malloc(sizeof(char) * tab[i] + 1);
		i++;
	}
	free(tab);
	res[i] = NULL;
	copy_split_delim(res, cmd, delim);
	return (res);
}

int		count_words_delim(char *cmd, char delim)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		if (cmd[i] != '\0')
			w++;
		while (cmd[i] != '\0' && cmd[i] != delim)
			i++;
	}
	return (w);
}

int		count_words(char *cmd)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '"' || cmd[i] == 39)
			i++;
		if (cmd[i] != '\0')
			w++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i]
		!= ' ' && cmd[i] != '"' && cmd[i] != 39)
			i++;
	}
	return (w);
}

int		*count_each_word(char *cmd, int words)
{
	int i;
	int len;
	int *tab;
	int j;

	i = 0;
	j = 0;
	len = 0;
	tab = create_tab(words);
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '"' || cmd[i] == 39)
			i++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i]
		!= ' ' && cmd[i] != '"' && cmd[i] != 39)
		{
			tab[j]++;
			i++;
		}
		j++;
	}
	return (tab);
}

void	copy_split(char **res, char *cmd)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '"' || cmd[i] == 39)
			i++;
		k = 0;
		if (cmd[i] == '\0')
			break ;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i]
		!= ' ' && cmd[i] != '"' && cmd[i] != 39)
			res[j][k++] = cmd[i++];
		res[j][k] = '\0';
		j++;
	}
}

char	**ft_full_split(char *cmd, int words)
{
	char	**res;
	int		*tab;
	int		i;

	i = 0;
	tab = count_each_word(cmd, words);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	while (i < words)
	{
		res[i] = (char *)malloc(sizeof(char) * tab[i] + 1);
		i++;
	}
	free(tab);
	res[i] = NULL;
	copy_split(res, cmd);
	return (res);
}


//  command: ls | cat - e | grep '21'

typedef struct tokens{
	int type;
	char *buf;
	struct tokens *next;
}token;

typedef struct tree{
	struct tree *left;
	struct tree *right;
	token *current;
	int type;   // 1 = pipe; 2 = command; 3 = suffix; 4 = word;
}tree;

typedef struct eval{
    int args;
    char **argv;
    int cur;
	int in;
	int out;
	int pipes;
}ev;

int		type(char *buf)
{
	if (ft_strcmp(buf, "|") == 0)
		return (0);
	return (1);
}

token *create_new(char *buf)
{
	token *new;

	new = (token *)malloc(sizeof(token) * 1);
	new->buf = ft_strdup(buf);
	new->type = type(buf);
	new->next = NULL;
	return (new);
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

token *create_list(char *buf)
{
	token *head;
	token *new;
	char **split;
	int w;
	int i;

	head = NULL;
	i = 0;
	w = count_words(buf);
	split = ft_full_split(buf, w);
	while (split[i])
	{
		new = create_new(split[i]);
		append(&head, new);
		i++;
	}
	return (head);
}

int		count_pipes(token *list)
{
	int i;

	i = 0;
	while (list)
	{
		if (list->type == 0)
			i++;
		list = list->next;
	}
	return (i);
}

void	split_list(token **list, token **right, int pipes)
{
	token *temp;

	temp = *list;
	while (temp->next)
	{
		if (temp->next && temp->next->type == 0)
		{
			pipes -= 1;
			if (pipes == 0)
			{
				*right = temp->next->next;
				temp->next = NULL;
				break ;
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
	*right = temp->next;
	temp->next = NULL;
}

void	create_tree(tree *ast, token *list, int pipes)
{
	token *left;
	token *right;

	left = list;
	right = NULL;
	if (ast->type == 1 && pipes == 0)
	{
		ast->type = 2;
	}
	else if (ast->type == 1 && pipes != 0)
	{
		split_list(&list, &right, pipes);
		ast->left = create_node(list, 1);
		ast->right = create_node(right, 2);
		pipes -= 1;
		create_tree(ast->left, list, pipes);
		create_tree(ast->right, right, 0);
	}
	if (ast->type == 2)
	{
		if (list_len(ast->current) == 1)
		{
			ast->type = 4;
			return ;
		}
		else
		{
			split(&(ast->current), &right);
			ast->left = create_node(ast->current, 4);
			ast->right = create_node(right, 2);
			create_tree(ast->right, right, 0);
		}
	}
}

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

void     execute_tree(tree *tr, ev *eval)
{
	int fd[2];
    if (tr == NULL)
        return ;
    if (tr->type == 2)
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

void	action(char *cmd)
{
	token *list;
	tree *ast;
	int pipes;

	list = create_list(cmd);
	pipes = count_pipes(list);
	ast = (tree *)malloc(sizeof(tree) * 1);
	ast->current = list;
	ast->type = 1;
	create_tree(ast, list, pipes);
	ev *eval;
    eval = (ev *)malloc(sizeof(ev) * 1);
    eval->args=0;
    eval->cur = 0;
    eval->argv =NULL;
	eval->in = 0;
	eval->out = 1;
	eval->pipes = 2;
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