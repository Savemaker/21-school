//
// Created by Екатерина on 2019-10-03.
//

#include "minishell.h"

void copy_after_cursor(t_readline *input)
{
	int pos;
	char *firstpart;

	pos = input->y * input->maxwidth + input->x - input->prompt_end;
	ft_bzero(input->clipboard, MAXLINE);
	input->clipboard = ft_strncpy(input->clipboard, input->line + pos, (size_t)input->size - pos);
	firstpart = ft_memalloc(MAXLINE);
	firstpart = ft_strncpy(firstpart, input->line, (unsigned)pos);
	clear_visible_line(input);

	ft_putstr(firstpart);
	ft_putstr(UWHITE);
	ft_putstr(input->clipboard);
	ft_putstr(RESET);
	goto_lastsymb(input);
	free(firstpart);
}

void copy_before_cursor(t_readline *input)
{
	int pos;
	char *residue;

	pos = input->y * input->maxwidth + input->x - input->prompt_end;
	ft_bzero(input->clipboard, MAXLINE);
	input->clipboard = ft_strncpy(input->clipboard, input->line, (size_t)pos);

	residue = ft_memalloc(MAXLINE);
	residue = ft_strncpy(residue, input->line + pos, (size_t)input->size - pos);

	clear_visible_line(input);
	ft_putstr(UWHITE);
	ft_putstr(input->clipboard);
	ft_putstr(RESET);
	ft_putstr(residue);
	goto_lastsymb(input);
	free(residue);
}

void cut_after_cursor(t_readline *input)
{
	int		pos;

	pos = input->y * input->maxwidth + input->x - input->prompt_end;
	ft_bzero(input->clipboard, MAXLINE);
	input->clipboard = ft_strncpy(input->clipboard, input->line + pos, (size_t)input->size - pos);
	ft_bzero(input->line + pos, MAXLINE - pos);
	input->size = (int)ft_strlen(input->line);
	clear_visible_line(input);
	ft_putstr(input->line);
	goto_lastsymb(input);
}
