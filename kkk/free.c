/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 21:13:31 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/07 21:13:34 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_env(char **env_cp)
{
	int len;
	int j;

	j = 0;
	len = str_quantity(env_cp) + 1;
	while (j < len)
	{
		free(env_cp[j]);
		j++;
	}
	free(env_cp);
	env_cp = NULL;
}

//void	free_parse(char **parse, int w)
//{
//	int i;
//
//	i = 0;
//	while (i < w)
//	{
//		free(parse[i]);
//		i++;
//	}
//	free(parse);
//}
//
//void	free_copy_envp(char ***envp)
//{
//	char	**ref;
//
//	ref = *envp;
//	free_parse(ref, str_quantity(ref) + 1);
//}
