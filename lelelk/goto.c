//
// Created by Екатерина on 2019-10-03.
//
#include "minishell.h"

void goto_linestart(t_readline *input)
{
	int  strn;

	if (input->y)
	{
		strn = input->y;
		while (strn--)
			TUP;
	}
	TLEFT_BORDER;
}

void goto_inputstart(t_readline *input)
{
	int prompt;

	goto_linestart(input);
	prompt = input->prompt_end;
	while (prompt--)
		TRIGHT;
}


void goto_start(t_readline *input)
{
	goto_inputstart(input);
	input->x = input->prompt_end;
	input->y = 0;
}

void goto_end(t_readline *input)
{
	int fullstrsize;

	fullstrsize = input->prompt_end + input->size;
	while (input->y * input->maxwidth + input->x < fullstrsize)
		cursor_right(input);
}

void goto_next_word(t_readline *input)
{
	int pos;

	pos = input->y * input->maxwidth + input->x - input->prompt_end;
	while (input->line[pos] && !ft_isspace(input->line[pos]))
	{
		pos++;
		cursor_right(input);
	}
	while (input->line[pos] && ft_isspace(input->line[pos]))
	{
		pos++;
		cursor_right(input);
	}
}

void goto_prev_word(t_readline *input)
{
	int pos;

	pos = input->y * input->maxwidth + input->x - input->prompt_end;
	if (pos && (!(ft_isspace(input->line[pos]) && ft_isspace(input->line[pos - 1])) || !input->line[pos]))
	{
		pos--;
		cursor_left(input);
	}
	while (pos && input->line[pos] && ft_isspace(input->line[pos]))
	{
		pos--;
		cursor_left(input);
	}
	while (pos && input->line[pos] && !ft_isspace(input->line[pos]))
	{
		pos--;
		cursor_left(input);
	}
	if (pos > 0)
		cursor_right(input);
}