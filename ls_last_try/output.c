#include "ft_ls.h"

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
        perror(path);
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

int     print_major_minor(char *buf, int off, dev_t rdev, t_max *max, t_dir *list)
{
    char *res;
    int i;
    int num;
    int spc;
    int until;

    i = 0;
    printf("%s\n", list->name);
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
    i = 0;
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
    return (off);
}

int     print_link(char *buf, int off, t_dir *list)
{
    int res;
    int i;
    char b[1024];

    res = readlink(list->path, b, 1024);
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
    if (list->special_file == 0)
        off = print_size(buf, off, list, max);
    if (list->special_file == 1)
    {
            off = print_major_minor(buf, off, s.st_rdev, max, list);
    }
    off = print_time(buf, off, list);
    return (off);
}

int     print_total(char *buf, int off, t_dir *list)
{
    struct stat s;
    int total;
    char *res;
    int check;

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
        buf[off++] = 't';
        buf[off++] = 'o';
        buf[off++] = 't';
        buf[off++] = 'a';
        buf[off++] = 'l';
        buf[off++] = ' ';
        total = 0;
        while (res[total])
            buf[off++] = res[total++];
        buf[off++] = '\n';
    }
    return (off);
}

int     print_dir_content(char *buf, t_dir *list, int flags, int off)
{
    int i;
    t_max *max;

    max = new_max(list);
    flags++;
    i = 0;
    if (check_flag('l', flags))
    {
       off = print_total(buf, off, list);
    }
    while (list)
    {
        i = 0;
        if (check_flag('l', flags))
        {
            off = print_l_flag(buf, off, list, flags, max);
        }
        while (list->name[i])
            buf[off++] = list->name[i++];
        if (check_flag('l', flags))
            off = print_link(buf, off, list);
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