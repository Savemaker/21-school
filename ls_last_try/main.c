#include "ft_ls.h"

t_dir    *open_dir(char *path, int flags)   // returns sorted list of path content
{
    DIR *dir;
    struct dirent *d;
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
            new = new_list(d->d_name, path, 0);
            append(&head, new);
        }
        else
        {
            if (d->d_name[0] != '.')
            {
                new = new_list(d->d_name, path, 0);
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
        i = print_dir_content(buf, cur, flags, i);
        if (dir_list->next)
            buf[i++] = '\n';
        dir_list = dir_list->next;
    }
    return (i);
}


int    basic_stuf(char *path, int flags, int offset, int c, char *buf)  //flags ???
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
                offset += print_dir_content(buf, content, flags, offset);
            }
            else
                offset = print_file_name(path, offset, buf);
        }
        else
            perror(path);
        if (check_flag('R', flags))
        {
            if (content)
            {
                buf[offset++] = '\n';
                fork_arg_list(content, &dir_list, &file, path);
                expand_list(&dir_list);
                correct_list(&dir_list, flags);
                offset += print_dir_basic_recursive(&buf[offset], dir_list, flags);
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
    while (list)
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

void    expand_list(t_dir **list)
{
    t_dir *args;
    t_dir *new;
    DIR *dir;
    struct stat s;
    struct dirent *d;

    args = *list;
    while (args)
    {
        if (no_dots_dirs(args->name) == 0)
        {
            dir = opendir(args->path);
            if (dir == NULL)
            {
                perror(args->path);
                args = args->next;
                continue;
            }
            while ((d = readdir(dir)) != NULL)
            {
                if (d->d_name[0] != '.')
                {
                    lstat(create_path(d->d_name, args->path), &s);
                    if (S_ISDIR(s.st_mode) == 1)
                    {
                        new = new_list(create_path(d->d_name, args->path), NULL, 1);
                        new->next = args->next;
                        args->next = new;
                    }
                }
            }
            closedir(dir);
        }
        args = args->next;
    }
}

int     complex_stuf(char **argv, int start, int flags, char *buf, int off)
{
    t_dir *new;
    t_dir *args;
    int i;
    struct stat s;
    int st;

    st = 0;
    i = 0;
    args = NULL;
    while (argv[start])
    {
        new = new_list(argv[start], NULL, 0);
        append(&args, new);
        start++;
    }
    sorts(&args, flags);
    while (args)
    {
        i = 0;
        st = lstat(args->name, &s);
        if (st == 0)
        {
            while (args->name[i])
                buf[off++] = args->name[i++];
            buf[off++] = ':';
            buf[off++] = '\n';
        }
        off = basic_stuf(args->name, flags, off, 1, buf);
        if (st == 0)
        {
        if (args->next)
            buf[off++] = '\n';
        }
        args = args->next;
    }
    return (off);
}

int   parse_args(char **argv, int flags, int start, char *buf)
{
    int c;
    int ret;

    c = arg_len(argv, start);
    if (argv[start] == NULL)
       ret = basic_stuf(".", flags, 0, c, buf);
    if (c == 1)
    {
        ret = basic_stuf(argv[start], flags, 0, c, buf);
    }
    if (c > 1)
    {
       ret = complex_stuf(argv, start, flags, buf, 0);
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
    static char *buf;
    int ret;

    buf = (char *)malloc(sizeof(char) * BUF_SIZE);
    buf[BUF_SIZE] = '\0';
    start = 0;
    flags = 0;
    if (argc == 1)
    {
        ret = basic_stuf(".", flags, 0, 0, buf);
    }
    if (argc > 1)
    {
        start = get_flags(argv, &flags);
        ret = parse_args(argv, flags, start, buf);
    }
    output(buf, ret);
    return (0);
}