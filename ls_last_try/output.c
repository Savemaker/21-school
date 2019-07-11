#include "ft_ls.h"

// int     output_dir_list(t_dir *dir_list, int flags, int off)
// {
//     int i;
//     t_dir *cur;

//     i = 0;
//     int j;
//     j = 0;
//     flags++;
//     if (dir_list)
//     {
//         if (off > 0)
//             buf[off++] = '\n';
//     }
//     while (dir_list)
//     {
//         i = 0;
//         while (dir_list->name[i])
//             buf[off++] = dir_list->name[i++];
//         buf[off++] = ':';
//         buf[off++] = '\n';
//         cur = list_for_output(dir_list->name, flags);
//         off += print_dir_content(&buf[off], cur, flags);
//         if (dir_list->next)
//             buf[off++] = '\n';
//         dir_list = dir_list->next;
//     }   
//     return (off);
// }

int     print_l_rights(char *buf, int off, mode_t st_mode)
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

int     print_l_extended(char *buf, int off, char *path)
{
    ssize_t res;
    char name[1024];

    res = listxattr(path, name, 1024, XATTR_NOFOLLOW);
    if (res == 0)
    {
        buf[off++] = ' ';
        buf[off++] =' ';
    }
    if (res > 0)
    {
        buf[off++] = '@';
        buf[off++] = ' ';
    }
    if (res < 0)
    {
        perror("xattr");
        buf[off++] = ' ';
    }
    return (off);
}

int     print_file_type(char *buf, int off, mode_t st_mode)
{
    if (S_ISDIR(st_mode))
        buf[off++] = 'd';
    if (S_ISBLK(st_mode))
        buf[off++] = 'b';
    if (S_ISCHR(st_mode))
        buf[off++] = 'c';
    if (S_ISLNK(st_mode))
        buf[off++] = 'l';
    if (S_ISSOCK(st_mode))
        buf[off++] = 's';
    if (S_ISFIFO(st_mode))
        buf[off++] = 'p';
    if (S_ISREG(st_mode))
        buf[off++] = '-';
    return (off);
}

int     space(int m)
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

int     print_link_number(char *buf, int off, t_dir *list, t_max *max)
{
    char *res;
    int i;
    int m;
    int j;

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
    buf[off++] = ' ';
    return (off);
}

int     print_user_name(char *buf, int off, t_dir *list, t_max *max)
{
    size_t m;
    int i;
    size_t len;

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

int     print_group_name(char *buf, int off, t_dir *list, t_max *max)
{
    int i;
    size_t len;

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

int     print_size(char *buf, int off, t_dir *list, t_max *max)
{
    char *res;
    int i;
    int m;
    int j;

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
    {
        buf[off++] = res[j++];
    }
    buf[off++] = ' ';
    return (off);
}

int     check_six_months(time_t stm)
{
    time_t now;
    time_t then;
    time_t dif;

    now = time(NULL);
    then = stm;
    dif = now - then;
    if (dif >= 15638400)
        return (1);   //yes 6 months hv pssd
    return (0);
}

int     print_time(char *buf, int off, t_dir *list)
{
    char *time;
    struct stat s;
    int i;
    int check;

    i = 4;
    if (list)
    {
        lstat(list->path, &s);
        check = check_six_months(s.st_mtime);
        time = ctime(&s.st_mtime);
        if (check == 0)
        {
            while (time[i] && i < 16)
            {
                buf[off++] = time[i++];
            }
        }
        else
        {
            while (time[i] && i < 11)
            {
                buf[off++] = time[i++];
            }
            buf[off++] = ' ';
            i = 20;
            while (time[i] != '\n')
                buf[off++] = time[i++];
        }
        buf[off++] = ' ';
    }
    return (off);
}

int     print_l_flag(char *buf, int off, t_dir *list, int flags, t_max *max)
{
    struct stat s;
    flags++; ///useleeesss
    lstat(list->path, &s);
    off = print_file_type(buf, off, s.st_mode);
    off = print_l_rights(buf, off, s.st_mode);
    off = print_l_extended(buf, off, list->path);
    off = print_link_number(buf, off, list, max);
    off = print_user_name(buf, off, list, max);
    off = print_group_name(buf, off, list, max);
    off = print_size(buf, off, list, max);
    off = print_time(buf, off, list);
    return (off);
}

int     print_dir_content(char *buf, t_dir *list, int flags, int off)
{
    int i;
    t_max *max;

    max = new_max(list);
    flags++;
    i = 0;
    while (list)
    {
        i = 0;
        if (check_flag('l', flags))
            off = print_l_flag(buf, off, list, flags, max);
        while (list->name[i])
            buf[off++] = list->name[i++];
        if (list->next)
            buf[off++] = ' ';
        else
            buf[off++] = '\n';
        if (check_flag('l', flags) && list->next)
            buf[off++] = '\n';
        list = list->next;
    }
    return (off);
}

// int    output_file_list(t_dir *list, int flags)
// {
//     flags++;
//     int i;
//     int off;

//     i = 0;
//     off = 0;
//     while (list)
//     {
//         i = 0;
//         while (list->name[i])
//             buf[off++] = list->name[i++];
//         if (list->next)
//             buf[off++] = ' ';
//         list = list->next;
//     }
//     if (i > 0)
//         buf[off++] = '\n';
//     return (off);
// }

// int    output_file_names(t_dir *list, int flags)
// {
//     struct stat s;
//     int off;

//     off = 0;
//     flags++;
//     while (list)
//     {
//         lstat(list->name, &s);
//         if (S_ISREG(s.st_mode) == 1)
//         {
//             off += print_file_name(list->name, off);
//             if (list->next)
//                 buf[off++] = ' ';
//             else
//                 buf[off++] = '\n';
//         }
//         list = list->next;
//     }
//     return (off);
// }

// int   add_content_to_buf(t_dir *list, int flags, int start)
// {
//     int i;

//     i = 0;
//     flags++;
//     while (list)
//     {
//         i = 0;
//         while (list->name[i])
//             buf[start++] = list->name[i++];
//         if (list->next)
//             buf[start++] = ' ';
//         list = list->next;
//     }
//     buf[start++] = '\n';
//     return (start);
// }