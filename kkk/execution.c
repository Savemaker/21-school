/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:14:18 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/08 13:51:30 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

