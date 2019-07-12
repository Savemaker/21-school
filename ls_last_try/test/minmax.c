#include "../ft_ls.h"
#include "../libft/includes/libft.h"
#include <time.h>


void    append(t_dir **head, t_dir *node)
{
	t_dir *temp;

	temp = *head;
	if (*head == NULL)
		*head = node;
	else
    {
		while (temp->next)
			temp = temp->next;
		temp->next = node;
		node->prev = temp;
	}
}

char    *create_path(char *name, char *path)
{
    char *new;
    char *res;

    new = ft_strjoin(path, "/");
    res = ft_strjoin(new, name);
    return (res);
}

t_dir   *new_list(char *name, char *path, int level)
{
    t_dir *new;

    if (!(new = (t_dir *)malloc(sizeof(t_dir))))
        return (NULL);
    new->name = ft_strdup(name);
    if (path == NULL)
        new->path = ft_strdup(name);
    else
        new->path = create_path(name, path);
    new->next = NULL;
    new->prev = NULL;
    new->level = level;
    new->inside = NULL;
    new->user = NULL;
    new->group = NULL;
    new->link = 0;
    new->size = 0;
    return (new);
}

void    print_bits(int test)
{
    int i;
    int res;

    res = 0;
    i = 32;
    while (i--)
    {
        res = ((test >> i) & 1)  + 48;
        write(1, &res, 1);
    }
}

int main()
{
    t_dir *head = NULL;
    t_dir *new;
    dev_t test;

    DIR *dir;
    struct dirent *d;
    struct stat s;

    dir = opendir("/dev");
    while ((d = readdir(dir)) != NULL)
    {
        if (d->d_name[0] != '.')
        {
            new = new_list(d->d_name, "/dev", 0);
            append(&head, new);
        }
    }
    head = head->next;
    lstat(head->path, &s);
    test = s.st_rdev;
    printf("%s\n", head->name);
    printf("%d\n", major(test));
    printf("%d\n", minor(test));
    print_bits(test);
    return (0);
}