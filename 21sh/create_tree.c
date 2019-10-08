#include "21sh.h"

void	split(t_token **list, t_token **right)
{
	t_token *temp;

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

t_tree *create_node(t_token *list, int type, t_tree *parent)
{
	t_tree *res;

	res = (t_tree *)malloc(sizeof(t_tree) * 1);
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

void	split_list(t_token **list, t_token **right, t_tree *ast, int type)
{
	t_token *temp;

	temp = *list;
	if (temp == NULL)
		return ;
	while (temp->next)
	{
		if (temp->next && temp->next->type == type)
		{
				ast->t_pipes -= 1;
				if (ast->t_pipes == 0)
				{
					*right = temp->next->next;
					free(temp->next->buf);
					free(temp->next);
					temp->next = NULL;
					break ;
				}
		}
		temp = temp->next;
	}
}

void	split_semicolomn(t_token **left, t_token **right)
{
	t_token *list;

	list = *left;
	if (list == NULL)
		return ;
	while (list->next && list->next->type != 2)
		list = list->next;
	if (list->next && list->next->next)
	{
		*right = list->next->next;
		free(list->next->buf);
		free(list->next);
	}
	else
		*right = NULL;
	list->next = NULL;
}

int		count_token_types(t_token *list, int type)
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

void	create_tree(t_tree *ast)
{
	t_token *left;
	t_token *right;

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
		if (ast->current->type >= 3 && ast->current->type <= 9)
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