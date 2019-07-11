#ifndef FT_LS_H
#define FT_LS_H
#include "libft/includes/libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>

#define BUF_SIZE 55000000

typedef struct s_dir{
	char *name;
	char *path;
	int		level;
	nlink_t link;
	off_t   size;
	char		*group;
	char		*user;
	struct s_dir *next;
	struct s_dir *inside;
	struct s_dir *prev; //delete this shit 
}t_dir;

typedef struct s_max{
	size_t		max_group;
	size_t		max_user;
	size_t		max_links;
	off_t		max_size;
}t_max;

// typedef struct s_stat{
// 	dev_t 		st_dev;
// 	ino_t		st_ino;
// 	mode_t    	st_mode;        /* File type and mode */
//     nlink_t   	st_nlink;       /* Number of hard links */
//     uid_t     	st_uid;         /* User ID of owner */
//    	gid_t     	st_gid;         /* Group ID of owner */
//    	dev_t     	st_rdev;        /* Device ID (if special file) */
//     off_t     	st_size;        /* Total size, in bytes */
// 	blksize_t	st_blksize;     /* Block size for filesystem I/O */
//     blkcnt_t	st_blocks;
// }s_stat;


t_max *new_max(t_dir *list);

// void    print_arg_rec(t_dir *list, char *buf, int flags);
void    correct_list(t_dir **head, int flags);


int     get_flags(char **args, int *flag);
int    	check_flag(char flag, int flags);

t_dir   *new_list(char *name, char *path, int level);
t_dir 	*list_for_output(char *path, int flags);
void    append(t_dir **head, t_dir *node);
void    fork_arg_list(t_dir *arg, t_dir **dir, t_dir **file, char *path);
t_dir   *create_arg_list(char **argv, int flags);

void    expand_list(t_dir **list);

// int     output_rec(t_dir *dir_list, int flags, char *buf, int off);

t_dir   *open_dir(char *path, int flags);

void	sorts(t_dir **head, int flags);
int     default_sort(t_dir *dir, t_dir *dira);
t_dir	*merge(t_dir *a, t_dir *b, int(f)(t_dir *, t_dir *));
void	divide_list(t_dir **list, t_dir **b);
void	merge_sorting(t_dir **list, int (f)(t_dir *, t_dir *));


// //int     output_dir_list(t_dir *dir_list, int flags, int off);
int     print_dir_content(char *buf, t_dir *list, int flags, int off);
// //int    	output_file_list(t_dir *list, int flags);
// int		output_file_names(t_dir *list, int flags);
// int		add_content_to_buf(t_dir *list, int flags, int start); //

char    *create_path(char *name, char *path);
int     arg_len(char **argv, int start);
int    print_file_name(char *path, int off, char *buf); //

int    parse_args(char **argv, int flags, int start, char *buf);
int    	basic_stuf(char *path, int flags, int offset, int c, char *buf);
// void    complex_stuf(char **argv, int flags);
#endif