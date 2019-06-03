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
#include <unistd.h>

int	upper_sort(int start, char *s)
{
	int				i;
	int				r;
	struct dirent	*st;
	DIR *dir;

	i = 0;
	r = 0;
	dir = opendir(s);
	while ((st = readdir(dir)) != NULL)
	{
		i = 0;
		if (st->d_name[i] >= 65 && st->d_name[i] <= 90)
		{
			r = 1;
			if (start == 1)
				write(1, " ", 1);
			start = 1;
			while (st->d_name[i] != '\0')
			{
				write(1, &st->d_name[i], 1);
				i++;
			}
		}
	}
	closedir(dir);
	return (r);
}

int	lower_sort(int start, char *s)
{
	int				i;
	int				r;
	struct dirent	*st;
	DIR *dir;

	i = 0;
	r = 0;
	dir = opendir(s);
	while ((st = readdir(dir)) != NULL)
	{
		i = 0;
		if (st->d_name[i] >= 97 && st->d_name[i] <= 122)
		{
			r = 1;
			if (start == 1)
				write(1, " ", 1);
			start = 1;
			while (st->d_name[i] != '\0')
			{
				write(1, &st->d_name[i], 1);
				i++;
			}
		}
	}
	closedir(dir);
	return (r);
}

int	num_sort(int start, char *s)
{
	int				i;
	int				r;
	struct dirent	*st;
	DIR *dir;

	i = 0;
	r = 0;
	dir = opendir(s);
	while ((st = readdir(dir)) != NULL)
	{
		i = 0;
		if (st->d_name[i] >= 48 && st->d_name[i] <= 57)
		{
			r = 1;
			if (start == 1)
				write(1, " ", 1);
			start = 1;
			while (st->d_name[i] != '\0')
			{
				write(1, &st->d_name[i], 1);
				i++;
			}
		}
	}
	closedir(dir);
	return (r);
}

int		main(int argc, char **argv)
{
	int				r;

	r = 0;
	if (argc == 1)
	{
		r = num_sort(r, ".");
		r = upper_sort(r, ".");
		r = lower_sort(r, ".");
	}
	else if (argc == 2)
	{
		r = num_sort(r, argv[1]);
		r = upper_sort(r, argv[1]);
		r = lower_sort(r, argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}

