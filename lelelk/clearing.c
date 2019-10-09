//
// Created by Екатерина on 2019-10-03.
//
#include "minishell.h"

void clear_visible_line(t_readline *input)
{
	TCLEAR_STR;
	goto_inputstart(input);
}

void clear_screen(t_readline *input)
{
	int i;

	i = 0;
	while (i++ < input->maxheight)
		TUP;
	clear_visible_line(input);
	TCLEAR_STR;
	TLEFT_BORDER;
	display_prompt();
	goto_inputstart(input);
	input->size = 0;
	input->y = 0;
	input->x = input->prompt_end;
	ft_bzero(input->line, MAXLINE);
}

void clear_input(t_readline *input)
{
	clear_visible_line(input);
	input->y = 0;
	input->size = 0;
	ft_bzero(input->line, MAXLINE);
	input->x = input->prompt_end;
}
