//
// Created by Екатерина on 2019-10-03.
//

#include "minishell.h"

//void	char_enter(char *buf, t_readline *input)
//{
//	char	*residue;
//	int		pos;
//	int		bufsize;
//
//	bufsize = (int)ft_strlen(buf);
//	if (input->size < MAXLINE - bufsize)
//	{
//		pos = input->y * input->maxwidth + input->x - input->prompt_end;
//		residue = ft_strsub(input->line, (unsigned)pos, (size_t)input->size - pos);
//		ft_bzero(input->line + pos, (size_t)MAXLINE - pos);
//		input->line = ft_strcat(input->line, buf);
//		input->line = ft_strcat(input->line, residue);
//		clear_visible_line(input);
//		ft_putstr(input->line);
//		input->size += bufsize;
//		goto_lastsymb(input);
//		while (bufsize-- > 0)
//			cursor_right(input);
//		free(residue);
//	}
//	else
//		TBELL;
//}


void	char_enter(char *buf, t_readline *input)
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
		goto_lastsymb(input);
		while (bufsize-- > 0)
			cursor_right(input);
		free(residue);
	}
	else
		TBELL;
}



void	del_rightchar(t_readline *input)
{
	int		pos;
	char	*firstpart;
	char	*residue;

	pos = input->y * input->maxwidth + input->x - input->prompt_end;
	if (pos < input->size)
	{
		firstpart = ft_strsub(input->line, 0, (unsigned)pos);
		residue = ft_strsub(input->line, (unsigned)pos + 1, input->size - ft_strlen(firstpart));
		ft_bzero(input->line, MAXLINE);
		input->line = ft_strcpy(input->line, firstpart);
		input->line = ft_strcat(input->line, residue);
		free(firstpart);
		free(residue);
		clear_visible_line(input);
		ft_putstr(input->line);
		input->size--;
		goto_lastsymb(input);
	}
	else
		TBELL;
}

void	del_leftchar(t_readline *input)
{
	int		pos;
	char	*firstpart;
	char	*residue;

	pos = input->y * input->maxwidth + input->x - input->prompt_end;
	if (input->y > 0 || (input->y == 0 && input->x > input->prompt_end))
	{
		firstpart = ft_strsub(input->line, 0, (unsigned)pos - 1);
		residue = ft_strsub(input->line, (unsigned)pos, input->size - ft_strlen(firstpart));
		ft_bzero(input->line, MAXLINE);
		input->line = ft_strcpy(input->line, firstpart);
		input->line = ft_strcat(input->line, residue);
		clear_visible_line(input);
		ft_putstr(input->line);
		TDEL_CHAR;
		input->size--;
		goto_lastsymb(input);
		cursor_left(input);
		free(firstpart);
		free(residue);
	}
	else
		TBELL;
}