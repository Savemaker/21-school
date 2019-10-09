/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:01:51 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/09 16:02:17 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

void	free_token_list(t_token **list)
{
	t_token *cur;
	t_token *temp;

	cur = *list;
	while (cur != NULL)
	{
		free(cur->buf);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	*list = NULL;
}

void	free_hash_list(t_hash_node **list)
{
	t_hash_node *cur;
	t_hash_node *temp;

	cur = *list;
	while (cur != NULL)
	{
		free(cur->name);
		free(cur->path);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
}

void	free_copy_envp(char ***envp)
{
	int		p;
	char	**ref;

	ref = *envp;
	p = count_pointers(ref);
	free_parse(ref, p);
	envp = NULL;
}

void	free_tree(t_tree *tree)
{
	t_tree *right;
	t_tree *left;

	if (tree == NULL)
		return ;
	if (tree->type == 3)
	{
		if (tree->argv != NULL)
			free_parse(tree->argv, tree->args);
	}
	if (tree->type == 4 || tree->type == 5)
	{
		if (tree->current)
			free_token_list(&(tree->current));
	}
	right = tree->right;
	left = tree->left;
	free(tree);
	free_tree(left);
	free_tree(right);
}

void	free_hash_table(t_hash **table)
{
	int		i;
	t_hash	*cur_hash;

	i = 0;
	cur_hash = *table;
	while (i < cur_hash->quant)
	{
		free_hash_list(&(cur_hash->node[i]));
		i++;
	}
	free(cur_hash->node);
	free(cur_hash);
	*table = NULL;
}
