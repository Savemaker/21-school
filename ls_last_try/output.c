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

int     print_dir_content(char *buf, t_dir *list, int flags, int off)
{
    int i;

    flags++;
    i = 0;
    while (list)
    {
        i = 0;
        while (list->name[i])
            buf[off++] = list->name[i++];
        if (list->next)
            buf[off++] = ' ';
        else
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