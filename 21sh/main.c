/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/07 17:38:03 by gbeqqo           ###   ########.fr       */
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

char	*sub_line(char *parse, char **envp)
{
	char *seek;
	char *res;

	res = parse;
	if (parse[0] == '$')
	{
		seek = ft_getenv(&parse[1], envp);
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
	}
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

int		semantics(token *list)
{
	if (list && list->next == NULL)
	{
		if (list->type == 2)
			return (1);
	}
	return (0);
}

void	update_lexer(token *list)
{
	while (list)
	{
		if (list->next && list->next->type == 8)
		{
			list->type = 9;
			if (list->next->next)
				list->next->next->type = 9;
		}
		list->buf = sub_line(list->buf, my_env);
		list = list->next;
	}
}

void	action(char *cmd)
{
	token *list;
	tree *ast;
	unsigned int i;
	i = 0;
	// ast = NULL;
	// (void)envp;
	list = lexer(cmd);
	update_lexer(list);
	if (semantics(list) == 1)
		return ;
	// while (list)
	// {
	// 	ft_putnbr(list->type);
	// 	list = list->next;
	// }
	ast = create_node(list, 2, NULL);
	create_tree(ast);
	execute_tree(ast);
}

int main(int argc, char **argv, char **envp)
{
	char *cmd;

	(void)argv;
	if (argc == 1)
	{
		my_env = create_env_copy(envp, count_pointers(envp));
		table = create_table();
		while (1)
		{
			cmd = readline("-> ");
			action(cmd);
		}
	}
}
