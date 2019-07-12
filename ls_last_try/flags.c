#include "ft_ls.h"

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
            if (args[i][j] == 'R')
                *flag |= 1 << 1;
            if (args[i][j] == 'a')
                *flag |= 1 << 2;
            if (args[i][j] == 'd')
                *flag |= 1 << 3;
            if (args[i][j] == 'f')
                *flag |= 1 << 4;
            if (args[i][j] == 'g')
                *flag |= 1 << 5;
            if (args[i][j] == 'l')
                *flag |= 1 << 6;
            if (args[i][j] == 'r')
                *flag |= 1 << 7;
            if (args[i][j] == 't')
                *flag |= 1 << 8;
            if (args[i][j] == 'u')
                *flag |= 1 << 9;
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