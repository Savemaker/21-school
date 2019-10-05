#include "21sh.h"

char	**ft_echo(char **parse, char **envp)
{
	int i;

	i = 1;
	while (parse[i])
	{
		if (ft_strcmp(parse[i], " ") == 0)
		{
			i++;
			continue;
		}
		ft_putstr(parse[i]);
		if (parse[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (envp);
}

char	**ft_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putendl(envp[i]);
		i++;
	}
	return (envp);
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
	p = fork();
	if (p == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		close(in);
		create_argv(ast);
		if (redirs)
			aggregation_order(redirs->current, out);
		execve(ast->argv[0], ast->argv, ast->envp);
	}
	else
	{
			// waitpid(p, NULL, 0);
		close(out);
	}
}

void	execute_right(tree *ast, int in, int out, int temp)
{
	pid_t	p;
	tree *redirs;

	redirs = get_redirs_node(ast);
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
		if (redirs)
			aggregation_order(redirs->current, out);
		create_argv(ast);
		execve(ast->argv[0], ast->argv, ast->envp);
	}
	else
	{
		waitpid(p, NULL, 0);
		close(out);
		close(temp);
	}
}

void	copy_index(char **ress, char *name, char *value)
{
	int		i;
	int		j;
	char	*res;

	res = *ress;
	i = 0;
	j = 0;
	while (name[i])
	{
		res[i] = name[i];
		i++;
	}
	res[i++] = '=';
	j = 0;
	while (value[j])
	{
		res[i] = value[j];
		i++;
		j++;
	}
	res[i] = '\0';
}

int		test_getenv(const char *name, char *ret)
{
	size_t i;

	i = 0;
	while (ret[i] && ret[i] != '=')
		i++;
	if (ft_strlen(name) != i)
		return (0);
	return (1);
}

int		ft_getenv_index(const char *name, char **envp)
{
	int		i;
	char	*ret;
	int		len;

	i = 0;
	len = ft_strlen(name) + 1;
	while (envp[i])
	{
		ret = ft_strstr(envp[i], name);
		if (ret != NULL)
		{
			if (test_getenv(name, envp[i]) == 1)
				return (i);
		}
		i++;
	}
	return (-1);
}



void	copy_to_realloc(char **envp, char **res, char *name, char *value)
{
	int index;
	int i;
	int j;

	index = ft_getenv_index(name, envp);
	i = 0;
	j = 0;
	while (envp[i])
	{
		j = 0;
		if (index != i)
		{
			while (envp[i][j] != '\0')
			{
				res[i][j] = envp[i][j];
				j++;
			}
			res[i][j] = '\0';
		}
		if (index == i)
			copy_index(&res[i], name, value);
		i++;
	}
	if (index == -1)
		copy_index(&res[i], name, value);
}

char	*malloc_line(char *name, char *value)
{
	char	*res;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	res = (char *)malloc(sizeof(char) * (name_len + value_len + 2));
	if (res == NULL)
		return (NULL);
	return (res);
}

char	**realloc_envp(int pointers, char *name, char *value, char **envp)
{
	char	**res;
	int		index;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (pointers + 1));
	index = ft_getenv_index(name, envp);
	if (index == -1)
		--pointers;
	while (i < pointers)
	{
		if (i == index)
			res[i] = malloc_line(name, value);
		else
			res[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		i++;
	}
	if (index == -1)
		res[i++] = malloc_line(name, value);
	res[i] = NULL;
	copy_to_realloc(envp, res, name, value);
	return (res);
}

void	free_parse(char **parse, int w)
{
	int i;

	i = 0;
	w++;
	while (i < w)
	{
		free(parse[i]);
		i++;
	}
	free(parse);
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

char	**ft_setenv(char **parse, char **envp)
{
	char	**new_env;
	int		p;

	new_env = NULL;
	p = count_pointers(parse);
	if (p == 3 && parse[1] != NULL && parse[2] != NULL)
	{
		p = count_pointers(envp);
		if (getenv(parse[1]) == NULL)
			p++;
		new_env = realloc_envp(p, parse[1], parse[2], envp);
		free_copy_envp(&envp);
		return (new_env);
	}
	return (envp);
}

char	**update_pwd(char **envp, char *name, char *oldpath)
{
	char **parse;
	char **old;

	old = (char **)malloc(sizeof(char *) * 4);
	old[0] = ft_strdup("setenv");
	old[1] = ft_strdup("OLDPWD");
	old[2] = ft_strdup(oldpath);
	old[3] = NULL;
	parse = (char **)malloc(sizeof(char *) * 4);
	parse[0] = ft_strdup("setenv");
	parse[1] = ft_strdup("PWD");
	parse[2] = ft_strdup(name);
	parse[3] = NULL;
	envp = ft_setenv(old, envp);
	envp = ft_setenv(parse, envp);
	free_parse(parse, 3);
	free_parse(old, 3);
	return (envp);
}

void	print_no_such(char *s)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(s);
}

char 	**ft_cd_stuf(char **parse, char **envp)
{
	int		res;
	char	*tmp;
	char	buf[2048];
	char	old_buf[2048];

	tmp = getcwd(old_buf, 2048);
	if (ft_strcmp(parse[1], " ") == 0)
		res = chdir(getenv("HOME"));
	else if (ft_strcmp(parse[1], "-") == 0)
		res = chdir(getenv("OLDPWD"));
	else
		res = chdir(parse[1]);
	if (res == -1)
	{
		if (access(parse[1], F_OK) == 0)
		{
			ft_putstr("cd: permission denied: ");
			ft_putendl(parse[1]);
		}
		else
			print_no_such(parse[1]);
	}
	// if (res == 0)
	// 	envp = update_pwd(envp, getcwd(buf, 2048), tmp);
	return (envp);
}

char **ft_cd(char **parse, char **envp)
{
	int		i;
	char	*home;
	char	tmp[2048];

	home = getenv("HOME");
	i = 0;
	while (parse[i])
		i++;
	if (i > 2)
	{
		ft_putendl("cd: too many arguments");
		return (envp);
	}
	if (--i == 0)
	{
		if (home != NULL)
		{
			getcwd(tmp, 2048);
			// if (chdir(home) == 0)
			// 	envp = update_pwd(envp, home, tmp);
		}
	}
	if (i == 1)
		envp = ft_cd_stuf(parse, envp);
	return (envp);
}

int		check_builtin(tree *ast)
{
	if (ft_strcmp(ast->argv[0], "cd") == 0)
	{
		ast->envp = ft_cd(ast->argv, ast->envp);
		return (1);
	}
	if (ft_strcmp(ast->argv[0], "env") == 0)
	{
		ast->envp = ft_env(ast->envp);
		return (1);
	}
	if (ft_strcmp(ast->argv[0], "echo") == 0)
	{
		ast->envp = ft_echo(ast->argv, ast->envp);
		return (1);
	}
	return (0);
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
	if (check_builtin(ast) == 0)
	{
		p = fork();
		if (p == 0)
		{
			dup2(in, 0);
			dup2(out, 1);
			if (redirs)
				aggregation_order(redirs->current, out);
			execve(ast->argv[0], ast->argv, ast->envp);
		}
		else
		{
			waitpid(p, NULL, 0);
		}
	}
}

void	execute_tree_type_one(tree *ast)
{
	int fd[2];
	int start;
	int tmp_fd;
	// int temp;

	start = 0;
	while (ast->left->type == 1)
		ast = ast->left;
	while (ast != NULL && ast->type == 1)
	{
		pipe(fd);
		if (start == 0)
		{
			// temp = dup(1);
			
			// dup2(fd[1], 1);
			// ft_putstr("yeeeeee");
			// dup2(temp, 1);
			// close(temp);
			// close(fd[1]);
			
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