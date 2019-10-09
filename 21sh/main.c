/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/09 15:38:35 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

char	*sub_line_stuf(char *parse)
{
	char *res;

	if (ft_strlen(parse) == 1)
		res = ft_strdup("$");
	else
		res = ft_strdup(" ");
	return (res);
}

char	*sub_line_dollar(char *parse)
{
	char *res;
	char *seek;

	seek = ft_getenv(&parse[1], g_my_env);
	if (seek == NULL)
	{
		res = sub_line_stuf(parse);
		free(parse);
	}
	else
	{
		res = ft_strdup(seek);
		free(parse);
	}
	return (res);
}

char	*sub_line(char *parse, char **envp)
{
	char *seek;
	char *res;

	res = parse;
	if (parse[0] == '$')
		res = sub_line_dollar(parse);
	else if (parse[0] == '~')
	{
		seek = ft_getenv("HOME", envp);
		if (seek == NULL)
			res = NULL;
		else
		{
			res = ft_strjoin(seek, &parse[1]);
			free(parse);
		}
	}
	return (res);
}

int		semantics_semicolomn(t_token *list)
{
	if (list->type == 2)
	{
		if (list->next && list->next->type == 2)
		{
			ft_putendl("Parse error near ;;");
			return (1);
		}
	}
	return (0);
}

int		semantics(t_token *list)
{
	int first;

	first = 1;
	if (list && list->next == NULL)
	{
		if (list->type == 2)
			return (1);
	}
	while (list)
	{
		if (list->type != 1)
			first = 0;
		if (semantics_semicolomn(list))
			return (1);
		if (list->type == 1)
		{
			if ((list->next && list->next->type == 1) || first == 1)
			{
				ft_putendl("Parse error near |");
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

void	update_lexer(t_token **list)
{
	t_token *temp;
	t_token *head;

	head = *list;
	if (head->type == 2 && head->next && head->next->type != 2)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->buf);
		free(temp);
	}
	head = *list;
	while (head)
	{
		if (head->next && head->next->type == 8)
		{
			head->type = 9;
			if (head->next->next)
				head->next->next->type = 9;
		}
		head->buf = sub_line(head->buf, g_my_env);
		head = head->next;
	}
}

void	action(char *cmd)
{
	t_token	*list;
	t_tree	*ast;

	list = lexer(cmd);
	update_lexer(&list);
	if (semantics(list) == 1)
	{
		free_token_list(&list);
		return ;
	}
	ast = create_node(list, 2, NULL);
	create_tree(ast);
	execute_tree(ast);
	free_tree(ast);
}

int		main(int argc, char **argv, char **envp)
{
	char *cmd;

	(void)argv;
	if (argc == 1)
	{
		g_my_env = create_env_copy(envp, count_pointers(envp));
		g_table = create_table();
		while (1)
		{
			cmd = readline("-> ");
			action(cmd);
			free(cmd);
		}
	}
	return (0);
}
