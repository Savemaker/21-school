/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 14:18:44 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/07/23 15:20:51 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir		*open_dir(char *path, int flags)
{
	DIR				*dir;
	struct dirent	*d;
	t_dir			*head;

	head = NULL;
	dir = opendir(path);
	if (dir == NULL)
	{
		perror(path);
		return (NULL);
	}
	while ((d = readdir(dir)) != NULL)
	{
		if (check_flag('a', flags))
			open_dir_create(d->d_name, path, &head);
		else
		{
			if (d->d_name[0] != '.')
				open_dir_create(d->d_name, path, &head);
		}
	}
	sorts(&head, flags);
	closedir(dir);
	return (head);
}

void		open_dir_create(char *name, char *path, t_dir **head)
{
	char		*put;
	int			check;
	struct stat s;
	t_dir		*new;

	new = NULL;
	put = create_path(name, path);
	check = lstat(put, &s);
	if (check == 0)
	{
		new = new_list(name, path, 0);
		if (S_ISDIR(s.st_mode) == 1)
			new->dir = 1;
		append(head, new);
	}
	else
		perror(put);
	free(put);
}

void		delete_list(t_dir **list)
{
	t_dir *cur;
	t_dir *temp;

	cur = *list;
	while (cur != NULL)
	{
		free(cur->name);
		free(cur->user);
		free(cur->group);
		free(cur->path);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	*list = NULL;
}

int			basic_stuf(char *path, int flags, int offset)
{
	t_dir		*content;
	struct stat s;
	int			check;

	content = NULL;
	check = lstat(path, &s);
	if (check == 0)
	{
		if (S_ISDIR(s.st_mode) == 1)
		{
			content = open_dir(path, flags);
			print_dir_content(content, flags, check_flag('R', flags), NULL);
		}
		else
			print_file(path);
	}
	else
	{
		perror(path);
		return (offset);
	}
	if (check_flag('R', flags))
		fork_and_expand(content, path, flags);
	delete_list(&content);
	return (offset);
}

void		fork_and_expand(t_dir *content, char *path, int flags)
{
	t_dir *file;
	t_dir *dir_list;

	if (content)
	{
		fork_arg(content, &dir_list, &file, path);
		expand_list(&dir_list, flags);
	}
	delete_list(&file);
}

int			print_files(char *name, char *buf)
{
	int i;
	int off;

	off = 0;
	i = 0;
	while (name[i])
		buf[off++] = name[i++];
	buf[off++] = ' ';
	return (off);
}

void		expand_open(t_dir *open, char *path, t_dir **head)
{
	char	*p;
	t_dir	*new;

	while (open)
	{
		if (open->dir == 1 && no_dots_dirs(open->name) == 0)
		{
			p = create_path(open->name, path);
			new = new_list(p, NULL, 1);
			free(p);
			append(head, new);
		}
		open = open->next;
	}
}

void		expand_head(t_dir **head, t_dir **args, int flags)
{
	t_dir *t;

	if (*head)
	{
		sorts(head, flags);
		t = (*args)->next;
		(*args)->next = *head;
		while ((*head)->next)
			*head = (*head)->next;
		(*head)->next = t;
	}
	*head = NULL;
}

void		expand_list(t_dir **list, int flags)
{
	t_dir	*args;
	t_dir	*open;
	int		n;
	t_dir	*head;
	t_dir	*del;

	head = NULL;
	args = *list;
	del = args;
	while (args)
	{
		n = 0;
		if (no_dots_dirs(args->path) == 0)
		{
			open = open_dir(args->path, flags);
			expand_open(open, args->path, &head);
			expand_head(&head, &args, flags);
		}
		if (args->next)
			n = 1;
		print_dir_content(open, flags, n, args->path);
		delete_list(&open);
		args = args->next;
	}
	delete_list(&del);
}

int			output_files(t_dir *files)
{
	char	buf[4096];
	int		i;
	int		off;

	off = 0;
	while (files)
	{
		i = 0;
		while (files->path[i])
			buf[off++] = files->path[i++];
		if (files->next)
			buf[off++] = ' ';
		files = files->next;
	}
	if (i > 0)
		buf[off++] = '\n';
	write(1, buf, off);
	return (off);
}

void		create_list_append(t_dir **args, char *argv)
{
	t_dir *new;

	new = new_list(argv, NULL, 0);
	append(args, new);
}

int			complex_stuf(char **argv, int start, int flags, int off)
{
	t_dir	*files;
	t_dir	*dirs;
	t_dir	*args;
	int		c;

	args = NULL;
	while (argv[start])
	{
		create_list_append(&args, argv[start]);
		start++;
	}
	sorts(&args, flags);
	complex_fork(args, &dirs, &files);
	c = output_files(files);
	if (dirs && c > 0)
		write(1, "\n", 1);
	while (dirs)
	{
		print_file_name_comp(dirs->path);
		basic_stuf(dirs->path, flags, 0);
		if (dirs->next && check_flag('R', flags) == 0)
			write(1, "\n", 1);
		dirs = dirs->next;
	}
	return (off);
}

int			parse_args(char **argv, int flags, int start)
{
	int c;
	int ret;

	c = arg_len(argv, start);
	if (argv[start] == NULL)
		ret = basic_stuf(".", flags, 0);
	if (c == 1)
		ret = basic_stuf(argv[start], flags, 0);
	if (c > 1)
		ret = complex_stuf(argv, start, flags, 0);
	return (ret);
}

void		output(char *buf, int ret)
{
	write(1, buf, ret);
}

int			main(int argc, char **argv)
{
	int flags;
	int start;
	int ret;

	start = 0;
	flags = 0;
	if (argc == 1)
	{
		ret = basic_stuf(".", flags, 0);
	}
	if (argc > 1)
	{
		start = get_flags(argv, &flags);
		if (start == -1)
			return (1);
		ret = parse_args(argv, flags, start);
	}
	return (0);
}
