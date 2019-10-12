//
// Created by Екатерина on 2019-10-03.
//

#include "minishell.h"

int display_added_prompt(int  prompt_type)
{
	char *prompt;

	if (prompt_type == 1)
		prompt = "quote> ";
	else
		prompt = "dquote> ";
	ft_putstr_fd(BWHITE, STDOUT_FILENO);
	ft_putstr_fd(prompt, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	return ((int)ft_strlen(prompt));
}


int check_quote(char *line)
{

	char *stack;
	int q_count = 0;
	int dq_count = 0;
	int i = 0;

	stack = ft_memalloc(1);
	stack[0] = '0';
	while (line[i])
	{
		if (line[i] == 39)
		{
			if (stack[0] == '0')
				stack[0] = 39;
			q_count++;
		}
		else if (line[i] == 34)
		{
			if (stack[0] == '0')
				stack[0] = 34;
			dq_count++;
		}
		i++;
	}
	if (q_count % 2 && stack[0] == 39)
	{
		free(stack);
		return (1);
	}
	else if (dq_count % 2 && stack[0] == 34)
	{
		free(stack);
		return (2);
	}
	free(stack);
	if (q_count % 2)
		return (1);
	else if (dq_count % 2)
		return (2);
	else
		return (0);
}

int repeat_check_quote(char *line, char c)
{
	int i = 0;
	int count = 0;

	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	return (count % 2);

}

char *change_last_char(char *str, char c)
{
	int i = 0;

	while (str[i])
	{
		if (str[i + 1] == '\0')
		{
			str[i] = c;
			return (str);
		}
		i++;
	}
	return (NULL);
}

char	*skip_quotes(const char *src, char q_type)
{
	int i;
	int j;
	char *clearline;

	clearline = ft_memalloc(MAXLINE);
	i = 0;
	j = 0;
	while (src[i])
	{
		while (src[j] == q_type)
			j++;
		clearline[i] = src[j];
		i++;
		j++;
	}
	clearline[i] = '\0';
	return (clearline);
}


void quote_readline(int quote_type)
{
	char *line;

	set_input_tmode();
	line = NULL;
	readline_cmnd(&line, display_added_prompt(quote_type));
	g_shell->main_cmnd = ft_strcat(g_shell->main_cmnd, skip_quotes(line, quote_type == 1 ? (char)39 : (char)34));
	if (!repeat_check_quote(line, quote_type == 1 ? (char)39 : (char)34))
	{
		g_shell->main_cmnd = ft_strcat(g_shell->main_cmnd,"\n");
		quote_readline(quote_type);
	}
	reset_input_tmode();
}

void quote_output(char *line, int q_type)
{
	g_shell->inputmode = QUOTE_INPUT;
	g_shell->main_cmnd = ft_strcpy(g_shell->main_cmnd, ft_strcat(skip_quotes(line, q_type == 1 ? (char)39 : (char)34), "\n"));
	quote_readline(q_type);
}
