#include "ft_ls.h"

t_dir *merge(t_dir *a, t_dir *b, int(f)(t_dir *, t_dir *))
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if ((f(a,b) == 0))
	{
		a->next=merge(a->next, b, f);
		a->next->prev=a;
		a->prev=NULL;
		return (a);
	}
	else
	{
		b->next=merge(b->next, a, f);
		b->next->prev=b;
		b->prev=NULL;
		return (b);
	}
}

void	divide_list(t_dir **list, t_dir **b)
{
	t_dir *fast;
	t_dir *slow;

	slow = *list;
	fast = (*list)->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*b = slow->next;
	slow->next = NULL;
}

void	merge_sorting(t_dir **list, int (f)(t_dir *, t_dir *))
{
	t_dir *a;
	t_dir *b;

	if (*list == NULL || (*list)->next == NULL)
		return ;
	a = *list;
	b = NULL;
	divide_list(list, &b);
	merge_sorting(&a, f);
	merge_sorting(&b, f);
	*list = merge(a, b, f);
}


int     default_sort(t_dir *dir, t_dir *dira)
{
    if (ft_strcmp(dir->name, dira->name) > 0)
        return (1);
    return (0);
}

void sorts(t_dir **head, int flags)
{
	flags++;
    merge_sorting(head, default_sort);
}