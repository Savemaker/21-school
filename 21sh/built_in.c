#include "21sh.h"

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

int    ft_echo(char **parse)
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
	return (1);
}

int     ft_env(char **envp)
{
    int i;

	i = 0;
	while (envp[i])
	{
		ft_putendl(envp[i]);
		i++;
	}
	return (1);
}

int ft_exit(char **envp)
{
	free_copy_envp(&envp);
    exit(0);
	return (1);
}

int     check_builtin(tree *ast)
{
    if (ft_strcmp(ast->argv[0], "echo") == 0)
        return (1);
    if (ft_strcmp(ast->argv[0], "env") == 0)
        return (1);
    if (ft_strcmp(ast->argv[0], "exit") == 0)
        return (1);
    if (ft_strcmp(ast->argv[0], "setenv") == 0)
        return (1);
    if (ft_strcmp(ast->argv[0], "unsetenv") == 0)
        return (1);
    if (ft_strcmp(ast->argv[0], "cd") == 0)
        return (1);
    return (0);
}

int     execute_builtin(tree *ast)
{
	tree *redirs;
	int fd;
	int res;
	int save;

	res = 0;
	fd = 1;
	redirs = get_redirs_node(ast);
	if (redirs)
		aggregation_order(redirs->current, 1);
	fd = get_redirections(ast, fd, 3, 0);
	save = dup(1);
	dup2(fd, 1);
    if (ft_strcmp(ast->argv[0], "echo") == 0)
        res = ft_echo(ast->argv);
    if (ft_strcmp(ast->argv[0], "env") == 0)
        res = ft_env(my_env);
    if (ft_strcmp(ast->argv[0], "exit") == 0)
        res = ft_exit(my_env);
    if (ft_strcmp(ast->argv[0], "setenv") == 0)
       res = ft_setenv(ast->argv, my_env);
    if (ft_strcmp(ast->argv[0], "unsetenv") == 0)
        res = ft_unsetenv(ast->argv, my_env);
    if (ft_strcmp(ast->argv[0], "cd") == 0)
        res = ft_cd(ast->argv);
	close(fd);
	dup2(save, 1);
	close(save);
    return (res);
}