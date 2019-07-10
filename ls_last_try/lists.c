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
    while (list)
    {
        lstat(list->path, &s);
        p = getpwuid(s.st_uid);
        g = getgrgid(s.st_gid);
        if (ft_strlen(p->pw_name) > res->max_user)
            res->max_user = ft_strlen(p->pw_name);
        if (ft_strlen(g->gr_name) > res->max_group)
            res->max_group = ft_strlen(g->gr_name);
        list->user = ft_strdup(p->pw_name);
        list->group = ft_strdup(g->gr_name);
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
    new->inside = NULL;
    new->user = NULL;
    new->group = NULL;
    new->link = 0;
    new->size = 0;
    return (new);
}

t_dir *list_for_output(char *path, int flags)
{
    DIR *dir;
    t_dir *new;
    t_dir *head;
    struct dirent *d;

    head = NULL;
    dir = opendir(path);
    while (((d = readdir(dir))) != NULL)
    {
        if (d->d_name[0] != '.')
        {
            new = new_list(d->d_name, path, 0);
            append(&head, new);
        }
    }
    sorts(&head, flags);
    return (head);
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
        if (S_ISDIR(s.st_mode) == 1)
        {
            new = new_list(arg->name, path, 0);
            append(dir, new);
        }
        else
        {
            new = new_list(arg->name, path, 0);
            append(file, new);
        }
        arg = arg->next;
    }
}

t_dir   *create_arg_list(char **argv, int flags)
{
    t_dir *arg_l;
    t_dir *new;
    int i;
    struct stat s;

    i = 0;
    arg_l = NULL;
    while (argv[i])
    {
        if (!lstat(argv[i], &s))
        {
            new = new_list(argv[i], NULL, 0);
            append(&arg_l, new);
        }
        else
        {
            ft_putstr("ft_ls: ");
            perror(argv[i]);
        }
        i++;
    }
    //flags
    sorts(&arg_l, flags);
    return (arg_l);
}