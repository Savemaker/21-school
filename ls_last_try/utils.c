#include "ft_ls.h"

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

int   print_file_name(char *path, int off, char *buf)
{
    int i;

    i = 0;
    while (path[i])
        buf[off++] = path[i++];
    buf[off++] = '\n';
    return (off);
}