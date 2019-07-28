/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:43:21 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/07/23 16:30:11 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			print_usr(char *buf, int off, mode_t st_mode)
{
	if (st_mode & S_IRUSR)
		buf[off++] = 'r';
	else
		buf[off++] = '-';
	if (st_mode & S_IWUSR)
		buf[off++] = 'w';
	else
		buf[off++] = '-';
	if (st_mode & S_IXUSR)
		buf[off++] = 'x';
	else
		buf[off++] = '-';
	return (off);
}

int			print_grp(char *buf, int off, mode_t st_mode)
{
	if (st_mode & S_IRGRP)
		buf[off++] = 'r';
	else
		buf[off++] = '-';
	if (st_mode & S_IWGRP)
		buf[off++] = 'w';
	else
		buf[off++] = '-';
	if (st_mode & S_IXGRP)
		buf[off++] = 'x';
	else
		buf[off++] = '-';
	return (off);
}

int			print_oth(char *buf, int off, mode_t st_mode)
{
	if (st_mode & S_IROTH)
		buf[off++] = 'r';
	else
		buf[off++] = '-';
	if (st_mode & S_IWOTH)
		buf[off++] = 'w';
	else
		buf[off++] = '-';
	if (st_mode & S_IXOTH)
		buf[off++] = 'x';
	else
		buf[off++] = '-';
	return (off);
}

int			print_l_rights(char *buf, int off, mode_t st_mode)
{
	off = print_usr(buf, off, st_mode);
	off = print_grp(buf, off, st_mode);
	off = print_oth(buf, off, st_mode);
	return (off);
}

int			print_l_extended(char *buf, int off, t_dir *list)
{
	ssize_t		res;
	acl_t		acl;
	acl_entry_t d;
	char		name[1024];

	acl = NULL;
	acl = acl_get_link_np(list->path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &d) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	res = listxattr(list->path, name, 1024, XATTR_NOFOLLOW);
	if (res < 0)
		res = 0;
	if (res > 0)
		buf[off++] = '@';
	else if (acl != NULL)
		buf[off++] = '+';
	else
		buf[off++] = ' ';
	buf[off++] = ' ';
	acl_free(acl);
	return (off);
}

int			print_file_type(char *buf, int off, mode_t st_mode)
{
	if (S_ISDIR(st_mode))
		buf[off++] = 'd';
	else if (S_ISBLK(st_mode))
		buf[off++] = 'b';
	else if (S_ISCHR(st_mode))
		buf[off++] = 'c';
	else if (S_ISLNK(st_mode))
		buf[off++] = 'l';
	else if (S_ISSOCK(st_mode))
		buf[off++] = 's';
	else if (S_ISFIFO(st_mode))
		buf[off++] = 'p';
	else if (S_ISREG(st_mode))
		buf[off++] = '-';
	return (off);
}

int			space(int m)
{
	int count;

	count = 0;
	while (m > 0)
	{
		count++;
		m /= 10;
	}
	if (count == 0)
		return (1);
	return (count);
}

int			print_link_num(char *buf, int off, t_dir *list, t_max *max)
{
	char	*res;
	int		i;
	int		m;
	int		j;

	j = 0;
	m = space(max->max_links);
	i = space(list->link);
	while (i < m)
	{
		buf[off++] = ' ';
		i++;
	}
	res = ft_itoa(list->link);
	while (res[j])
	{
		buf[off++] = res[j++];
	}
	free(res);
	buf[off++] = ' ';
	return (off);
}

int			print_user_nam(char *buf, int off, t_dir *list, t_max *max)
{
	size_t	m;
	int		i;
	size_t	len;

	i = 0;
	m = max->max_user;
	len = ft_strlen(list->user);
	while (list->user[i])
	{
		buf[off++] = list->user[i++];
	}
	while (len < m)
	{
		buf[off++] = ' ';
		len++;
	}
	buf[off++] = ' ';
	buf[off++] = ' ';
	return (off);
}

int			print_gr_name(char *buf, int off, t_dir *list, t_max *max)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(list->group);
	while (list->group[i])
	{
		buf[off++] = list->group[i++];
	}
	while (len < max->max_group)
	{
		buf[off++] = ' ';
		len++;
	}
	buf[off++] = ' ';
	buf[off++] = ' ';
	return (off);
}

int			print_size(char *buf, int off, t_dir *list, t_max *max)
{
	char	*res;
	int		i;
	int		m;
	int		j;

	j = 0;
	m = space(max->max_size);
	i = space(list->size);
	while (i < m)
	{
		buf[off++] = ' ';
		i++;
	}
	res = ft_itoa(list->size);
	while (res[j])
		buf[off++] = res[j++];
	buf[off++] = ' ';
	free(res);
	return (off);
}

int			check_six_months(time_t stm)
{
	time_t now;
	time_t then;
	time_t dif;

	now = time(NULL);
	then = stm;
	dif = now - then;
	if (dif > 15811200)
		return (1);
	return (0);
}

int			print_time_stuff(char *buf, int off, char *time)
{
	int i;

	i = 4;
	while (time[i] && i < 11)
		buf[off++] = time[i++];
	buf[off++] = ' ';
	i = 20;
	while (time[i] != '\n')
		buf[off++] = time[i++];
	return (off);
}

int			print_time(char *buf, int off, t_dir *list)
{
	char		*time;
	struct stat s;
	int			i;
	int			check;

	i = 4;
	if (list)
	{
		lstat(list->path, &s);
		check = check_six_months(s.st_mtime);
		time = ctime(&s.st_mtime);
		if (check == 0)
		{
			while (time[i] && i < 16)
				buf[off++] = time[i++];
		}
		else
			off = print_time_stuff(buf, off, time);
		buf[off++] = ' ';
	}
	return (off);
}

int			print_major(char *buf, int off, dev_t rdev, t_max *max)
{
	int		num;
	int		spc;
	int		until;
	char	*res;
	int		i;

	i = 0;
	num = major(rdev);
	spc = space(num);
	until = space(max->max_major);
	while (spc < until)
	{
		buf[off++] = ' ';
		spc++;
	}
	res = ft_itoa(num);
	while (res[i])
		buf[off++] = res[i++];
	free(res);
	return (off);
}

int			print_maj_min(char *buf, int off, dev_t rdev, t_max *max)
{
	char	*res;
	int		i;
	int		num;
	int		spc;
	int		until;

	i = 0;
	off = print_major(buf, off, rdev, max);
	buf[off++] = ',';
	buf[off++] = ' ';
	num = minor(rdev);
	spc = space(num);
	until = space(max->max_minor);
	while (spc < until)
	{
		buf[off++] = ' ';
		spc++;
	}
	res = ft_itoa(num);
	while (res[i])
		buf[off++] = res[i++];
	buf[off++] = ' ';
	free(res);
	return (off);
}

int			print_link(char *buf, int off, t_dir *list)
{
	int		res;
	int		i;
	char	b[1024];

	res = readlink(list->path, b, 1024);
	b[res] = '\0';
	i = 0;
	if (res > 0)
	{
		buf[off++] = ' ';
		buf[off++] = '-';
		buf[off++] = '>';
		buf[off++] = ' ';
		while (b[i])
			buf[off++] = b[i++];
	}
	return (off);
}

int			check_std_spaces(t_dir *list)
{
	if (ft_strcmp(list->name, "fd") == 0)
		return (1);
	if (ft_strcmp(list->name, "stderr") == 0)
		return (1);
	if (ft_strcmp(list->name, "stdin") == 0)
		return (1);
	if (ft_strcmp(list->name, "stdout") == 0)
		return (1);
	return (0);
}

int			print_std_spaces(t_dir *list, char *buf, int off)
{
	int i;

	i = 6;
	if (check_std_spaces(list) == 1)
	{
		while (i > 0)
		{
			buf[off++] = ' ';
			i--;
		}
	}
	return (off);
}

int			print_l_flag(char *buf, int off, t_dir *list, t_max *max)
{
	struct stat s;

	if (lstat(list->path, &s) == 0)
	{
		off = print_file_type(buf, off, s.st_mode);
		off = print_l_rights(buf, off, s.st_mode);
		off = print_l_extended(buf, off, list);
		off = print_link_num(buf, off, list, max);
		off = print_user_nam(buf, off, list, max);
		off = print_gr_name(buf, off, list, max);
		off = print_std_spaces(list, buf, off);
		if (list->special_file == 0)
			off = print_size(buf, off, list, max);
		if (list->special_file == 1)
		{
			off = print_maj_min(buf, off, s.st_rdev, max);
		}
		off = print_time(buf, off, list);
	}
	else
		perror(list->path);
	return (off);
}

int			write_total(char *buf, int off)
{
	buf[off++] = 't';
	buf[off++] = 'o';
	buf[off++] = 't';
	buf[off++] = 'a';
	buf[off++] = 'l';
	buf[off++] = ' ';
	return (off);
}

int			print_total(char *buf, int off, t_dir *list)
{
	struct stat s;
	int			total;
	char		*res;
	int			check;

	check = 0;
	total = 0;
	while (list)
	{
		check++;
		lstat(list->path, &s);
		total += s.st_blocks;
		list = list->next;
	}
	if (check > 0)
	{
		res = ft_itoa(total);
		off = write_total(buf, off);
		total = 0;
		while (res[total])
			buf[off++] = res[total++];
		free(res);
		buf[off++] = '\n';
	}
	return (off);
}

int			print_dir_content_stuff_ch(char *tb, int off, t_dir *list)
{
	if (list->next)
		tb[off++] = ' ';
	else
		tb[off++] = '\n';
	return (off);
}

int			print_dir_content_st(t_dir *list, char *tb, int off, int f)
{
	t_max	*max;
	int		i;

	i = 0;
	max = NULL;
	if (check_flag('l', f))
		max = new_max(list);
	while (list)
	{
		i = 0;
		if (check_flag('l', f))
			off = print_l_flag(tb, off, list, max);
		while (list->name[i])
			tb[off++] = list->name[i++];
		if (check_flag('l', f))
			off = print_link(tb, off, list);
		if (check_flag('l', f) && list->next)
			tb[off++] = '\n';
		else
			off = print_dir_content_stuff_ch(tb, off, list);
		list = list->next;
	}
	if (check_flag('l', f))
		free(max);
	return (off);
}

int			print_dir_content(t_dir *list, int flags, int n, char *arg)
{
	int		off;
	char	*tb;

	tb = (char *)malloc(sizeof(char) * BUF_SIZE);
	off = 0;
	if (arg)
		off = print_file_name(arg, tb);
	if (check_flag('l', flags))
		off = print_total(tb, off, list);
	off = print_dir_content_st(list, tb, off, flags);
	if (n == 1)
		tb[off++] = '\n';
	write(1, tb, off);
	free(tb);
	return (off);
}
