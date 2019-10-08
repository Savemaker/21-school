#include "21sh.h"

int     count_command(char *path)
{
    DIR *dir;
    struct dirent *d;
    int res;

    res = 0;
    dir = opendir(path);
    if (dir != NULL)
    {
        while ((d = readdir(dir)) != NULL)
        {
            if (ft_strcmp(d->d_name, ".") != 0 && ft_strcmp(d->d_name, "..") != 0)
                res++;
        }
		closedir(dir);
    }
    
    return (res);
}

int     counter(void)
{
    char *env;
    int words;
    char **split;
    int count;
    int i;

    i = 0;
    count = 0;
    env = ft_getenv("PATH", g_my_env);
    if (env != NULL)
    {
        words = count_words_delim(env, ':');
        split = ft_split_delim(env, words, ':');
        while (split[i])
        {
            count += count_command(split[i]);
            i++;
        }
		free_parse(split, words);
    }
    return (count);
}

int		hashing(char *name, int size)
{
    int res;
    int i;
	if (size == 0)
		return (0);
	res = 0;
    i = 0;
    while (name && name[i])
    {
        res = (res + name[i]) % size;
        i++;
    }
    return (res);
}

void    get_bin_from_path(char *path, t_hash *new)
{
    DIR *dir;
    struct dirent *d;
    int hash_i;
    dir = opendir(path);
    int cols;
    t_hash_node **node;
    t_hash_node *cur;

    node = new->node;
    cols = 0;
    if (dir != NULL)
    {
        while ((d = readdir(dir))!= NULL)
        {
            if (d->d_name[0] != '.')
            {
                hash_i = hashing(d->d_name, new->quant);
                if (node[hash_i] == NULL)
                {
                    node[hash_i] = (t_hash_node *)malloc(sizeof(t_hash_node) * 1);
                    node[hash_i]->name = ft_strdup(d->d_name);
                    node[hash_i]->path = ft_strdup(path);
                    node[hash_i]->next = NULL;
                }
                else
                {
                    cur = node[hash_i];
                    while (cur->next != NULL)
                        cur = cur->next;
                    cur->next = (t_hash_node *)malloc(sizeof(t_hash_node) * 1);
                    cur->next->name = ft_strdup(d->d_name);
                    cur->next->path= ft_strdup(path);
                    cur->next->next = NULL;
                }
            }
        }
        closedir(dir);
    }
    
}

void    insert_in_table(t_hash *new)
{
    char *env;
    char **split;
    int words;
    int i;

    i = 0;
    env = ft_getenv("PATH", g_my_env);
    if (env != NULL)
    {
        words = count_words_delim(env, ':');
        split = ft_split_delim(env, words, ':');
        while (split[i])
        {
            get_bin_from_path(split[i], new);
            i++;
        }
		free_parse(split, words);
    }
}

t_hash    *create_table(void)
{
    t_hash *new;
    int count;
    int i;

    i = 0;
    count = 0;
    count = counter();
	new = (t_hash *)malloc(sizeof(t_hash) * 1);
    new->quant = count;
    new->node = (t_hash_node **)malloc(sizeof(t_hash_node *) * (count + 1));
    while (i < count)
    {
        new->node[i] = NULL;
        i++;
    }
    insert_in_table(new);
    return (new);
}