/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:54:14 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/06/06 15:50:18 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include "libft.h"

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

int		check_for_else(char *s)  //without hidden files and dirs
{
	int i;
	
	i = 0;
	if (s[i] >= 32 && s[i] <= 47 && s[i] != 46)
		return (1);
	if (s[i] >= 58 && s[i] <= 63)
		return (1);
	if (s[i] >= 91 && s[i] <= 96)
		return (1);
	if (s[i] >= 123 && s[i] <= 126)
		return (1);
	return (0);
}

int	else_sort(int start, char *s)
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
		if (check_for_else(st->d_name) == 1)
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

void	list_directory(char *path)
{
	int r;

	r = 0;
	r = else_sort(r, path);
	r = num_sort(r, path);
	r = upper_sort(r, path);
	r = lower_sort(r, path);
}

// int	ft_strcmp(char *s1, char *s2)
// {
// 	while (*s1 == *s2)
// 	{
// 		if (*s1 == '\0')
// 			return (0);
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned char)*s1 - (unsigned char)*s2);
// }

// void	ft_putstr(char *s)
// {
// 	if (s == NULL)
// 		return ;
// 	while (*s)
// 		write(1, s++, 1);
// }

int		list_current(char *s)
{
	DIR *dir;
	struct dirent *d;
	
	dir = opendir(".");
	while ((d = readdir(dir)) != NULL)
	{
		if (ft_strcmp(s, d->d_name) == 0)
		{
			ft_putstr(d->d_name);
			write(1, "\n", 1);
			return (0);
		}
	}
	write(1, "ls: ", 4);
	ft_putstr(s);
	write(1, ": No such file or directory\n", 28);
	return (-1);
}

int		main(int argc, char **argv)
{
	DIR *dir;
	int i;

	i = 0;
	if (argc == 1)
		list_directory(".");
	else if (argc == 2)
	{
		if (!(dir = opendir(argv[1])))
		{
			if (list_current(argv[1]) == 0)
				return (0);
			else
				return (-1);
		}
		list_directory(argv[1]);
	}
	write(1, "\n", 1);
	return (0);
}

