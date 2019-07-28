/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 15:30:04 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/07/23 15:20:59 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		append(t_dir **head, t_dir *node)
{
	t_dir *temp;

	temp = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

void		init_res_max(t_max *res)
{
	res->max_group = 0;
	res->max_links = 0;
	res->max_size = 0;
	res->max_user = 0;
	res->max_major = 0;
	res->max_minor = 0;
}

void		pwuid_max(t_max *res, uid_t st_uid, t_dir *list)
{
	struct passwd	*p;

	p = getpwuid(st_uid);
	if (p != NULL)
	{
		if (ft_strlen(p->pw_name) > res->max_user)
			res->max_user = ft_strlen(p->pw_name);
		list->user = ft_strdup(p->pw_name);
	}
	else
	{
		if (st_uid > res->max_user)
			res->max_user = st_uid;
		list->user = ft_itoa(st_uid);
	}
}

void		grgid_max(t_max *res, gid_t st_gid, t_dir *list)
{
	struct group	*g;

	g = getgrgid(st_gid);
	if (g != NULL)
	{
		if (ft_strlen(g->gr_name) > res->max_group)
			res->max_group = ft_strlen(g->gr_name);
		list->group = ft_strdup(g->gr_name);
	}
	else
	{
		if (st_gid > res->max_group)
			res->max_group = st_gid;
		list->group = ft_itoa(st_gid);
	}
}

void		major_minor(t_max *res, dev_t st_rdev)
{
	if (major(st_rdev) > res->max_major)
		res->max_major = major(st_rdev);
	if (minor(st_rdev) > res->max_minor)
		res->max_minor = minor(st_rdev);
}

t_max		*new_max(t_dir *list)
{
	t_max			*res;
	struct stat		s;

	res = (t_max *)malloc(sizeof(t_max));
	init_res_max(res);
	while (list)
	{
		lstat(list->path, &s);
		if (S_ISBLK(s.st_mode) || S_ISCHR(s.st_mode))
			list->special_file = 1;
		if (S_ISLNK(s.st_mode))
			list->lnk = 1;
		pwuid_max(res, s.st_uid, list);
		grgid_max(res, s.st_gid, list);
		major_minor(res, s.st_rdev);
		if (s.st_nlink > res->max_links)
			res->max_links = s.st_nlink;
		if (s.st_size > res->max_size)
			res->max_size = s.st_size;
		list->size = s.st_size;
		list->link = s.st_nlink;
		list = list->next;
	}
	return (res);
}

t_dir		*new_list(char *name, char *path, int level)
{
	t_dir *new;

	if (!(new = (t_dir *)malloc(sizeof(t_dir))))
		return (NULL);
	new->name = ft_strdup(name);
	if (path == NULL)
		new->path = ft_strdup(name);
	else
		new->path = create_path(name, path);
	new->next = NULL;
	new->level = level;
	new->std = 0;
	new->link = 0;
	new->dir = 0;
	new->extended = 0;
	new->user = NULL;
	new->group = NULL;
	new->lnk = 0;
	new->size = 0;
	new->special_file = 0;
	return (new);
}

void		complex_fork(t_dir *arg, t_dir **dir, t_dir **file)
{
	struct stat	s;
	t_dir		*new;

	*dir = NULL;
	*file = NULL;
	while (arg)
	{
		if (lstat(arg->path, &s) == 0)
		{
			if ((S_ISDIR(s.st_mode) == 1) && (no_dots_dirs(arg->name) == 0))
			{
				new = new_list(arg->name, NULL, 0);
				append(dir, new);
			}
			else if (S_ISDIR(s.st_mode) == 0)
			{
				new = new_list(arg->name, NULL, 0);
				append(file, new);
			}
		}
		else
			perror(arg->path);
		arg = arg->next;
	}
}

void		fork_arg(t_dir *arg, t_dir **dir, t_dir **file, char *path)
{
	struct stat	s;
	t_dir		*new;

	*dir = NULL;
	*file = NULL;
	while (arg)
	{
		if (lstat(arg->path, &s) == 0)
		{
			if ((S_ISDIR(s.st_mode) == 1) && (no_dots_dirs(arg->name) == 0))
			{
				new = new_list(arg->name, path, 0);
				append(dir, new);
			}
			else if (S_ISDIR(s.st_mode) == 0)
			{
				new = new_list(arg->name, path, 0);
				append(file, new);
			}
		}
		else
			perror(arg->path);
		arg = arg->next;
	}
}
