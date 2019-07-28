/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:16:34 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/07/23 15:21:03 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/types.h>
# include <sys/acl.h>
# define BUF_SIZE 8000000

typedef struct		s_dir{
	char			*name;
	char			*path;
	int				special_file;
	int				extended;
	int				std;
	int				dir;
	int				lnk;
	int				level;
	nlink_t			link;
	off_t			size;
	char			*group;
	char			*user;
	struct s_dir	*next;
}					t_dir;

typedef struct		s_max{
	size_t			max_group;
	size_t			max_user;
	size_t			max_links;
	off_t			max_size;
	int				max_major;
	int				max_minor;
}					t_max;

int					basic_stuf(char *path, int flags, int offset);
t_dir				*open_dir(char *path, int flags);
void				open_dir_create(char *name, char *path, t_dir **head);
void				sorts(t_dir **head, int flags);
int					check_flag(char flag, int flags);
void				merge_sorting(t_dir **list, int (f)(t_dir *, t_dir *));
void				divide_list(t_dir **list, t_dir **b);
t_dir				*merge(t_dir *a, t_dir *b, int (f) (t_dir *, t_dir *));
int					default_sort(t_dir *dir, t_dir *dira);
int					reverse_sort(t_dir *dir, t_dir *dira);
int					time_sort(t_dir *dir, t_dir *dira);
int					time_reverse_sort(t_dir *dir, t_dir *dira);
int					print_dir_content(t_dir *list, int flags, int n, char *arg);
int					print_file_name(char *path, char *buf);
int					print_total(char *buf, int off, t_dir *list);
int					write_total(char *buf, int off);
int					print_dir_content_st(t_dir *list, char *tb, int off, int f);
t_max				*new_max(t_dir *list);
void				init_res_max(t_max *res);
void				pwuid_max(t_max *res, uid_t st_uid, t_dir *list);
void				grgid_max(t_max *res, gid_t st_gid, t_dir *list);
void				major_minor(t_max *res, dev_t st_rdev);
int					print_l_flag(char *buf, int off, t_dir *list, t_max *max);
int					print_file_type(char *buf, int off, mode_t st_mode);
int					print_l_rights(char *buf, int off, mode_t st_mode);
int					print_l_extended(char *buf, int off, t_dir *list);
int					print_link_num(char *buf, int off, t_dir *list, t_max *max);
int					space(int m);
int					print_user_nam(char *buf, int off, t_dir *list, t_max *max);
int					print_gr_name(char *buf, int off, t_dir *list, t_max *max);
int					print_std_spaces(t_dir *list, char *buf, int off);
int					check_std_spaces(t_dir *list);
int					print_size(char *buf, int off, t_dir *list, t_max *max);
int					print_maj_min(char *buf, int off, dev_t rdev, t_max *max);
int					print_major(char *buf, int off, dev_t rdev, t_max *max);
int					print_time(char *buf, int off, t_dir *list);
int					check_six_months(time_t stm);
int					print_time_stuff(char *buf, int off, char *time);
int					print_dir_content_stuff_ch(char *tb, int off, t_dir *list);
void				print_file(char *path);
void				fork_and_expand(t_dir *content, char *path, int flags);
void				fork_arg(t_dir *arg, t_dir **dir, t_dir **file, char *path);
int					no_dots_dirs(char *name);
t_dir				*new_list(char *name, char *path, int level);
char				*create_path(char *name, char *path);
void				append(t_dir **head, t_dir *node);
void				expand_list(t_dir **list, int flags);
void				expand_open(t_dir *open, char *path, t_dir **head);
void				expand_head(t_dir **head, t_dir **args, int flags);
void				delete_list(t_dir **list);
int					get_flags(char **args, int *flag);
int					usage(char c);
int					parse_args(char **argv, int flags, int start);
int					arg_len(char **argv, int start);
int					complex_stuf(char **argv, int start, int flags, int off);
void				create_list_append(t_dir **args, char *argv);
void				complex_fork(t_dir *arg, t_dir **dir, t_dir **file);
int					output_files(t_dir *files);
int					print_file_name_comp(char *path);

#endif
