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
	int		special_file;
	int		std;
	int lnk;
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
	int			max_major;
	int			max_minor;
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


// void    print_arg_rec(t_dir *list, char *buf, int flags);
void    correct_list(t_dir **head, int flags);





t_dir 	*list_for_output(char *path, int flags);


t_dir   *create_arg_list(char **argv, int flags);



// int     output_rec(t_dir *dir_list, int flags, char *buf, int off);




int     default_sort(t_dir *dir, t_dir *dira);



// //int     output_dir_list(t_dir *dir_list, int flags, int off);

// //int    	output_file_list(t_dir *list, int flags);
// int		output_file_names(t_dir *list, int flags);
// int		add_content_to_buf(t_dir *list, int flags, int start); //

char    *create_path(char *name, char *path);
int     arg_len(char **argv, int start);
 //







int    	basic_stuf(char *path, int flags, int offset, int c, char *buf);
int     complex_stuf(char **argv, int start, int flags, char *buf, int off);
int		parse_args(char **argv, int flags, int start, char *buf);

t_dir   *open_dir(char *path, int flags);

int     print_dir_content(char *buf, t_dir *list, int flags, int off);
int		print_file_name(char *path, int off, char *buf);
int     print_dir_basic_recursive(char *buf, t_dir *dir_list, int flags);

int     print_total(char *buf, int off, t_dir *list);
int     print_l_flag(char *buf, int off, t_dir *list, int flags, t_max *max);
int     print_file_type(char *buf, int off, mode_t st_mode);
int     print_l_rights(char *buf, int off, mode_t st_mode);
int     print_l_extended(char *buf, int off, char *path);
int     print_link_number(char *buf, int off, t_dir *list, t_max *max);
int     print_user_name(char *buf, int off, t_dir *list, t_max *max);
int     print_group_name(char *buf, int off, t_dir *list, t_max *max);
int     print_size(char *buf, int off, t_dir *list, t_max *max);
int     print_major_minor(char *buf, int off, dev_t rdev, t_max *max, t_dir *list);
int     print_time(char *buf, int off, t_dir *list);
int     print_link(char *buf, int off, t_dir *list);

int     get_flags(char **args, int *flag);
int    	check_flag(char flag, int flags);

t_dir   *new_list(char *name, char *path, int level);
t_max 	*new_max(t_dir *list);
void    append(t_dir **head, t_dir *node);
void    fork_arg_list(t_dir *arg, t_dir **dir, t_dir **file, char *path);
void    expand_list(t_dir **list);
void    correct_list(t_dir **head, int flags);

void	sorts(t_dir **head, int flags);
t_dir	*merge(t_dir *a, t_dir *b, int(f)(t_dir *, t_dir *));
void	divide_list(t_dir **list, t_dir **b);
void	merge_sorting(t_dir **list, int (f)(t_dir *, t_dir *));
int		time_reverse_sort(t_dir *dir, t_dir *dira);
int		time_sort(t_dir *dir, t_dir *dira);
int		reverse_sort(t_dir *dir, t_dir *dira);
int     default_sort(t_dir *dir, t_dir *dira);

int     no_dots_dirs(char *name);
char    *create_path(char *name, char *path);
int     arg_len(char **argv, int start);
void    output(char *buf, int ret);
#endif