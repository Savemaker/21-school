//
// Created by Екатерина on 2019-10-03.
//
#include "minishell.h"


void cursor_right(t_readline *input)
{
	int fullstrsize;

	fullstrsize = input->prompt_end + input->size;
	if ((input->y * (input->maxwidth) + input->x)< fullstrsize)
	{
		if (input->x < input->maxwidth - 1)
		{
			input->x++;
			TRIGHT;
		}
		else
		{
			input->y++;
			input->x = 0;
			TLEFT_BORDER;// левая граница тек строки
			TDOWN;
		}
	}
	else
		TBELL;
}

void cursor_left(t_readline *input)
{
	int i;


	if ((input->y == 0 && input->x > input->prompt_end) || (input->y > 0 && input->x > 0))
	{
		TLEFT;
		input->x--;
	}
	else if (input->y > 0 && input->x == 0)
	{
		TUP;
		i = input->maxwidth - 1;
		while (i--)
			TRIGHT;
		input->x = input->maxwidth -1;
		input->y--;
	}
	else
		TBELL;
}

void	cursor_up(t_readline *input)
{
	if (input->y > 1)
	{
		TUP;
		input->y--;
	}
	else if (input->y == 1 && input->x >= input->prompt_end)
	{
		TUP;
		input->y--;
	}
	else if (input->y == 1 && input->x < input->prompt_end)
	{
		goto_inputstart(input);
		input->x = input->prompt_end;
		input->y--;
	}
	else
		TBELL;
}

void	goto_lastsymb(t_readline *input)
{
	int fullstrsize;
	int	maxstrn;
	int	i;

	fullstrsize = input->prompt_end + input->size;
	maxstrn = fullstrsize / (input->maxwidth);
	if ((fullstrsize % input->maxwidth) == 0)
		maxstrn--;
	while (maxstrn--)
		TUP;
	TLEFT_BORDER;
	i = 0;
	while (i++ < input->y)
		TDOWN;
	i = 0;
	while (i++ < input->x)
		TRIGHT;

}

void	cursor_down(t_readline *input)
{
	int lastxpos;
	int fullstrsize;

	fullstrsize = input->prompt_end + input->size;
	if ((input->y + 1) * input->maxwidth + input->x < fullstrsize)
	{
		lastxpos = input->x;
		TDOWN;
		while (lastxpos--)
			TRIGHT;
		input->y++;
	}
	else if (((input->y + 1) * input->maxwidth <= fullstrsize))
	{
		while ((input->y * input->maxwidth + input->x) < fullstrsize)
			cursor_right(input);
	}
	else
		TBELL;
}
