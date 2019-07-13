#include "ft_ls.h"

void    append(t_dir **head, t_dir *node)
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
		node->prev = temp;
	}
}

t_max *new_max(t_dir *list)
{
    t_max *res;
    struct stat s;
    struct passwd *p;
    struct group *g;

    res = (t_max *)malloc(sizeof(t_max));
    res->max_group = 0;
    res->max_links = 0;
    res->max_size = 0;
    res->max_user = 0;
    res->max_major = 0;
    res->max_minor = 0;
    while (list)
    {
        lstat(list->path, &s);
        if (S_ISBLK(s.st_mode) || S_ISCHR(s.st_mode))
            list->special_file = 1;
        if (S_ISLNK(s.st_mode))
            list->lnk = 1;
        p = getpwuid(s.st_uid);
        g = getgrgid(s.st_gid);
        if (major(s.st_rdev) > res->max_major)
            res->max_major = major(s.st_rdev);
        if (minor(s.st_rdev) > res->max_minor)
            res->max_minor = minor(s.st_rdev);
        if (p != NULL)
        {
            if (ft_strlen(p->pw_name) > res->max_user)
                res->max_user = ft_strlen(p->pw_name);
            list->user = ft_strdup(p->pw_name);
        }
        else
        {
            if (s.st_uid > res->max_user)
                res->max_user = s.st_uid;
            list->user = ft_itoa(s.st_uid);
        }
        if (g != NULL)
        {
            if (ft_strlen(g->gr_name) > res->max_group)
                res->max_group = ft_strlen(g->gr_name);
            list->group = ft_strdup(g->gr_name);
        }
        else
        {
            if (s.st_gid > res->max_group)
                res->max_group = s.st_gid;
            list->group = ft_itoa(s.st_gid);
        }
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

t_dir   *new_list(char *name, char *path, int level)
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
    new->prev = NULL;
    new->level = level;
    new->std = 0;
    new->link = 0;
    new->inside = NULL;
    new->user = NULL;
    new->group = NULL;
    new->lnk = 0;
    new->size = 0;
    new->special_file = 0;
    return (new);
}

void    complex_fork(t_dir *arg, t_dir **dir, t_dir **file)
{
    struct stat s;
    t_dir *new;

    *dir = NULL;
    *file = NULL;
    while (arg)
    {
        lstat(arg->path, &s);
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
        arg = arg->next;
    }
}

void    fork_arg_list(t_dir *arg, t_dir **dir, t_dir **file, char *path)
{
    struct stat s;
    t_dir *new;

    *dir = NULL;
    *file = NULL;
    while (arg)
    {
        lstat(arg->path, &s);    //path = name
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
        arg = arg->next;
    }
}
