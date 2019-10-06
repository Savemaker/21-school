#include "21sh.h" //segfault

void update_pwd(char *name, char *oldpath)
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
	ft_setenv(old, my_env);
	ft_setenv(parse, my_env);
	free_parse(parse, 3);
	free_parse(old, 3);
}

void	print_no_such(char *s)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(s);
}

void	ft_cd_stuf(char **parse)
{
	int		res;
	char	*tmp;
	char	buf[2048];
	char	old_buf[2048];

	tmp = getcwd(old_buf, 2048);
	if (ft_strcmp(parse[1], " ") == 0)
		res = chdir(ft_getenv("HOME", my_env));
	else if (ft_strcmp(parse[1], "-") == 0)
		res = chdir(ft_getenv("OLDPWD", my_env));
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
	if (res == 0)
		update_pwd(getcwd(buf, 2048), tmp);
}

int     ft_cd(char **parse)
{
	int		i;
	char	*home;
	char	tmp[2048];

	home = ft_getenv("HOME", my_env);
	i = 0;
	while (parse[i])
		i++;
	if (i > 2)
	{
		ft_putendl("cd: too many arguments");
		return (1);
	}
	if (--i == 0)
	{
		if (home != NULL)
		{
			getcwd(tmp, 2048);
			if (chdir(home) == 0)
				update_pwd(home, tmp);
		}
	}
	if (i == 1)
		ft_cd_stuf(parse);
	return (1);
}
