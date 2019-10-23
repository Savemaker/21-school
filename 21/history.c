//
// Created by Екатерина on 2019-10-03.
//

#include "minishell.h"



int ft_check_char(char *str, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
	i++;
	}
	return (count);
}




void	char_enter_nextline(char *buf, t_readline *input)
{
	char	*residue;
	int		pos;
	int		bufsize;

	bufsize = (int)ft_strlen(buf);
	if (input->size < MAXLINE - bufsize)
	{
		pos = input->y * input->maxwidth + input->x - input->prompt_end;
		residue = ft_strsub(input->line, (unsigned)pos, (size_t)input->size - pos);
		ft_bzero(input->line + pos, (size_t)MAXLINE - pos);
		input->line = ft_strcat(input->line, buf);
		input->line = ft_strcat(input->line, residue);
		clear_visible_line(input);
		ft_putstr(input->line);
		input->size += bufsize;
		goto_start(input);

//		goto_lastsymb(input);

		int lastwlen;
		lastwlen = 0;

		while (*buf++ != '\n')
		{
			lastwlen++;
		}

		while (lastwlen-- > 0)
			cursor_right(input);

		int n;
		n = ft_check_char(buf, '\n') + 1;
		while (n--)
		{
			cursor_up(input);
			TUP;
		}

		free(residue);
	}
	else
		TBELL;
}




void scroll_his_back(t_readline *input, t_history *history)//up
{
	if (history->cmnds && history->index > 0)
	{
		clear_input(input);
		char_enter(history->cmnds[history->index - 1], input);
		history->index--;
	}
	else
		TBELL;
}

void scroll_his_forward(t_readline *input, t_history *history)//down
{
	int tabsize;

	tabsize = str_quantity(history->cmnds);
	if (history->cmnds && history->index < tabsize - 1)
	{



		clear_input(input);
		char_enter(history->cmnds[history->index + 1], input);
		history->index++;
	}
	else
		TBELL;
}

int ft_nbrlen(int nb)
{
	int i;

	i = 1;
	if (nb == 0)
		return (i);
	while (nb / 10 > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}


int display_history(char **cmnd)
{
	int num;
	int i;
	int argc;
	int space = 0;
	int i_len;

	argc = str_quantity(cmnd);
	ft_putnbr(argc);

	if (g_shell->history->index >= HISTFILESIZE)
		i = g_shell->history->index - HISTFILESIZE;
	else
		i = 0;

	if (argc > 2)
	{
		ft_putstr_fd("usage: history [value]\n", STDOUT_FILENO);
		return (1);
	}
	if (argc > 1)
	{
		if ((num = ft_atoi(cmnd[1])) == 0 || num > g_shell->history->index)
		{
			ft_putstr_fd("history: invalid value\n", STDOUT_FILENO);
			return (1);
		}
		else
			i = g_shell->history->index - num;
	}
	int maxlen;
	maxlen = ft_nbrlen(g_shell->history->index);
	while (g_shell->history->cmnds[i])
	{
		i_len = ft_nbrlen(i + 1);
		space = maxlen - i_len + 1;


		ft_putstr_fd(UWHITE, STDOUT_FILENO);
		ft_putnbr_fd(i + 1, STDOUT_FILENO);
		ft_putstr_fd(RESET, STDOUT_FILENO);



		while (space--)
			ft_putstr_fd(" ", STDOUT_FILENO);

		ft_putstr_fd(g_shell->history->cmnds[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}

	return (1);
}

char *get_hiscmnd(char *line, t_history *history)
{
	int		tabsize;

	if (!history->cmnds)
		return (NULL);
	tabsize = str_quantity(history->cmnds);
	while (tabsize--)
	{
		if (ft_strstr(history->cmnds[tabsize], line))
			return (ft_strdup(history->cmnds[tabsize]));
	}
	return (NULL);
}

int display_his_prompt()
{
	char *prompt;
	prompt = "history search> " ;
	ft_putstr_fd(BWHITE, STDOUT_FILENO);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	return ((int)ft_strlen(prompt));
}

void		his_search()
{
	char	*line;
	int prompt_sz;
	char	*cmnd;

	set_input_tmode();


	int up;
	up = g_shell->input->y;
	while (up-- > 0)
	{
		tputs(tgetstr("ce", NULL), 1, &ft_putchar_int);
		TUP;
	}
	ft_putchar('\n');
	prompt_sz = display_his_prompt();
	ft_bzero(g_shell->input->line, MAXLINE);
	g_shell->input = init_readline(prompt_sz);
	readline_cmnd(&line, prompt_sz);
	if (!ft_strcmp(line, "\n"))
	{
		ft_putchar('\n');
		g_shell->inputmode = HISTORY_INPUT_STOP;

		reset_input_tmode();
		return;
	}
	if ((cmnd = get_hiscmnd(line, g_shell->history)))
	{
		goto_start(g_shell->input);
		tputs(tgetstr("ce", NULL), 1, &ft_putchar_int);
		ft_strcpy(g_shell->input->line, cmnd);
		ft_strcat(cmnd, "\n");
		ft_putstr_fd(cmnd, STDOUT_FILENO);
		free (cmnd);
	}
	else
	{
		ft_strcpy(g_shell->input->line, line);
		goto_start(g_shell->input);
		tputs(tgetstr("ce", NULL), 1, &ft_putchar_int);
		ft_putstr_fd("no matches found\n", STDOUT_FILENO);
		TBELL;
	}
	g_shell->inputmode = HISTORY_INPUT_STOP; //cmnd executes immediately
//	g_shell->input->mode = HISTORY_INPUT;
	reset_input_tmode();
}