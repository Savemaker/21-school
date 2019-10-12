/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bellyn-t <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:55:14 by bellyn-t          #+#    #+#             */
/*   Updated: 2018/12/13 19:17:17 by bellyn-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_lst;
	t_list *dst;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = f(lst);
	dst = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new_lst->next = f(lst)))
		{
			while (dst)
			{
				new_lst = dst;
				dst = dst->next;
				free(new_lst);
			}
		}
		new_lst = new_lst->next;
	}
	return (dst);
}
