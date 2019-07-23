/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:52:28 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/05/03 16:49:52 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * n + 1);
	if (str == NULL)
		return (NULL);
	str = ft_strncpy(str, s, n);
	str[n] = '\0';
	return (str);
}

t_list	*getlist(const int fd, t_list **head)
{
	t_list *tmp;

	if (!head)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(head, tmp);
	return (tmp);
}

int		myread(const int fd, char **content)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmp;
	int		ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		tmp = *content;
		if (!(*content = ft_strjoin(*content, buf)))
			return (-1);
		free(tmp);
		if (ft_strchr(buf, END))
			break ;
	}
	return (ret);
}

size_t	cop(char **line, char *content, char c)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != c)
		i++;
	if (!(*line = ft_strndup(content, i)))
		return (0);
	return (i);
}

int		get_next_line(const int fd, char **line)
{
	t_list			*list;
	char			*tmp;
	char			buf[BUFF_SIZE + 1];
	int				ret;
	static	t_list	*head;

	if (fd < 0 || read(fd, buf, 0) < 0 || !line ||
		!(list = getlist(fd, &head)))
		return (-1);
	tmp = list->content;
	ret = myread(fd, &tmp);
	if (!*tmp && !ret)
		return (0);
	list->content = tmp;
	ret = cop(line, list->content, END);
	tmp = list->content;
	if (tmp[ret] != '\0')
	{
		list->content = ft_strdup(&((list->content)[ret + 1]));
		free(tmp);
	}
	else
		tmp[0] = '\0';
	return (1);
}
