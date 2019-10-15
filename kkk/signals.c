/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:34:29 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/10/15 18:32:55 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//
//char	*check_sig_code(int sig_code)
//{
//	if (sig_code == SIGINT)
//		return (": Interrupt\n");
//	return (NULL);
//}
//
//void	print_signal(char *reason, int sig_code)
//{
//	ft_putstr_fd(reason, STDIN_FILENO);
//	ft_putstr(check_sig_code(sig_code));
//}

void	handler_interrupt(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
//		g_shell->sig |= SIGINT;
		g_shell->sig = 0;
		g_shell->error = EXIT_FAILURE;

		display_prompt();
	}
}


void	handler_win(int sig)
{
	char	*line_cp;
	char	*clipboard_cp;
	int		promptsize_cp;
	int		position_cp;

	sig = 0;
	line_cp = NULL;
	clipboard_cp = NULL;
	if (g_shell->input->line)
		line_cp = ft_strdup(g_shell->input->line);
//	ft_bzero(g_shell->input->line, sizeof(g_shell->input->line));
	// free(&g_shell->input->line);
	if (g_shell->input->clipboard)
		clipboard_cp = ft_strdup(g_shell->input->clipboard);
//	ft_bzero(g_shell->input->clipboard, sizeof(g_shell->input->clipboard));
	free(g_shell->input->clipboard);
//
	position_cp = g_shell->input->y * g_shell->input->maxwidth + g_shell->input->x - g_shell->input->prompt_end;
	promptsize_cp = g_shell->input->prompt_size;
//
//	ft_putstr("oldwidth: ");
//	ft_putnbr(g_shell->input->maxwidth);
//	ft_putchar('\n');
//	ft_putstr("oldx: ");
//	ft_putnbr(g_shell->input->x);
//	ft_putchar('\n');
//
	g_shell->input = init_readline(promptsize_cp);
//
//
	if (line_cp)
		ft_memcpy(g_shell->input->line, line_cp, ft_strlen(line_cp));
////		ft_memcpy(g_shell.input.line, line_cp, ft_strlen(line_cp));
	free(line_cp);
////
	if (clipboard_cp)
		ft_memcpy(g_shell->input->clipboard, clipboard_cp, ft_strlen(clipboard_cp));
	free(clipboard_cp);



	g_shell->input->size = (int)ft_strlen(g_shell->input->line);
	g_shell->input->x = ((position_cp + g_shell->input->prompt_end) % g_shell->input->maxwidth);
	g_shell->input->y = ((position_cp + g_shell->input->prompt_end) / g_shell->input->maxwidth);
//
//		ft_putstr("newwidth: ");
//	ft_putnbr(g_shell->input->maxwidth);
//	ft_putchar('\n');
//	ft_putstr("newx: ");
//	ft_putnbr(g_shell->input->x);
//	ft_putchar('\n');
//
}
void	handler_interrupt_exe(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
//		g_shell->sig |= SIGINT;
		g_shell->sig = 0;
		g_shell->error = EXIT_FAILURE;

//		display_prompt();
	}
}

void	signals(int exe)
{
	if (exe)
		signal(SIGINT, handler_interrupt_exe);
	else
		signal(SIGINT, handler_interrupt);
	signal(SIGWINCH, handler_win);
//	signal(SIGTERM, handler_interrupt);
}
