/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:44:51 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/13 17:07:27 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lstnew;
	void	*cp_content;
	size_t	cp_content_size;

	if (!(lstnew = (t_list *)malloc(sizeof(t_list))))
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
		cp_content_size = content_size;
		lstnew->content_size = cp_content_size;
	}
	lstnew->next = NULL;
	return (lstnew);
}
