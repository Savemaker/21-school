/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:48:14 by bellyn-t          #+#    #+#             */
/*   Updated: 2019/09/08 13:48:17 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//his scroll when quotes ??
//ctrl d -> cat ???

//autocom
//leaks


#include "minishell.h"





int		str_quantity(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int ft_putchar_int(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (1);
}

t_readline *init_readline(int prompt_size)
{
	struct winsize	win;
	t_readline *input;

//	int savemode = 0;
//
//	if (g_shell->input)
//		savemode = g_shell->input->mode;
	input = ft_memalloc(sizeof(t_readline));
//	input->mode = savemode;
//	ft_bzero(input, sizeof(t_readline));
	input->line = ft_memalloc(MAXLINE);
	input->clipboard = ft_memalloc(MAXLINE);
	if ((ioctl(STDIN_FILENO, TIOCGWINSZ, &win)) == -1)
	{
		ft_putchar('\n');
		perror_cmnd(SHELLNAME, NULL, IOCTLERR);
		exit_clean();
	}
	input->maxwidth = win.ws_col;
	input->maxheight = win.ws_row;
	if (prompt_size >= (input->maxwidth))
	{
		input->prompt_end = prompt_size % (input->maxwidth);
		if (input->prompt_end == 0)
			TDOWN;
	}
	else
		input->prompt_end = prompt_size;
	input->x = input->prompt_end;
	input->prompt_size = prompt_size;
	return (input);
}



void print_line(t_readline *input, int eof)
{
	clear_visible_line(input);
	ft_putstr_fd(input->line, STDOUT_FILENO);
	if (eof)
	    ft_putchar_fd('\n', STDOUT_FILENO);
}



static void	cursor_motion(t_readline *input, char *buf) //ok
{
//	if (!ft_strcmp(buf, tgetstr("nd", NULL)))
//	if (!ft_strcmp(buf, tgetstr("kr", NULL)))
    if (!ft_strcmp(buf, RIGHT_KEY))
		cursor_right(input);

	if (!ft_strcmp(buf, LEFT_KEY))
//	if (!ft_strcmp(buf, tgetstr("kl", NULL)))
		cursor_left(input);
//	if (!ft_strcmp(buf, tgetstr("ku", NULL)))
	else if (!ft_strcmp(buf, UP_KEY))
		cursor_up(input);
//	if (!ft_strcmp(buf, tgetstr("kd", NULL)))
	else if (!ft_strcmp(buf, DOWN_KEY))//
		cursor_down(input);
	else if (!ft_strcmp(buf, CTRL_A) || !ft_strcmp(buf, FN_LEFT)) ////ctrl A  || fn < (home)
//	else if (!ft_strcmp(buf, CTRL_A) || !ft_strcmp(buf,tgetstr("kh", NULL))) ////ctrl A  || fn < (home)
		goto_start(input);
	else if (!ft_strcmp(buf, CTRL_E) || !ft_strcmp(buf, FN_RIGHT)) ////ctrl E  || fn > (end)
//	else if (!ft_strcmp(buf, CTRL_E) || !ft_strcmp(buf, tgetstr("kh", NULL)))
		goto_end(input);
	else if (!ft_strcmp(buf, CTRL_F))
		goto_next_word(input);
	else if (!ft_strcmp(buf, CTRL_B))
		goto_prev_word(input);

}





void	add_autocomlst(t_autocom **alst, t_autocom *new)
{
	if (alst != NULL && new != NULL)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_autocom	*new_autocomlst(char *content, size_t content_size, int select)
{
	t_autocom	*lstnew;
	char	*cp_content;
	size_t	cp_content_size;


	if (!(lstnew = (t_autocom *)malloc(sizeof(t_autocom))))
		return (NULL);
	if (content == NULL)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
	}
	else
	{
		if (!(cp_content = ft_memalloc(content_size)))
		{
			free(lstnew);
			return (NULL);
		}
		ft_memcpy(cp_content, content, content_size);
		lstnew->content = cp_content;

		ft_strcat(lstnew->content, "\0");//

		cp_content_size = content_size;
		lstnew->content_size = cp_content_size;
	}
	lstnew->select = select;
	lstnew->next = NULL;
	return (lstnew);
}

int autocom_lstsize(t_autocom *lst)
{
	int i = 0;

	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	autocom_addpath(t_autocom **list, char *clear_path, char *request_path, int current, int bin)
{
    char *full_path;
    DIR *dir;
    struct dirent	*dir_ptr;
    struct stat stat;
    t_autocom *newlist;

    int i = 0;

	if ((dir = opendir(clear_path)))
	{
if (!request_path)
{
	while ((dir_ptr = readdir(dir)))
	{
		if (dir_ptr->d_name[0] != '.')
		{

			i = autocom_lstsize(*list);
			full_path = ft_memalloc(MAXLINE);
			if (!current && !bin) {

				full_path = ft_strcpy(full_path, clear_path);
				full_path = ft_strcat(full_path, "/");
			}
			full_path = ft_strcat(full_path, dir_ptr->d_name);


			if (!bin) {
				if (lstat(full_path, &stat) == -1)
					perror_cmnd(SHELLNAME, NULL, LSTATERR);
				if (S_ISDIR(stat.st_mode)) {
					full_path = ft_strcat(full_path, "/");
				}

			}

//            	ft_putstr("\nindex num :");
//            	ft_putnbr(i);
			ft_strcat(full_path, "\0");

			if (g_shell->auto_quantity != 0 && g_shell->autocom_index - 1 + i == g_shell->auto_quantity)
				newlist = new_autocomlst(full_path, ft_strlen(full_path), 1);
			else
				newlist = new_autocomlst(full_path, ft_strlen(full_path), 0);
			add_autocomlst(list, newlist);
			free(full_path);

		}

	}
	closedir(dir);
	return;
}




        while ((dir_ptr = readdir(dir)))
        {
            if (dir_ptr->d_name[0] != '.' && !ft_strncmp(dir_ptr->d_name, request_path, ft_strlen(request_path)))
            {

				i = autocom_lstsize(*list);
				full_path = ft_memalloc(MAXLINE);
            	if (!current && !bin)
				{

					full_path = ft_strcpy(full_path, clear_path);
					full_path = ft_strcat(full_path, "/");
				}
            		full_path = ft_strcat(full_path,dir_ptr->d_name);


            	if (!bin)
				{
					if (lstat(full_path, &stat) == -1)
						perror_cmnd(SHELLNAME, NULL, LSTATERR);
					if (S_ISDIR(stat.st_mode))
					{
						full_path = ft_strcat(full_path, "/");
					}

				}


//            	ft_putstr("\nindex num :");
//            	ft_putnbr(i);

            	if (g_shell->auto_quantity != 0 && g_shell->autocom_index - 1 + i == g_shell->auto_quantity)
					newlist = new_autocomlst(full_path, ft_strlen(full_path), 1);
            	else
					newlist = new_autocomlst(full_path, ft_strlen(full_path), 0);
                add_autocomlst(list, newlist);
                free(full_path);

            }
        }
        closedir(dir);
    }
}



int ft_lstsize(t_list *lst)
{
	int i = 0;

	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}




int get_max_width(t_autocom *list)
{
	int maxlen;

	maxlen = 0;

	while (list)
	{
		if ((int)list->content_size > maxlen)
			maxlen = (int)list->content_size;
		list = list->next;
	}
	return (maxlen);
}


//int count_columns(int maxlen)





void set_cols()
{
	int quantity = g_shell->auto_quantity;

	if (quantity % g_shell->auto_rows == 0)
		g_shell->auto_cols = quantity / g_shell->auto_rows;
	else
		g_shell->auto_cols = quantity / g_shell->auto_rows + 1;
}

void set_cols_plus()
{
	int quantity = g_shell->auto_quantity;

	if (quantity % ++(g_shell->auto_rows) == 0)
		g_shell->auto_cols = quantity / g_shell->auto_rows;
	else
		g_shell->auto_cols = quantity / g_shell->auto_rows + 1;
}

void get_rows_cols(t_autocom *lst)
{

	int max_request_width;
	int quantity;
	int win_width;


	win_width = g_shell->input->maxwidth;
	g_shell->auto_cols = g_shell->auto_quantity;
	g_shell->auto_rows = 1;



	max_request_width = get_max_width(lst);
	g_shell->max_request_width = max_request_width;

	quantity = g_shell->auto_quantity;

	if (max_request_width > win_width)
	{
		g_shell->auto_cols = quantity / g_shell->auto_rows;
		g_shell->auto_rows = quantity;
		return ;
	}

	while ((max_request_width + 1) * quantity / g_shell->auto_rows > win_width)
		g_shell->auto_rows++;
	set_cols();

	 while (g_shell->auto_cols * (max_request_width + 1) > win_width)
	 	set_cols_plus();

}


char *get_color(char *path)
{

	struct stat stat;

	if (lstat(path, &stat) != -1)
	{
		if (S_ISDIR(stat.st_mode))
			return (BRED);
		if ((S_IXUSR &stat.st_mode) == S_IXUSR || (S_IXOTH &stat.st_mode) == S_IXOTH )
			return (BGREEN);
	}
	return (WHITE);
}




char  *dispplay_all_compliance(t_autocom *lst)
{




	if (!lst)
		return NULL;

	get_rows_cols(lst);
	if (g_shell->auto_rows > g_shell->input->maxheight)
		return NULL;


	int cur_row = 0;
	int cur_col;

int j;
int i = 0;


	char *buf;
	buf = ft_memalloc(MAXLINE);
	char *response;
	response = NULL;



while (cur_row < g_shell->auto_rows)
{


		cur_col = 0;
		while (lst && cur_col < g_shell->auto_cols)
		{
			j = 0;

			char *color;
			color = BGMAGENTA;
//			color = get_color(lst->content);

			if (lst->select)
			{
				response = ft_strdup(lst->content);
				ft_strcat(buf, color);
				i+= ft_strlen(color);

//				ft_strcat(g_shell->input->line, lst->content);
			}


			ft_strcat(buf, lst->content);
			ft_strcat(buf, RESET);

			i += ft_strlen(RESET);
			i += lst->content_size;
			j += lst->content_size;
			while (j++ <= g_shell->max_request_width && cur_col + 1 < g_shell->auto_cols)
				buf[i++] = ' ';
			lst = lst->next;
			cur_col++;
		}
		cur_row++;
		if (cur_row != g_shell->auto_rows)
			buf[i++] = '\n';
		else
			buf[i++] = '\0';

}

//	ft_strcat(buf, RESET);


	g_shell->autocom_buf = buf;

//ft_putstr("\n");
//ft_putstr(g_shell->autocom_buf);

	return (response);
}

char	*autocom_path(t_autocom **list, char *searching_path, char *request_path)
{
	char	*clear_path;

	clear_path = ft_memalloc(MAXLINE);
	ft_strncpy(clear_path, searching_path, ft_strlen(searching_path) - ft_strlen(request_path));


	autocom_addpath(list, clear_path, request_path + 1, 0, 0);

//
//	if (!autocom_lstsize(*list))
//		return (NULL);
//    if (autocom_lstsize(*list) == 1)
//		return ((char *)(*list)->content);

//	g_shell->auto_quantity = autocom_lstsize(*list);
//	if (!g_shell->auto_quantity)
//		return (NULL);
//	if (g_shell->auto_quantity == 1)
//		return ((*list)->content);
//
//
//	dispplay_all_compliance(*list);
//
//    return ("display all answers");
	g_shell->auto_quantity = autocom_lstsize(*list);
	if (!g_shell->auto_quantity)
		return (NULL);
	if (g_shell->auto_quantity == 1)
		return ((*list)->content);


//	char *response;
//	response = dispplay_all_compliance(*list);


	return (dispplay_all_compliance(*list));
}







char	*dir_autocom(t_autocom **list, char *request)
{

	char **all_bins;
	int	 i;
	char *bin_path;

	//from system
	all_bins = ft_strsplit(ft_getenv("PATH"), ':');
	i = 0;
	while (all_bins[i])
	{
		bin_path = ft_memalloc(MAXLINE);
		bin_path = ft_strcpy(bin_path, all_bins[i]);
		autocom_addpath(list, bin_path, request, 0, 1);
		free(bin_path);
		i++;
	}
	if (all_bins)
		clean_env(all_bins);
	//from current directory
	autocom_addpath(list, ".", request, 1, 0);


	g_shell->auto_quantity = autocom_lstsize(*list);
	if (!g_shell->auto_quantity)
		return (NULL);
	if (g_shell->auto_quantity == 1)
		return ((*list)->content);


//	char *response;
//	response = dispplay_all_compliance(*list);


	return (dispplay_all_compliance(*list));
}



void tilde_to_path(char *homepath, char **request)
{
	char *tmp;
	tmp = ft_memalloc(MAXLINE);

	homepath = ft_getenv("HOME");
	ft_strcpy(tmp, homepath);
	ft_strcat(tmp, "/");
	ft_strcat(tmp, *request + 2);
	ft_bzero(*request, MAXLINE);
	ft_strcpy(*request, tmp);
	free(tmp);
}

char *path_to_tilde(char *homepath, char *response)
{
	char *newresponse;

	newresponse = ft_memalloc(MAXLINE);
	newresponse = ft_strcpy(newresponse, "~");
	newresponse = ft_strcat(newresponse, response + ft_strlen(homepath));
	return (newresponse);
}






//char *create_buf(t_list *lst, int cols, int max_request_width)
//{
//	int curr_col = 0;
//
//	char *buf = ft_memalloc(MAXLINE);
//	int i;
//
//	i = 0;
//	int j;
//	char *name;
//	while (lst && ++curr_col <= cols)
//	{
//		name = (char *)lst->content;
////
////		j = 0;
////		while (lst->content)
////			buf[i++] = name[j++];
////		while (j++ <= max_request_width && curr_col != cols)
////			buf[i++] = ' ';
//		lst = lst->next;
//	}
//	buf[i] = '\0';
//	return (buf);
//}



//char  *dispplay_all_compliance(t_autocom *lst)
//{
//	int cols;
//	int rows;
//
//	int max_request_width;
//
//	max_request_width = get_max_width(lst);
//	if (!lst || max_request_width > g_shell->input->maxwidth)
//		return NULL;
//
//	cols = count_columns(max_request_width);
////	ft_putstr("\n");
////	ft_putnbr(cols);
//
//	rows = (g_shell->vals_quantity/ cols);
//	if (!rows)
//		rows = 1;
//
////	ft_putstr("\n");
////	ft_putnbr(rows);
//	if (rows > g_shell->input->maxheight)
//		return NULL;
////
////
//	int curr_row = 0;
//	int curr_col;
//////	char *buf;
//	int j;
//	char *response;
//	response = NULL;
//
//
//	char *test;
//	test = NULL;
//	while (lst && ++curr_row <= rows) {
//		curr_col = 0;
//		while (lst && ++curr_col <= cols)
//		{
//			j = (int)lst->content_size;
//			g_shell->autocom_buf = ft_strcat(g_shell->autocom_buf, get_color(lst->content));
//
//			if (lst->select)
//			{
//				g_shell->autocom_buf = ft_strcat(g_shell->autocom_buf, BGMAGENTA);
//
//				test = ft_strdup(lst->content);
////				response = ft_strdup(lst->content);
//			}
//
//////			ft_putstr(get_color(lst->content));
//			g_shell->autocom_buf = ft_strcat(g_shell->autocom_buf, lst->content);
//////			ft_putstr((char *)lst->content);
//			g_shell->autocom_buf = ft_strcat(g_shell->autocom_buf, RESET);
//			while (j++ <= max_request_width && curr_col != cols)
//				g_shell->autocom_buf = ft_strcat(g_shell->autocom_buf, " ");
//			lst = lst->next;
//		}
//	}
////	g_shell->autocom_buf = ft_strcat(g_shell->autocom_buf, "\0");
//
//
//
//	if (g_shell->autocom_buf)
//	{
//
//
////		while (--rows)
////			TUP;
//
////		TCLEAR_STR;
////	ft_putstr(test); //response !!!
//
//
//		goto_end(g_shell->input);
//		TLEFT_BORDER;
//		TDOWN;
//		TCLEAR_STR;
//		ft_putstr(g_shell->autocom_buf);
//
//
//
//
//
//
//		while (rows--)
//			TUP;
//		goto_lastsymb(g_shell->input);
//
//	}
//	return response;
//
//}

char	*get_autocom(char *request)
{

	char	*response;
	char *request_path;
	int reassign;
	t_autocom	*list;
//
    response = NULL;
	set_input_tmode();
	list = NULL;
	reassign = 0;


	if (!ft_strncmp(request, "~/", 2))
	{
		reassign = 1;
		tilde_to_path(ft_getenv("HOME"), &request);
	}

	if ((request_path = ft_strrchr(request, '/')))
		response = autocom_path(&list, request, request_path);
	else
        response = dir_autocom(&list, request);

	if (reassign && response)
		response = path_to_tilde(ft_getenv("HOME"), response);


	return (response);
}


void autocom(t_readline *input)
{
	
	char *response;

	int bufsize;




	ft_bzero(g_shell->autocom_buf, MAXLINE);

	if (g_shell->autocom_index == 0)
		g_shell->old_request = ft_strdup(input->line);

	if (g_shell->autocom_index <= g_shell->auto_quantity)
		g_shell->autocom_index += 1;
	else
		g_shell->autocom_index = 2;


	char *answer;
	if (g_shell->autocom_buf)
		answer = get_autocom(g_shell->old_request);
	else
		answer = get_autocom(input->line);



	if (!answer)

	{	TBELL;
		return;
	}
	response = ft_strdup(answer);
//	ft_putstr(response);




	bufsize = (int)ft_strlen(response) - input->size;
	if (input->size < MAXLINE - bufsize)
	{
//		if (g_shell->autocom_buf)
//		{
//			int rowsnum = g_shell->auto_rows - 1;
//			while (rowsnum--)
//				TUP;
//		}


		goto_start(input);
        ft_bzero(input->line, MAXLINE);
		input->line = ft_strcpy(input->line, response);
		free(response);
		clear_visible_line(input);
		ft_putstr(input->line);


//
		if (g_shell->auto_quantity > 1)
		{
			TDOWN;
			TCLEAR_STR;
			ft_putstr(g_shell->autocom_buf);

			int rows_n = g_shell->auto_rows;
			while (rows_n--)
			{
//				TCLEAR_STR;
				TUP;

			}
		}

		goto_start(input);

//		TLEFT_BORDER;
		input->size += bufsize;
		bufsize = input->size;
		while (bufsize-- > 0)
			cursor_right(input);

//		goto_lastsymb(input);
//		while (bufsize-- > 0)
//			cursor_right(input);
	}
	else
		TBELL;


}

void line_editing(char *buf, t_readline *input, t_history *history)
{
	if (g_shell->inputmode != HISTORY_INPUT_STOP)
	{
		if (ft_isprint(buf[0]))
		{
			char_enter(buf, input);
//			return (0); //stop reading
		}
		if (!ft_strcmp(buf, DEL))
			del_leftchar(input);
	}

	if (g_shell->inputmode != HISTORY_INPUT)
    {

//        if (!ft_strcmp(buf, "\t"))//???

       if (buf[0] == 9)
	   {
       	g_shell->inputmode = AUTOCOM_INPUT;
       	autocom(input);
	   }

        if (!ft_strcmp(buf, FN_DEL))
            del_rightchar(input); //fn del
        else if (buf[0] == 12) //form feed
            clear_screen(input);
//        else if (buf[0] == ???)
//        	char_enter(input->clipboard, input); //paste
        else if (buf[0] == 24) //ctrl X
            cut_after_cursor(input);
		else if (buf[0] == 8) //ctrl h
            copy_before_cursor(input);
		else if (buf[0] == 11) //ctrl k
            copy_after_cursor(input);
		else if (!ft_strcmp(buf, FN_UP))
            scroll_his_back(input, history);
		else if (!ft_strcmp(buf, FN_DOWN))
            scroll_his_forward(input, history);
		else if (buf[0] == 18 && g_shell->inputmode == DEFAULT_INPUT) //ctrl R
		{
			g_shell->inputmode = HISTORY_INPUT;
			his_search();
		}
    }


//    if (buf[0] == ) ???
    //		cut_before_cursor(input);
}

void add_to_histfile()
{
	int		fd;
	int	i;
	char *path;

	path = g_shell->history->path;
	if ((fd = open(path, O_RDWR | O_TRUNC)) == -1)
		perror_cmnd(SHELLNAME, NULL, OPENERR);
	else
	{
		if (g_shell->history->index >= HISTFILESIZE)
			i = g_shell->history->index - HISTFILESIZE;
		else
			i = 0;
		while (g_shell->history->cmnds[i])
		{
			ft_putstr_fd(g_shell->history->cmnds[i], fd);
			ft_putchar_fd('\n', fd);
			i++;
		}
	}
	if (close(fd) == -1)
		perror_cmnd(SHELLNAME, NULL, CLOSEERR);
}

void history_add(char *line)
{
	char	**new;
	int		tabsize;
	int		i;
	char 	**tab;

	tab = g_shell->history->cmnds;
	if (tab)
		tabsize = str_quantity(tab) + 1;
	else
		tabsize = 1;
	if (!(new = (char **)malloc(sizeof(char *) * (tabsize + 1))))
		perror_cmnd(SHELLNAME, NULL, MLKERR);
	new[tabsize] = NULL;
	i = 0;
	if (tab)
	{
		while (i < tabsize - 1)
		{
			new[i] = ft_strdup(tab[i]);
			i++;
		}
	}
	new[i] = ft_strdup(line);
	clean_env(g_shell->history->cmnds);
	g_shell->history->cmnds = new;
	g_shell->history->index = tabsize;
	add_to_histfile();
}

void do_ctrl_d()
{
    if (g_shell->input->size == 0 && (g_shell->inputmode == DEFAULT_INPUT || g_shell->inputmode == HISTORY_INPUT))
    {
        reset_input_tmode();
        exit_clean();
    }
    else
        TBELL;
}

void do_ctrl_g(char **line)
{
    TBELL;
    g_shell->error = EXIT_FAILURE;
    ft_bzero(g_shell->input->line, MAXLINE);
    print_line(g_shell->input, 1);
    *line = ft_strdup(g_shell->input->line);
	reset_input_tmode();
}

void do_sigint(char **line) //???
{
	g_shell->error = 1;
	*line = ft_strdup("\0");
//            *line = ft_strdup(ft_strcat(g_shell->input->line, "\0"));
	print_line(g_shell->input, 1);
//	g_shell->sig = 0;
	reset_input_tmode();
}


int action_signs(char *buff, char **line)
{
	if (*buff == EOT)
		do_ctrl_d();

	if (g_shell->sig == SIGINT)
	{
		do_sigint(line);
		return 1;
	}
	if (!ft_strcmp(buff, EOL) && g_shell->inputmode == AUTOCOM_INPUT)
	{

		//стереть баф
		g_shell->inputmode = DEFAULT_INPUT;
		g_shell->autocom_index = 0;
		return 0;
	}


	if (!ft_strcmp(buff, EOL)) // \n
	{

		*line = ft_strdup(ft_strcat(g_shell->input->line, "\0"));
		if (g_shell->inputmode != HISTORY_INPUT && (g_shell->inputmode != HISTORY_INPUT_STOP))
			print_line(g_shell->input, 1);
		if (g_shell->inputmode == AUTOCOM_INPUT)
			return 0;
		return 1;
	}
	if (*buff == CTRL_G && g_shell->inputmode != HISTORY_INPUT) //bell
	{
		do_ctrl_g(line);
		return 1;
	}
	return (0);
}

void readline_cmnd(char **line, int prompt_size)
{
	char	buff[MAXREAD];

	set_input_tmode();
	g_shell->input = init_readline(prompt_size);
	g_shell->error = 0;
	while (1)
	{
		signals(0);
		ft_bzero(buff, MAXREAD);
		read(STDIN_FILENO, buff, MAXREAD);
		if (g_shell->inputmode != HISTORY_INPUT && (g_shell->inputmode != HISTORY_INPUT_STOP))
			cursor_motion(g_shell->input, buff);
		line_editing(buff, g_shell->input, g_shell->history);
		if (action_signs(buff, line)) //ctrl d c g // sig int // \n
		{
			reset_input_tmode();
			return;
		}
	}
}


int check_heredoc(char *str)
{
	int i;

	i = 0;
	while (str && str[i] && str[i + 1] && str[i + 2])
	{
		if (str[i] == 60 && str[i + 1] == 60 && str[i + 2] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void heredoc_output(char *str)
{
	char *word;

	word = ft_strrchr(str, '<');
	word += 2;
//	char *cropw;
//	cropw = ft_memalloc(MAXLINE);
	int i = 0;
//	int j = 0;

	while (!ft_isspace(word[i]))
		i++;


	ft_strncpy(g_shell->main_cmnd, word, i);
	ft_putstr(g_shell->main_cmnd);
//
}

void	cmnd_loop()
{
	char	*line;
	int status;


	status = 1;
	line = NULL;
	int q_type;

	while (status)
	{

		signals(0);
		set_input_tmode();
		g_shell->main_cmnd = ft_memalloc(MAXLINE); //free!
		g_shell->autocom_buf = ft_memalloc(MAXLINE);
		g_shell->inputmode = DEFAULT_INPUT;
		g_shell->sig = 0;
		readline_cmnd(&line, display_prompt());


		if (ft_strcmp(line, "\0") && !g_shell->sig) {

			if ((q_type = check_quote(line)) && g_shell->inputmode == DEFAULT_INPUT)
			{
				quote_output(line, q_type);
				ft_putstr_fd(g_shell->main_cmnd, 0);
			}

			else if (check_heredoc(line))
			{
//				ft_strcpy(g_shell->main_cmnd, "\0");
				ft_strcpy(g_shell->main_cmnd, "\n");
				heredoc_output(line);
			}
			else
				ft_strcpy(g_shell->main_cmnd, line);
			if (g_shell->inputmode != HISTORY_INPUT && (g_shell->inputmode != HISTORY_INPUT_STOP))// && g_shell->inputmode != QUOTE_INPUT)
				history_add(g_shell->main_cmnd);
			if (g_shell->inputmode != QUOTE_INPUT)
				action(g_shell->main_cmnd);
			else
				perror_cmnd(SHELLNAME, g_shell->main_cmnd, CMNDNTFND);
		}

	}

}
