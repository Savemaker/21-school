//
// Created by Екатерина on 2019-10-03.
//

#include "minishell.h"

int display_user(void)
{
	char	*user;
	int len;
//	if (!g_shell.error)
	ft_putstr_fd(BGREEN, STDOUT_FILENO);
//	else
//		ft_putstr_fd(BRED, STDOUT_FILENO);
	if ((user = ft_getenv("USER", g_my_env)))
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
		val = ft_getenv("HOME", g_my_env);
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
//	ft_putstr_fd("$ ", STDOUT_FILENO);
	ft_putstr_fd(" ➜  ", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	return (len + 4);
}



//
//int	prompt_user_host(char *ps1)
//{
//	char host[MAXHOSTNAME];
//	char clear_host[MAXHOSTNAME];
//	char *user;
//	int	i;
//
//	int len;
//	len = 0;
//
//	if (!ft_strncmp(ps1, "\\u", 2)) //current user
//	{
//		if ((user = ft_getenv("USER", g_my_env)))
//		{
//			ft_putstr_fd(ft_strcat(user, " "), STDOUT_FILENO);
//			len = (int)ft_strlen(user);
//		}
//	}
//	gethostname(host, MAXHOSTNAME);
//	if (!ft_strncmp(ps1, "\\H", 2)) //hostname
//	{
//		ft_putstr_fd(ft_strcat(host, " "), STDOUT_FILENO);
//		len = (int)ft_strlen(host);
//	}
//	else if (!ft_strncmp(ps1, "\\h", 2))//up to the first .
//	{
//		i = 0;
//		while (host[i] && host[i] != '.')
//		{
//			clear_host[i] = host[i];
//			i++;
//		}
//		ft_putstr_fd(ft_strcat(clear_host, " "), STDOUT_FILENO);
//		len = (int)ft_strlen(host);
//	}
//	return (len);
//}



//int display_dir(int tilde) //разобраться
//{
//	char	*cwd;
//	char 	*newcwd;
//	char 	*val;
//	int 	len;
//	char *short_cwd;
//
//	short_cwd = ft_memalloc(MAXLINE);
//	len = 0;
//	val = ft_getenv("HOME", g_my_env);
//	if ((cwd = getcwd(NULL, 0)))
//	{
//		if (tilde && !ft_strncmp(cwd, val, ft_strlen(val)))
//		{
//			newcwd = ft_strjoin("~", cwd + ft_strlen(val));
//			ft_putstr(newcwd);
//			len = (int)ft_strlen(newcwd);
//			free(newcwd);
//		}
//		if (!tilde)
//		{
//			if (!ft_strcmp(cwd, val))
//				short_cwd = ft_strcpy(short_cwd, "~");
//			else
//				short_cwd = ft_strrchr(cwd, '/') + 1;
//			ft_putstr_fd(short_cwd, STDOUT_FILENO);
//			len = (int)ft_strlen(short_cwd);
//		}
//
//		if (!ft_strncmp(cwd, "/", 1))
//		{
//			ft_putstr_fd(cwd, STDOUT_FILENO);
//			len = (int)ft_strlen(cwd);
//		}
//
//	}
//	free(cwd);
//	return (len);
//}



//int	prompt_his(char *ps1, int his_size)
//{
//	if (!ft_strncmp(ps1, "\\W", 2))
//		return (display_dir(0));
//
//	if (!ft_strncmp(ps1, "\\w", 2))
//		return (display_dir(1));
//	if (!ft_strncmp(ps1, "\\$", 2))
//	{
//		if (ft_getenv("USER", g_my_env) && !ft_strcmp(ft_getenv("USER", g_my_env),"root"))
//			ft_putchar_fd('#', STDOUT_FILENO);
//		else
//			ft_putchar_fd('$', STDOUT_FILENO);
//		return (1);
//	}
////	else if (!ft_strncmp(ps1 , "\\#", 2))
////	{
////		ft_putnbr_fd(his_size, STDOUT_FILENO);
////		return (ft_nbrlen(his_size));
////	}
//	return (0);
//}



//
//int	get_time_format(char *ps1, struct tm *local)
//{
//	char	buf[MAXLINE];
//
//	if (!ft_strncmp(ps1, "\\A", 2))
//		strftime(buf, MAXLINE, "%H:%M", local);
//	else if (!ft_strncmp(ps1, "\\t", 2))
//		strftime(buf, MAXLINE, "%H:%M:%S", local);
//	else if (!ft_strncmp(ps1 , "\\T", 2))
//		strftime(buf, MAXLINE, "%I:%M:%S", local);
//	else if (!ft_strncmp(ps1, "\\@", 2))
//		strftime(buf, MAXLINE, "%I:%M", local);
//	else if (!ft_strncmp(ps1, "\\d", 2))
//		strftime(buf, MAXLINE, "%a %b %d", local);
//	ft_putstr_fd(buf, STDOUT_FILENO);
//	return ((int)ft_strlen(buf));
//}
//
//int	prompt_time(char *ps1)
//{
//	time_t	t;
//
//	time(&t);
//	if (t == -1)
//		perror_cmnd(SHELL_NAME, NULL, TIMEERR);
//	return (get_time_format(ps1, localtime(&t)));
//}
//
//int display_custom_prompt(char *ps1)
//{
//	int len;
//
//
//	len = 0;
//	int oldlen = 0;
//	while (*ps1 )
//	{
////			len += prompt_user_host(ps1);
////			if (len > oldlen)
////			{
////				ps1 += 2;
////				oldlen = len;
////			}
////
////			len += prompt_time(ps1);
////			if (len > oldlen)
////			{
////				ps1 += 2;
////				oldlen = len;
////			}
//
//			len += prompt_his(ps1, str_quantity(g_shell->history->cmnds));
//			if (len > oldlen)
//			{
//				ps1 += 2;
//				oldlen = len;
//			}
//
////			if (j == i)
////				j = prompt_colour_name(ps1, i, SHELL_NAME);
////			ps1 = ft_strchr(ps1, '\\');
//
//
////		}
////		if (j == i)
////			ft_putchar_fd(ps1[i], STDIN_FILENO);
////		else
//
//		if (len == 0)
//			break;
//	}
//	ft_putchar_fd(' ', STDOUT_FILENO);
//	return (len + 1);
//}








//int	init_keypad_transmitmode(void)
//{
//	if (tgetstr("ks", NULL))
//		tputs(tgetstr("ks", NULL), 1, &ft_putchar_int);
//	else
//	{
//		ft_putchar_fd('\n', STDOUT_FILENO);
//		perror_cmnd(SHELLNAME, "no correct capabilities", 0);
//		return (0);
//	}
//	return (1);
//}

int display_prompt(void)
{
	int len;
//	char *custom_prompt;

	set_input_tmode();

	len = 0;
//	if ((custom_prompt = ft_getenv("PS1", g_my_env)))
//		len = display_custom_prompt(custom_prompt);
//	if (!len)
		len = display_ordinary_prompt();
	reset_input_tmode();
	return (len);
}