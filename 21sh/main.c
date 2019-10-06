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
