/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:54:14 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/04/28 18:59:14 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int main(int argc, char **argv)
{
	int f;
	DIR* op;
	struct dirent *pDirent;

	if (argc < 2)
	{
		printf("usage = ./ft_ls <dirname> \n");
		return (1);
	}
		f = 0;
		op = NULL;
		op = opendir(argv[1]);
		if (op == NULL)
		{
			printf("err\n");
			return (1);
		}
		while ((pDirent = readdir(op)) != NULL)
		{
			if (ft_strcmp(pDirent->d_name, "Makefile") == 0)
			{
				f = 1;
				printf("Makefile ");
			}
		}
		closedir(op);
		op = opendir(argv[1]);
		while ((pDirent = readdir(op)) != NULL)
		{
			if (pDirent->d_name[0] != '.' && ft_strcmp(pDirent->d_name, "Makefile") != 0)
			{
				printf("%s", pDirent->d_name);
				printf(" ");
			}
		}
	printf("\n");
	closedir(op);
	return (0);
}
