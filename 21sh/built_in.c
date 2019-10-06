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
    if (ft_strcmp(ast->argv[0], "echo") == 0)
        return (ft_echo(ast->argv));
    if (ft_strcmp(ast->argv[0], "env") == 0)
        return (ft_env(my_env));
    if (ft_strcmp(ast->argv[0], "exit") == 0)
        return (ft_exit(my_env));
    if (ft_strcmp(ast->argv[0], "setenv") == 0)
        return (ft_setenv(ast->argv, my_env));
    if (ft_strcmp(ast->argv[0], "unsetenv") == 0)
        return (ft_unsetenv(ast->argv, my_env));
    if (ft_strcmp(ast->argv[0], "cd") == 0)
        return (ft_cd(ast->argv));
    return (0);
}