#include "ft_ls.h"

int     no_dots_dirs(char *name)
{
    if (ft_strcmp(".", name) == 0)
        return (1);
    if (ft_strcmp("..", name) == 0)
        return (1);
    return (0);
}

int     arg_len(char **argv, int start)
{
    int i;

    i = 0;
    while (argv[start])
    {
        i++;
        start++;
    }
    return (i);
}

char    *create_path(char *name, char *path)
{
    char *new;
    char *res;

    if (ft_strcmp(path, "/") != 0)
        new = ft_strjoin(path, "/");
    else
        new = path;
    res = ft_strjoin(new, name);
    return (res);
}

int   print_file_name(char *path, char *buf)
{
    int i;
    int off;

    off = 0;
    i = 0;
    while (path[i])
        buf[off++] = path[i++];
    buf[off++] = ':';
    buf[off++] = '\n';
    return (off);
}

int   print_file_name_comp(char *path)
{
    int i;
    int off;
    char buf[4096];

    off = 0;
    i = 0;
    while (path[i])
        buf[off++] = path[i++];
    buf[off++] = ':';
    buf[off++] = '\n';
    write(1, buf, off);
    return (off);
}

void    print_file(char *path)
{
    char buf[4096];
    int i;

    i = 0;
    while (path[i])
    {
        buf[i] = path[i];
        i++;
    }
    buf[i++] = '\n';
    write(1, buf, i);
}