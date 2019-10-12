//
// Created by Екатерина on 2019-10-11.
//

#include "minishell.h"




int	prompt_user_host(unsigned int parsed)
{
	char host[MAXHOSTNAME];
	char clear_host[MAXHOSTNAME];
	char *user;
	int	i;


	int len = 0;

	if (check_parsed(parsed, 'u')) //current user
	{
		if ((user = ft_getenv("USER")))
		{

			ft_putstr(user);
			ft_putstr(" ");
			len += (int)ft_strlen(user) + 1;
		}
	}
	gethostname(host, MAXHOSTNAME);
	if (check_parsed(parsed, 'H')) //hostname
	{
		ft_putstr_fd(host, STDOUT_FILENO);
		ft_putstr(" ");
		len += (int)ft_strlen(host) + 1;

	}
	else if (check_parsed(parsed, 'h'))//up to the first .
	{
		i = 0;
		while (host[i] && host[i] != '.')
		{
			clear_host[i] = host[i];
			i++;
		}
		ft_putstr_fd(clear_host, STDOUT_FILENO);
		ft_putstr(" ");
		len += (int)ft_strlen(clear_host) + 1;

	}
	return (len);
}

int display_dir(int tilde)
{
	char	*cwd;
	char 	*newcwd;
	char 	*val;
	int 	len;
	char *short_cwd;

	short_cwd = ft_memalloc(MAXLINE);
	len = 0;
	val = ft_getenv("HOME");
	if ((cwd = getcwd(NULL, 0)))
	{

		if (tilde)
		{
			if (!ft_strncmp(cwd, val, ft_strlen(val)))
			{
				newcwd = ft_strjoin("~", cwd + ft_strlen(val));
				ft_putstr(newcwd);
				ft_putstr_fd(" ", STDOUT_FILENO);
				len = (int)ft_strlen(newcwd) + 1;
				free(newcwd);
			}
			else
			{
				ft_putstr_fd(cwd, STDOUT_FILENO);
				ft_putstr_fd(" ", STDOUT_FILENO);
				len = (int)ft_strlen(cwd) + 1;
			}
		}
		if (!tilde)
		{
			ft_putstr_fd(cwd, STDOUT_FILENO);
			ft_putstr_fd(" ", STDOUT_FILENO);
			len = (int)ft_strlen(cwd) + 1;
		}
	}
	free(cwd);
	return (len);
}



int	prompt_his(unsigned int parsed, int his_size)
{
	int len;

	len = 0;
	if (check_parsed(parsed, '#'))
	{
		ft_putnbr_fd(his_size, STDOUT_FILENO);
		len += ft_nbrlen(his_size);
	}
	return (len);
}

int	prompt_rights(unsigned int parsed)
{
	int len;

	len = 0;
	if (check_parsed(parsed, '$'))
	{
		if (ft_getenv("USER") && !ft_strcmp(ft_getenv("USER"),"root"))
			ft_putchar_fd('#', STDOUT_FILENO);
		else
			ft_putchar_fd('$', STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		len = 2;
	}
	return (len);
}
int	prompt_path(unsigned int parsed)
{
	int len;

	len = 0;

	if (check_parsed(parsed, 'w'))
		len += display_dir(1);
	else if (check_parsed(parsed, 'W'))
		len += display_dir(0);
	return (len);
}



int	get_time_format(unsigned int parsed, struct tm *local)
{
	char	buf[MAXLINE];
	int len;

	len = 0;
	if (check_parsed(parsed, 'A'))
	{
		strftime(buf, MAXLINE, "%H:%M", local);
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		len += ft_strlen(buf) + 1;
	}
	if (check_parsed(parsed, 't'))
	{
		strftime(buf, MAXLINE, "%H:%M:%S", local);
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		len += ft_strlen(buf) + 1;

	}
	if (check_parsed(parsed, 'T'))
	{
		strftime(buf, MAXLINE, "%I:%M:%S", local);
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		len += ft_strlen(buf) + 1;
	}
	if (check_parsed(parsed, '@'))
	{
		strftime(buf, MAXLINE, "%I:%M", local);
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		len += ft_strlen(buf) + 1;
	}
	if (check_parsed(parsed, 'd'))
	{
		strftime(buf, MAXLINE, "%a %b %d", local);
		ft_putstr_fd(buf, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		len += ft_strlen(buf) + 1;
	}
	return (len);
}

int	prompt_time(unsigned int parsed)
{
	time_t	t;

	time(&t);
	if (t == -1)
		perror_cmnd(SHELLNAME, NULL, TIMEERR);
	return (get_time_format(parsed, localtime(&t)));
}

int display_custom_prompt(char *ps1)
{
	int len;
	unsigned int parsed_prompt;

	len = 0;
	parsed_prompt = parse_ps1(ps1);
	len += prompt_his(parsed_prompt, str_quantity(g_shell->history->cmnds));
	len += prompt_time(parsed_prompt);
	len += prompt_user_host(parsed_prompt);
	len += prompt_path(parsed_prompt);
	len += prompt_rights(parsed_prompt);
	return (len);
}