/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:12:25 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/07 21:12:28 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_cmnd(char **args)
{
	int i;
	int argc;

	i = 1;
	argc = 0;
	while (args[argc])
		argc++;
	while (args[i])
	{
		if (!ft_strcmp(" ", args[i]))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if ((argc - 1) != i)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
