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

int main()
{
    t_dir *list;
    t_dir *head = NULL;
    DIR *dir;
    struct stat s;
    struct dirent *d;
    char *timer;
    time_t *save;
    time_t cur;
    time_t a;
    //15778458
    dir = opendir(".");
    while ((d = readdir(dir)) != NULL)
    {
        if (d->d_name[0] != '.')
        {
            list = new_list(d->d_name, ".", 0);
            append(&head, list);
        }
    }
    lstat(head->path, &s);
    a = s.st_mtime;
    timer = ctime(&a);

    //16070400
    time_t now;
    time_t then;
    time_t difference;

    now = time(NULL);
    then = s.st_mtime;
    difference = now - then;
    printf("%s", timer);
}
