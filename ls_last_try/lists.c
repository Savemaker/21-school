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