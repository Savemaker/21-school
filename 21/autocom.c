//
// Created by Ben bushy Ellyn tarbeck on 19/10/2019.
//

#include "minishell.h"

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
        cp_content = ft_strdup(content);
        //ft_memcpy(cp_content, content, content_size);
        lstnew->content = cp_content;
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

//void	autocom_addpath(t_autocom **list, char *clear_path, char *request_path, int current, int bin)
//{
//    char *full_path;
//    DIR *dir;
//    struct dirent	*dir_ptr;
//    struct stat stat;
//    t_autocom *newlist;
//
//    int i = 0;
//
//	if ((dir = opendir(clear_path)))
//	{
//if (!request_path)
//{
//	while ((dir_ptr = readdir(dir)))
//	{
//		if (dir_ptr->d_name[0] != '.')
//		{
//
//			i = autocom_lstsize(*list);
//			full_path = ft_memalloc(MAXLINE);
//			if (!current && !bin) {
//
//				full_path = ft_strcpy(full_path, clear_path);
//				full_path = ft_strcat(full_path, "/");
//			}
//			full_path = ft_strcat(full_path, dir_ptr->d_name);
//
//
//			if (!bin) {
//				if (lstat(full_path, &stat) == -1)
//					perror_cmnd(SHELLNAME, NULL, LSTATERR);
//				if (S_ISDIR(stat.st_mode)) {
//					full_path = ft_strcat(full_path, "/");
//				}
//
//			}
//
////            	ft_putstr("\nindex num :");
////            	ft_putnbr(i);
//			ft_strcat(full_path, "\0");
//
//			if (g_shell->auto_quantity != 0 && g_shell->autocom_index - 1 + i == g_shell->auto_quantity)
//				newlist = new_autocomlst(full_path, ft_strlen(full_path), 1);
//			else
//				newlist = new_autocomlst(full_path, ft_strlen(full_path), 0);
//			add_autocomlst(list, newlist);
//			free(full_path);
//
//		}
//
//	}
//	closedir(dir);
//	return;
//}
//        while ((dir_ptr = readdir(dir)))
//        {
//            if (dir_ptr->d_name[0] != '.' && !ft_strncmp(dir_ptr->d_name, request_path, ft_strlen(request_path)))
//            {
//
//				i = autocom_lstsize(*list);
//				full_path = ft_memalloc(MAXLINE);
//            	if (!current && !bin)
//				{
//
//					full_path = ft_strcpy(full_path, clear_path);
//					full_path = ft_strcat(full_path, "/");
//				}
//            		full_path = ft_strcat(full_path,dir_ptr->d_name);
//
//
//            	if (!bin)
//				{
//					if (lstat(full_path, &stat) == -1)
//						perror_cmnd(SHELLNAME, NULL, LSTATERR);
//					if (S_ISDIR(stat.st_mode))
//					{
//						full_path = ft_strcat(full_path, "/");
//					}
//
//				}
//
////            	ft_putstr("\nindex num :");
////            	ft_putnbr(i);
//
//            	if (g_shell->auto_quantity != 0 && g_shell->autocom_index - 1 + i == g_shell->auto_quantity)
//					newlist = new_autocomlst(full_path, ft_strlen(full_path), 1);
//            	else
//					newlist = new_autocomlst(full_path, ft_strlen(full_path), 0);
//                add_autocomlst(list, newlist);
//                free(full_path);
//
//            }
//        }
//        closedir(dir);
//    }
//}



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


void print_buf()
{
	goto_inputstart(g_shell->input);
	TDOWN;
	TLEFT_BORDER;
	ft_putstr(g_shell->autocom_buf);
while (g_shell->auto_rows--)
	TUP;
//cursor up
}

//void dispplay_all_compliance(t_autocom *lst)
//{
//
//
//	int cur_row = 0;
//	int cur_col;
//	char *buf;
//	char *response;
//
//
//	int j;
//	int i = 0;
//
//    if (!lst)
//        return ;
//    get_rows_cols(lst);
//    if (g_shell->auto_rows > g_shell->input->maxheight)
//        return ;
//
//
//    buf = ft_memalloc(MAXLINE);
//    response = NULL;
//    while (cur_row < g_shell->auto_rows)
//    {
//        cur_col = 0;
//        while (lst && cur_col < g_shell->auto_cols)
//        {
//            j = 0;
//            char *color;
//            color = BGMAGENTA;
////			color = get_color(lst->content);
//
//            if (lst->select)
//            {
//                response = ft_strdup(lst->content);
//	            buf = ft_strjoin(buf, color);
//                i+= ft_strlen(color);
//
//
////                clear_input(g_shell->input);
////	            g_shell->input->line = ft_strcpy(g_shell->input->line, lst->content);
////                char_enter(buf, g_shell->input);
//
//
//
//
////				ft_strcat(g_shell->input->line, lst->content);
//            }
//
//
//            buf = ft_strjoin(buf, lst->content);
//            buf = ft_strjoin(buf, RESET);
//
//            i += ft_strlen(RESET);
//            i += lst->content_size;
//            j += lst->content_size;
//            while (j++ <= g_shell->max_request_width && cur_col + 1 < g_shell->auto_cols)
//                buf[i++] = ' ';
//            lst = lst->next;
//            cur_col++;
//        }
//        cur_row++;
//        if (cur_row != g_shell->auto_rows)
//            buf[i++] = '\n';
//        else
//            buf[i++] = '\0';
//    }
//
////	ft_strcat(buf, RESET);
//    g_shell->autocom_buf = buf;
//
////    ft_putchar('\n');
////    ft_putstr(buf);
////    print_buf();
////    return (response);
//}


void    list_cycle(t_autocom **list)
{
	t_autocom *cur;
	t_autocom *tmp;

	cur = *list;
	tmp = *list;
	if (cur == NULL)
		return ;
	while (cur)
	{
		if (cur->next == NULL)
		{
			cur->next = tmp;
			return;
		}
		cur = cur->next;
	}
}

void autocom_addpath(t_autocom **list, char *clear_path, char *request_path)           //rp = word         clear_path = path
{
    char *full_path;
    DIR *dir;
    struct dirent *dir_ptr;
    struct stat stat;
    t_autocom *newlist;

    int i = 0;
    if ((dir = opendir(clear_path)))
    {
        while ((dir_ptr = readdir(dir)))
        {
//
            if (dir_ptr->d_name[0] != '.' && !ft_strncmp(dir_ptr->d_name, request_path, ft_strlen(request_path)))
            {

                i = autocom_lstsize(*list);
                // full_path = (char *)malloc(sizeof(char) * MAXLINE);

//                if (!current && !bin) {
//
//                    full_path = ft_strcpy(full_path, clear_path);
//                    full_path = ft_strcat(full_path, "/");
//                }
//                full_path = ft_strcat(full_path, dir_ptr->d_name);

// ft_bzero(full_path, MAXLINE);
//                 full_path = ft_strcpy(full_path, dir_ptr->d_name);

//full_path = ft_strdup("/Users/bellyn-t/Desktop");

//                if (!bin)
//                {


full_path = ft_strdup(dir_ptr->d_name);

char *killme;
killme = ft_strjoin(clear_path, "/");
killme = ft_strjoin(killme, full_path);
                    if (lstat(killme, &stat) != -1 )
                    {
	                    if (S_ISDIR(stat.st_mode)) {
		                    full_path = ft_strjoin(full_path, "/");
	                    }
                    }
//
//

//                        full_path = ft_strcat(full_path, "");
//                }
//                ft_putstr("\nindex num :");
//                ft_putnbr(i);
                if (g_shell->auto_quantity != 0 && g_shell->autocom_index  + i == g_shell->auto_quantity)
                    newlist = new_autocomlst(full_path, ft_strlen(full_path), 1);
                else
                    newlist = new_autocomlst(full_path, ft_strlen(full_path), 0);
                add_autocomlst(list, newlist);
                free(full_path);
            }
        }
        closedir(dir);
//        list_cycle(list);
    }
}




void enter_response(char *response, int first_part, int response_len, t_readline *input) //fuck!!!
{
      //  char	*residue;
        int		bufsize;

//        int posend = first_part + response_len + 1;
		input->size -= response_len;
        bufsize = (int)ft_strlen(response);

        while (response_len--)
        	cursor_left(input);
        if (input->size < MAXLINE - bufsize)
        {
//        	if (input->size > posend)
//        	    residue = ft_strsub(input->line, (unsigned)(posend), (size_t)input->size - posend);

            ft_bzero(input->line + first_part + 1, (size_t)(MAXLINE - (first_part + 1)));
            // ft_bzero(input->line, MAXLINE);
	        input->line = ft_strcat(input->line, response);
	        input->line = ft_strcat(input->line, "\0");
//	        if (input->size > posend)
//		        input->line = ft_strcat(input->line, residue);
	        clear_visible_line(input);
	        ft_putstr(input->line);
	        input->size += bufsize;
	       goto_lastsymb(input);
	        while (bufsize-- > 0)
		        cursor_right(input);
//	        if (posend > 2)
//	            free(resimakdue);

        }
        else
            TBELL;
}

void tilde_to_path(char **request)
{
//	char *tmp;
	char *homepath;

//	tmp = ft_memalloc(MAXLINE);
	homepath = ft_getenv("HOME");

	ft_strcpy(*request, homepath);
	ft_strcat(*request, "/");
//	ft_strcat(tmp, *request);
//	ft_bzero(*request, MAXLINE);


//	ft_strcpy(*request, tmp);
//	free(tmp);
}

char *path_to_tilde(char *homepath, char *response)
{
	char *newresponse;

	newresponse = ft_memalloc(MAXLINE);
	newresponse = ft_strcpy(newresponse, "~");
	newresponse = ft_strcat(newresponse, response + ft_strlen(homepath));
	return (newresponse);
}

void search_auto_path(t_autocom **list, char *searching_path, char *request_path, int req_len)
{
    char	*path_before_request;
    char *clear_path;
	int reassign;
	int pos;
int flag = 0;

	pos = 0;
	reassign = 0;
    path_before_request = ft_memalloc(MAXLINE);
    clear_path = ft_memalloc(MAXLINE);
    ft_strncpy(path_before_request, searching_path, ft_strlen(searching_path) - req_len - 1); //
    if (ft_strrchr(path_before_request, ' '))
    {
	    clear_path = ft_strrchr(path_before_request, ' ') + 1;
	    flag  = 1;
    }
    else
        clear_path = ft_strcpy(clear_path, path_before_request);

	if (*clear_path == '~')
	{
		reassign = 1;
		tilde_to_path(&clear_path);
	}


	autocom_addpath(list, clear_path, request_path);


    g_shell->auto_quantity = autocom_lstsize(*list);
    if (g_shell->auto_quantity == 0)
        TBELL;
    else if (g_shell->auto_quantity == 1)
    {
    	if (reassign && flag)
    		pos = ft_strlen(path_before_request) - ft_strlen(ft_getenv("HOME"));
	    else
	    	pos = ft_strlen(path_before_request);
        enter_response((*list)->content, pos, ft_strlen(request_path), g_shell->input); // trash
    }

    else
    {
	    t_autocom *current;

	    current = *list;


    	while (*list)
	    {
    		if ((*list)->select == 1)
		    {
			    if (reassign && flag)
				    pos = ft_strlen(path_before_request) - ft_strlen(ft_getenv("HOME"));
			    else
				    pos = ft_strlen(path_before_request);
    			clear_input(g_shell->input);
			    char_enter(searching_path, g_shell->input);
			    enter_response((*list)->content, pos, g_shell->input->size - pos - 1, g_shell->input); // trash (ne govori)
			    return;
		    }
    		*list = (*list)->next;
	    }
    }
}




char *get_autoword(char *request)
{
	char *clearpath;
	char *newrequest;

	int len;

	len = 0;
	clearpath = ft_strdup(request);
	while (clearpath[len] && !ft_isspace(clearpath[len]))
		len++;
    newrequest = ft_memalloc(len + 1);
    newrequest[len + 1] = '\0';
	ft_strncpy(newrequest, clearpath, len + 1);
	return (newrequest);
}


int get_autopos(char *request)
{
	int pos;
	int curpos;
	int i;

	pos = g_shell->input->x - g_shell->input->prompt_end;
	curpos = 0;
	i = 0;
	while (request && i <= pos)
	{
		if (ft_isspace(request[i]))
			curpos = i;
		i++;
	}
	return (curpos);
}

void dir_autocom(char *request)
{

    // char **all_bins;
    // int	 i;
    // char *bin_path;
	t_autocom	*list;

	list = NULL;
//	char *residue = ft_memalloc(MAXLINE);

	char *newrequest;
	int pos;

	pos = get_autopos(request);
	if (pos == 0)
    {
		newrequest = get_autoword(request);
    }
	else
		newrequest = get_autoword(request + pos + 1);

//	ft_putchar('\n');
//	ft_putstr(newrequest);

//	if ((int)(ft_strlen(newrequest) + pos + 1) < g_shell->input->size)
//		residue = ft_strsub(request, pos + 1 + ft_strlen(newrequest), MAXLINE - (pos + ft_strlen(newrequest)));

//		ft_putchar('\n');
//	ft_putstr(residue);

//	char *firstpart = ft_memalloc(MAXLINE);
//	ft_strncpy(firstpart, request, pos);

//    //from system
    // all_bins = ft_strsplit(ft_getenv("PATH"), ':');
    // i = 0;
    // while (all_bins[i])
    // {
    //     // bin_path = ft_memalloc(MAXLINE);
    //     // bin_path = ft_strcpy(bin_path, all_bins[i]);
    //     bin_path = ft_strdup(all_bins[i]);
	// 	autocom_addpath(&list, bin_path, newrequest);//trash
    //     free(bin_path);
    //     i++;
    // }

////    while (list)
////    {
////    	ft_putendl(list->content);
////    	list = list->next;
////    }
//////    if (all_bins)
//////        clean_env(all_bins);
////    //from current directory
	        autocom_addpath(&list, ".", newrequest); //!use
//
    g_shell->auto_quantity = autocom_lstsize(list);
    if (!g_shell->auto_quantity)
        TBELL;
    if (g_shell->auto_quantity == 1)
    {   
//pos = 0;
		if (!pos)
			enter_response((list)->content, -1, ft_strlen(newrequest), g_shell->input); // trash
		else
			enter_response((list)->content, pos, ft_strlen(newrequest), g_shell->input);
        g_shell->old_request = ft_strdup(g_shell->input->line);
//	    char_enter(residue, g_shell->input);
    }
    else
	{
		t_autocom *current;

		current = list;
		while (list)
		{
			if ((list)->select == 1)
			{
				clear_input(g_shell->input);
				char_enter(request, g_shell->input);



				if (!pos)
					enter_response((list)->content, -1, ft_strlen(newrequest), g_shell->input); // trash
				else
					enter_response((list)->content, pos, ft_strlen(newrequest), g_shell->input);


//				ft_putchar('\n');
//				ft_putnbr(pos);
//				enter_response((list)->content, pos, ft_strlen(newrequest), g_shell->input); // trash
				return;
			}
			list = (list)->next;
		}
	}
}



void path_autocom(char *request_path, char *request)
{
	t_autocom	*list;
	char *ok;
	char *tmp;
	int len;

	list = NULL;
	tmp = NULL;
	len = 0;
	if (ft_strchr(request_path, ' '))
	{
		tmp = request_path;
		while (!ft_isspace(*tmp))
		{
			len++;
			tmp++;
		}
		ok = ft_memalloc(MAXLINE);
		if (len > 0)
			ok = ft_strncpy(ok, request_path, len - 1);
		search_auto_path(&list, request, ok, (int)ft_strlen(request_path));
		return;
	}
	search_auto_path(&list, request, request_path, (int)ft_strlen(request_path));
}

void get_autocom(char *request)
{
    char *request_path;

    if ((request_path = ft_strrchr(request, '/')))
    	path_autocom(request_path + 1, request);
	else
        dir_autocom(request);

}

void autocom(t_readline *input)
{

//	char *response;

//	int bufsize;

    g_shell->inputmode = AUTOCOM_INPUT;
	ft_bzero(g_shell->autocom_buf, MAXLINE);//
	if (g_shell->autocom_index == 0)
    {
		g_shell->old_request = ft_strdup(input->line);
    }


////
////
	if (g_shell->autocom_index)
    {
		get_autocom(g_shell->old_request);
    }
	else
    {
		get_autocom(input->line);
    }

	if (g_shell->autocom_index < g_shell->auto_quantity)
		g_shell->autocom_index += 1;
	else
		g_shell->autocom_index = 1;

//    char *answer;
//	if (g_shell->autocom_buf)
//		answer = get_autocom(g_shell->old_request);
//	else
//ft_putstr(input->line);
//ft_putchar('\n');
//ft_putstr(input->line);
// get_autocom(input->line);
//	if (!answer)
//	{	TBELL;
//		return;
//	}
//
//	response = ft_strdup(answer);
//
//    ft_putstr("\n");
//    ft_putstr(answer);
//	ft_putstr(response);
}