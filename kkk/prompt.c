//
// Created by Екатерина on 2019-10-03.
//

#include "minishell.h"

int display_user(void)
{
	char	*user;
	int len;

	ft_putstr_fd(BGREEN, STDOUT_FILENO);
	if ((user = ft_getenv("USER")))
	{
		ft_putstr_fd(user, STDOUT_FILENO);
		len = (int)ft_strlen(user);
	}
	else
	{
		ft_putstr_fd(SHELLNAME, STDOUT_FILENO);
		len = (int)ft_strlen(SHELLNAME);
	}
	return (len);
}

int display_host(void)
{
	char	host[MAXHOSTNAME];

	gethostname(host, MAXHOSTNAME);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(host, STDOUT_FILENO);
	return ((int)ft_strlen(host) + 1);
}

int display_cwd(void)
{
	char	*cwd;
	char 	*newcwd;
	char 	*val;
	int 	len;

	len = 0;
	if ((cwd = getcwd(NULL, 0)))
	{
		ft_putstr_fd(WHITE, STDOUT_FILENO);
		ft_putstr_fd(":", STDOUT_FILENO);
		ft_putstr_fd(BCYAN, STDOUT_FILENO);
		val = ft_getenv("HOME");
		if (!ft_strncmp(cwd, val, ft_strlen(val)))
		{
			newcwd = ft_strjoin("~", cwd + ft_strlen(val));
			ft_putstr(newcwd);
			len = (int)ft_strlen(newcwd);
			free(newcwd);
		}
		else
		{
			ft_putstr_fd(cwd, STDOUT_FILENO);
			len = (int)ft_strlen(cwd);
		}
	}
	free(cwd);
	return (len + 1);
}

int display_ordinary_prompt()
{
	int len;

	len = 0;
	len += display_user();
	len += display_host();
	len += display_cwd();
	if (!g_shell->error)
		ft_putstr_fd(BGREEN, STDOUT_FILENO);
	else
		ft_putstr_fd(BRED, STDOUT_FILENO);
	ft_putstr_fd(" ➜  ", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	return (len + 4);
}

int display_prompt(void)
{
	int len;
	char *custom_prompt;

	set_input_tmode();
	len = 0;
	if ((custom_prompt = ft_getenv("PS1")))
		len = display_custom_prompt(custom_prompt);
	if (!len)
		len = display_ordinary_prompt();
	reset_input_tmode();
	return (len);
}