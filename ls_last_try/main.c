#include "ft_ls.h"

t_dir    *open_dir(char *path, int flags)   // returns sorted list of path content
{
    DIR *dir;
    struct dirent *d;
    struct stat s;
    t_dir *head;
    t_dir *new;

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
        {
            // if (no_dots_dirs(d->d_name) == 0)
            // {
                lstat(create_path(d->d_name, path), &s);
                new = new_list(d->d_name, path, 0);
                if (S_ISDIR(s.st_mode) == 1)
                    new->dir = 1;
                append(&head, new);
            // }
        }
        else
        {
            if (d->d_name[0] != '.')
            {
                lstat(create_path(d->d_name, path), &s);
                new = new_list(d->d_name, path, 0);
                if (S_ISDIR(s.st_mode) == 1)
                    new->dir = 1;
                append(&head, new);
            }
        }
    }
    sorts(&head, flags);
    closedir(dir);
    return (head);
}


int     print_dir_basic_recursive(char *buf, t_dir *dir_list, int flags)
{
    int i;
    int j;
    t_dir *cur;

    i = 0;
    j = 0;
    while (dir_list)
    {
        j = 0;
        while (dir_list->path[j])
            buf[i++] = dir_list->path[j++];    
        buf[i++] = ':';
        buf[i++] = '\n';
        cur = open_dir(dir_list->path, flags);
        i = print_dir_content(cur, flags, i, dir_list->name);
        if (dir_list->next)
            buf[i++] = '\n';
        dir_list = dir_list->next;
    }
    return (i);
}

int    basic_stuf(char *path, int flags, int offset, int c)  //flags ???
{
    t_dir *content;
    t_dir *dir_list;
    t_dir *file;
    struct stat s;
    int check;

    content = NULL;
    if (c <= 1)
    {
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
            perror(path);
        if (check_flag('R', flags))
        {
            if (content)
            {
                fork_arg_list(content, &dir_list, &file, path);
                expand_list(&dir_list, flags);
            }
        }
    }
    return (offset);
}

void    correct_list(t_dir **head, int flags)
{
    t_dir *list;
    t_dir *start;
    t_dir *stop;
    t_dir *point;

    list = *head;
    while (list && list->level != 0)
    {
        if (list->level == 0)
        {
            point = list;
            list = list->next;
            continue;
        }
        if (list->next && list->next->level == 0)
        {
            list = list->next;
            continue;
        }
        start = list;
        while (list->next && list->next->level != 0)
            list = list->next;
        stop = list->next;
        list->next = NULL;
        sorts(&start, flags);
        point->next = start;
        while (start->next && start->next->level == 1)
            start = start->next;
        start->next = stop;
        list = stop;
    }
}

int     print_files(char *name, char *buf)
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

void    expand_list(t_dir **list, int flags)
{
    t_dir *args;
    t_dir *new;
    t_dir *open;
    int n;
    t_dir *temp;
    t_dir *head;
    head = NULL;
    t_dir *t;

    args = *list;
    while (args)    //empty jp libft  ..
    {
        n = 0;
        if (no_dots_dirs(args->path) == 0)
        {
            open = open_dir(args->path, flags);
            temp = open;
            while (open)
            {
                if (open->dir == 1 && no_dots_dirs(open->name) == 0)
                {
                    new = new_list(create_path(open->name, args->path), NULL, 1);
                    append(&head, new);
                }
                open = open->next;
            }
            if (head)
            {
                sorts(&head, flags);
                t = args->next;
                args->next = head;
                while (head->next)
                    head = head->next;
                head->next = t;
            }
            head = NULL;
        }
        if (args->next)
            n = 1;
        print_dir_content(temp, flags, n, args->path);
        args = args->next;
    }
}

int    output_files(t_dir *files)
{
    char buf[4096];
    int i;
    int off;

    off = 0;
    while (files)
    {
        i = 0;
        while(files->path[i])
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

int     complex_stuf(char **argv, int start, int flags, int off)
{
    t_dir *files;
    t_dir *dirs;
    t_dir *args;
    t_dir *new;
    int c;

    args = NULL;
    while (argv[start])
    {
        new = new_list(argv[start], NULL, 0);
        append(&args, new);
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
        basic_stuf(dirs->path, flags, 0, 1);
        if (dirs->next)
            write(1, "\n", 1);
        dirs = dirs ->next;
    }
    return (off);
}

int   parse_args(char **argv, int flags, int start)
{
    int c;
    int ret;

    c = arg_len(argv, start);
    if (argv[start] == NULL)
       ret = basic_stuf(".", flags, 0, c);
    if (c == 1)
    {
       ret = basic_stuf(argv[start], flags, 0, c);
    }
    if (c > 1)
    {
       ret = complex_stuf(argv, start, flags, 0);
    }
    return (ret);
}

void    output(char *buf, int ret)
{
    write(1, buf, ret);
}

int main(int argc, char **argv)
{
    int flags;
    int start;
    int ret;

    start = 0;
    flags = 0;
    if (argc == 1)
    {
        ret = basic_stuf(".", flags, 0, 0);
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