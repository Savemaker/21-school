#include "21sh.h"

char	*create_path(char *name, char *path)
{
	char *new;
	char *res;

	if (ft_strcmp(path, "/") != 0)
		new = ft_strjoin(path, "/");
	else
		new = path;
	res = ft_strjoin(new, name);
	if (ft_strcmp(path, "/") != 0)
		free(new);
	return (res);
}

char	*get_cmd(char *cmd, unsigned int hash)
{
	hash_node *node;

	if (table->node[hash] == NULL)
		return (NULL);
	else
	{
		node = table->node[hash];
		while (node)
		{
			if (ft_strcmp(cmd, node->name) == 0)
				return (create_path(node->name, node->path));
			node = node->next;
		}
	}
	return (NULL);
}

int		argv_checker(char **argv)
{
	unsigned int hash;
	char *upd;

	hash = hashing(argv[0], table->quant);
	upd = get_cmd(argv[0], hash);
	if (upd == NULL)
	{
		ft_putendl("Command not found");
		return (0);
	}
	else
	{
		free(argv[0]);
		argv[0] = ft_strdup(upd);
		return (1);
	}
}

void	execute_start(tree *ast, int in, int out)
{
	pid_t p;
	tree *redirs;
	int flag;

	flag = 1;
	redirs = get_redirs_node(ast);
	in = get_redirections(ast, in, 4, 0);
	out = get_redirections(ast, out, 3, 1);
	if (argv_checker(ast->argv) == 1)
	{
		p = fork();
		if (p == 0)
		{
			dup2(in, 0);
			dup2(out, 1);
			close(in);
			if (redirs)
				aggregation_order(redirs->current, out);
			execve(ast->argv[0], ast->argv, my_env);
		}
		else
		{
				// waitpid(p, NULL, 0);
			close(out);
		}
	}
}

void	execute_right(tree *ast, int in, int out, int temp)
{
	pid_t	p;
	tree *redirs;

	redirs = get_redirs_node(ast);
	temp = get_redirections(ast, temp, 4, 1);
	out = get_redirections(ast, out, 3, 1);
	create_argv(ast);
	if (argv_checker(ast->argv) == 1)
	{
		if (check_builtin(ast) == 0)
		{
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
				if (redirs)
					aggregation_order(redirs->current, out);
				execve(ast->argv[0], ast->argv, my_env);
			}
			else
			{
				waitpid(p, NULL, 0);
				close(out);
				close(temp);
			}
		}
		else
		{
			execute_builtin(ast);
			close(out);
		}
	}
}

void	simple_execution(tree *ast)
{
	pid_t	p;
	int		in;
	int		out;
	tree *redirs;

	in = 0;
	out = 1;
	out = get_redirections(ast, out, 3, 0);
	in = get_redirections(ast, in, 4, 0);
	redirs = get_redirs_node(ast);
	create_argv(ast);
	if (argv_checker(ast->argv) == 1)
	{
		if (check_builtin(ast) == 0)
		{
			p = fork();
			if (p == 0)
			{
				dup2(in, 0);
				dup2(out, 1);
				if (redirs)
					aggregation_order(redirs->current, out);
				execve(ast->argv[0], ast->argv, my_env);
			}
			else
			{
				waitpid(p, NULL, 0);
			}
		}
		else
			execute_builtin(ast);
	}
}

void	execute_tree_type_one(tree *ast)
{
	int fd[2];
	int start;
	int tmp_fd;
	int temp;

	start = 0;
	while (ast->left->type == 1)
		ast = ast->left;
	while (ast != NULL && ast->type == 1)
	{
		pipe(fd);
		if (start == 0)
		{
			create_argv(ast->left);
			if (check_builtin(ast->left))
			{
				temp = dup(1);
				dup2(fd[1], 1);
				execute_builtin(ast->left);
				dup2(temp, 1);
				close(temp);
				close(fd[1]);
				start = 1;
				tmp_fd = fd[0];
				pipe(fd);
			}
			else
			{
				execute_start(ast->left, fd[0], fd[1]);
				start = 1;
				tmp_fd = fd[0];
				pipe(fd);
			}
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