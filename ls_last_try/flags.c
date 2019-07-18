#include "ft_ls.h"

int     usage(char c)
{
    write(1, "ls: illegal option -- ", 22);
    ft_putchar(c);
    ft_putchar('\n');
    write(1, "usage: ./ft_ls [-@Radfglrtu] [file ...]\n", 40);
    return (-1);
}

int     get_flags(char **args, int *flag)
{
    int i;
    int j;

    i = 1;
    while (args[i] && args[i][0] == '-')
    {
        j = 1;
        while (args[i][j])
        {
            if (args[i][j] == '@')
                *flag |= 1 << 0;
           else if (args[i][j] == 'R')
                *flag |= 1 << 1;
            else if (args[i][j] == 'a')
                *flag |= 1 << 2;
           else if (args[i][j] == 'd')
                *flag |= 1 << 3;
            else if (args[i][j] == 'f')
                *flag |= 1 << 4;
           else  if (args[i][j] == 'g')
                *flag |= 1 << 5;
           else if (args[i][j] == 'l')
                *flag |= 1 << 6;
            else if (args[i][j] == 'r')
                *flag |= 1 << 7;
           else  if (args[i][j] == 't')
                *flag |= 1 << 8;
           else  if (args[i][j] == 'u')
                *flag |= 1 << 9;
            else
                return(usage(args[i][j]));

            j++;
        }
        i++;
    }
    return (i);
}

int    check_flag(char flag, int flags)
{
    if (flag == 'R')
        if (((flags >> 1) & 1) == 1)
            return (1);
    if (flag == 'l')
        if (((flags>> 6) & 1) == 1)
            return (1);
    if (flag == 'a')
        if (((flags >> 2) & 1) == 1)
            return (1);
    if (flag == 'r')
        if (((flags >>7) & 1) == 1)
            return (1);
    if (flag == 't')
        if (((flags >> 8) & 1) == 1)
            return (1);
    return (0);
}