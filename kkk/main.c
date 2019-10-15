/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/15 18:02:54 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		*create_tab(int words)
{
	int *res;
	int i;

	i = 0;
	words++;
	if (!(res = (int *)malloc(sizeof(int) * words)))
		perror_cmnd(SHELLNAME, NULL, MLKERR);
	while (i < words)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

void	copy_split_delim(char **res, char *cmd, char delim)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		k = 0;
		if (cmd[i] == '\0')
			break ;
		while (cmd[i] != '\0' && cmd[i] != delim)
			res[j][k++] = cmd[i++];
		res[j][k] = '\0';
		j++;
	}
}

int		*count_each_word_delim(char *cmd, int words, char delim)
{
	int i;
	int *tab;
	int j;

	i = 0;
	j = 0;
	tab = create_tab(words);
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		while (cmd[i] != '\0' && cmd[i] != delim)
		{
			tab[j]++;
			i++;
		}
		j++;
	}
	return (tab);
}

int		count_words_delim(char *cmd, char delim)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == delim)
			i++;
		if (cmd[i] != '\0')
			w++;
		while (cmd[i] != '\0' && cmd[i] != delim)
			i++;
	}
	return (w);
}

char	**ft_split_delim(char *cmd, int words, char delim)
{
	char	**res;
	int		*tab;
	int		i;

	i = 0;
	tab = count_each_word_delim(cmd, words, delim);
	if (!(res = (char **)malloc(sizeof(char *) * (words + 1))))
		perror_cmnd(SHELLNAME, NULL, MLKERR);
	while (i < words)
	{
		res[i] = (char *)malloc(sizeof(char) * tab[i] + 1);
		i++;
	}
	free(tab);
	res[i] = NULL;
	copy_split_delim(res, cmd, delim);
	return (res);
}

int		check_type_class(t_token *list, int type, int count)
{
	while (list)
	{
		if (list->type == type)
		{
			count -= 1;
			if (count == 0)
			{
				if (ft_strcmp(list->buf, ">") == 0)
					return (1);
				if (ft_strcmp(list->buf, ">>") == 0)
					return (2);
			}
		}
		list = list->next;
	}
	return (0);
}

char	*take_buf(t_token *list, int type, int count)
{
	char	*res;
	int		fd;

	res = NULL;
	while (list)
	{
		if (list->type == type)
		{
			count -= 1;
			if (count == 0)
			{
				res = list->next->buf;
				break ;
			}
			else
			{
				if ((fd = open(list->next->buf, O_RDWR | O_CREAT, 0644)) == -1)
					perror_cmnd(SHELLNAME, NULL, OPENERR);
				if (close(fd) == -1)
					perror_cmnd(SHELLNAME, NULL, CLOSEERR);
			}
		}
		list = list->next;
	}
	return (res);
}

int		check_for_type(t_token *list, int type)
{
	while (list)
	{
		if (list->type == type)
			return (1);
		list = list->next;
	}
	return (0);
}

int		check_for_redir(t_tree *ast, int type)
{
	int res;

	res = 0;
	while (ast)
	{
		if (ast->type == TYPE_REDIR)
		{
			res = check_for_type(ast->current, type);
		}
		ast = ast->right;
	}
	return (res);
}

t_tree	*get_redirs_node(t_tree *ast)
{
	while (ast)
	{
		if (ast->type == TYPE_REDIR)
			return (ast);
		ast = ast->right;
	}
	return (NULL);
}

void	aggregation_order_stuff(t_token *list, int fd, int order)
{
	int num_a;
	int num_b;

	num_a = ft_atoi(list->buf);
	num_b = ft_atoi(list->next->next->buf);
	if (order == 0)
		dup2(num_b, num_a);
	if (order == 1)
		dup2(fd, num_a);
}

void	aggregation_order(t_token *list, int fd)
{
	int order;
	int num_a;

	order = 0;
	while (list)
	{
		if (list->type == TYPE_SUFFIX)
			order = 1;
		if (list->type == 9)
		{
			if (ft_strcmp(list->next->next->buf, "-") == 0)
			{
				num_a = ft_atoi(list->buf);
				close(num_a);
			}
			else
			{
				aggregation_order_stuff(list, fd, order);
				break ;
			}
		}
		list = list->next;
	}
}

int		get_redirections(t_tree *ast, int old, int type, int flag)
{
	int		fd;
	int		count;
	char	*buf;
	t_tree	*redirs;

	fd = 0;
	if (check_for_redir(ast, type))
	{
		redirs = get_redirs_node(ast);
		count = count_token_types(redirs->current, type);
		buf = take_buf(redirs->current, type, count);
		if (type == TYPE_SUFFIX)
		{
			if (check_type_class(redirs->current, type, count) == 1)
			{
				if ((fd = open(buf, O_RDWR | O_CREAT, 0644)) == -1)
					perror_cmnd(SHELLNAME, NULL, OPENERR);
			}
			if (check_type_class(redirs->current, type, count) == 2)
			{
				if ((fd = open(buf, O_RDWR | O_CREAT | O_APPEND, 0644)) == -1)
					perror_cmnd(SHELLNAME, NULL, OPENERR);
			}
		}
		if (type == TYPE_WORD)
			fd = open(buf, O_RDONLY);
		if (flag == 1)
			close(old);
		return (fd);
	}
	return (old);
}


void	copy_realloc_del(char **res, char **envp, int index)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (envp[i])
	{
		if (i == index)
		{
			i++;
			continue;
		}
		j = 0;
		while (envp[i][j])
		{
			res[k][j] = envp[i][j];
			j++;
		}
		res[k][j] = '\0';
		k++;
		i++;
	}
}

char	**realloc_envp_del(int p, char *name, char **envp)
{
	int		i;
	int		j;
	char	**res;
	int		index;

	index = ft_getenv_index(name, envp);
	i = 0;
	j = 0;
	if (!(res = (char **)malloc(sizeof(char *) * (p + 1))))
		perror_cmnd(SHELLNAME, NULL, MLKERR);
	while (i < p)
	{
		if (index == j)
			j++;
		res[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[j]) + 1));
		j++;
		i++;
	}
	res[i] = NULL;
	copy_realloc_del(res, envp, index);
	return (res);
}

void display_no(void)
{
	ft_putstr(BWHITE"NO"RESET" GOD! PLEASE "BWHITE"NO! "RESET BRED"N");
	int loop = g_shell->input->maxwidth - 20;
	while (loop--)
		ft_putstr("O");
	ft_putstr(RESET"\n");
}

int		ft_unsetenv(char *name)
{
	char	**new_env;
	int		p;


	if (!name)
	{
		ft_putstr("usage: unsetenv [name]\n");
		return (1);
	}
		if (ft_getenv(name) != NULL)
		{
			if (!ft_strcmp(name, "HOME"))
			{
				display_no();
				return (1);
			}
			p = count_pointers(g_my_env) - 1;
			new_env = realloc_envp_del(p, name, g_my_env);
			free_copy_envp(&g_my_env);
			g_my_env = NULL;
			g_my_env = new_env;
			if (ft_strcmp("PATH", name) == 0)
			{
				free_hash_table(&g_table);
				g_table = create_table();
			}
			return (1);
		}
		else
			ft_putstr("unsetenv: name not found\n");
	return (1);
}


void	copy_index(char **ress, char *name, char *value)
{
	int		i;
	int		j;
	char	*res;

	res = *ress;
	i = 0;
	while (name[i])
	{
		res[i] = name[i];
		i++;
	}
	res[i++] = '=';
	j = 0;
	while (value[j])
	{
		res[i] = value[j];
		i++;
		j++;
	}
	res[i] = '\0';
}

int		test_getenv(const char *name, char *ret)
{
	size_t i;

	i = 0;
	while (ret[i] && ret[i] != '=')
		i++;
	if (ft_strlen(name) != i)
		return (0);
	return (1);
}

int		ft_getenv_index(const char *name, char **envp)
{
	int		i;
	char	*ret;

	i = 0;
	while (envp[i])
	{
		ret = ft_strstr(envp[i], name);
		if (ret != NULL)
		{
			if (test_getenv(name, envp[i]) == 1)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	copy_to_realloc(char **envp, char **res, char *name, char *value)
{
	int index;
	int i;
	int j;

	index = ft_getenv_index(name, envp);
	i = 0;
	while (envp[i])
	{
		j = 0;
		if (index != i)
		{
			while (envp[i][j] != '\0')
			{
				res[i][j] = envp[i][j];
				j++;
			}
			res[i][j] = '\0';
		}
		if (index == i)
			copy_index(&res[i], name, value);
		i++;
	}
	if (index == -1)
		copy_index(&res[i], name, value);
}

char	*malloc_line(char *name, char *value)
{
	char	*res;
	int		name_len;
	int		value_len;

	name_len = (int)ft_strlen(name);
	value_len = (int)ft_strlen(value);
	res = (char *)malloc(sizeof(char) * (name_len + value_len + 2));
	if (res == NULL)
		return (NULL);
	return (res);
}

char	**realloc_envp(int pointers, char *name, char *value, char **envp)
{
	char	**res;
	int		index;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (pointers + 1));
	index = ft_getenv_index(name, envp);
	if (index == -1)
		--pointers;
	while (i < pointers)
	{
		if (i == index)
			res[i] = malloc_line(name, value);
		else
			res[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		i++;
	}
	if (index == -1)
		res[i++] = malloc_line(name, value);
	res[i] = NULL;
	copy_to_realloc(envp, res, name, value);
	return (res);
}

int		ft_setenv(char *name, char *value)
{
	char	**new_env;
	int		p;

	new_env = NULL;

	if (!name || !value)
	{
		ft_putstr("usage: setenv [name] [value]\n");
		return (1);
	}
	else
	{
		p = count_pointers(g_my_env);
		if (ft_getenv(name) == NULL)
			p++;
		new_env = realloc_envp(p, name, value, g_my_env);
		free_copy_envp(&g_my_env);
		g_my_env = new_env;
		if (ft_strcmp("PATH", name) == 0)
		{
			free_hash_table(&g_table);
			g_table = create_table();
		}
		return (1);
	}
	return (1);
}


//void	update_pwd(char *name, char *oldpath)
//{
//	char **parse;
//	char **old;
//
//	old = (char **)malloc(sizeof(char *) * 4);
//	old[0] = ft_strdup("setenv");
//	old[1] = ft_strdup("OLDPWD");
//	old[2] = ft_strdup(oldpath);
//	old[3] = NULL;
//	parse = (char **)malloc(sizeof(char *) * 4);
//	parse[0] = ft_strdup("setenv");
//	parse[1] = ft_strdup("PWD");
//	parse[2] = ft_strdup(name);
//	parse[3] = NULL;
//	ft_setenv(old, g_my_env);
//	ft_setenv(parse, g_my_env);
//	free_parse(parse, 3);
//	free_parse(old, 3);
//}


//void	ft_cd_stuf(char **parse)
//{
//	int		res;
//	char	*tmp;
//	char	buf[2048];
//	char	old_buf[2048];
//
//	tmp = getcwd(old_buf, 2048);
//	if (ft_strcmp(parse[1], " ") == 0)
//		res = chdir(ft_getenv("HOME", g_my_env));
//	else if (ft_strcmp(parse[1], "-") == 0)
//		res = chdir(ft_getenv("OLDPWD", g_my_env));
//	else
//		res = chdir(parse[1]);
//	if (res == -1)
//	{
//		if (access(parse[1], F_OK) == 0)
//			perror_cmnd("cd", parse[1], PMDND);
//		else
//			perror_cmnd(SHELLNAME, parse[1], NOFLODIR);
//	}
//	if (res == 0)
//		update_pwd(getcwd(buf, 2048), tmp);
//}

//int		ft_cd(char **parse)
//{
//	int		i;
//	char	*home;
//	char	tmp[2048];
//
//	(home = ft_getenv("HOME", g_my_env));
////	{
////		perror_cmnd(SHELLNAME, NULL, GETENVERR);
////		return (1);
////	}
//
//	i = 0;
//	while (parse[i])
//		i++;
//	if (i > 2)
//	{
//		perror_cmnd("cd", NULL, MANYARGS);
//		return (1);
//	}
//	if (--i == 0)
//	{
//		if (home != NULL)
//		{
//			getcwd(tmp, 2048);
//			if (chdir(home) == 0)
//				update_pwd(home, tmp);
//		}
//	}
//	if (i == 1)
//		ft_cd_stuf(parse);
//	return (1);
//}


void	free_token_list(t_token **list)
{
	t_token *cur;
	t_token *temp;

	cur = *list;
	while (cur != NULL)
	{
		free(cur->buf);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
	*list = NULL;
}

void	free_hash_list(t_hash_node **list)
{
	t_hash_node *cur;
	t_hash_node *temp;

	cur = *list;
	while (cur != NULL)
	{
		free(cur->name);
		free(cur->path);
		temp = cur->next;
		free(cur);
		cur = temp;
	}
}

void	free_copy_envp(char ***envp)
{
	int		p;
	char	**ref;

	ref = *envp;
	p = count_pointers(ref);
	free_parse(ref, p);
	envp = NULL;
}

void	free_tree(t_tree *tree)
{
	t_tree *right;
	t_tree *left;

	if (tree == NULL)
		return ;
	if (tree->type == TYPE_SUFFIX)
	{
		if (tree->argv != NULL)
			free_parse(tree->argv, tree->args);
	}
	if (tree->type == TYPE_WORD || tree->type == 5)
	{
		if (tree->current)
			free_token_list(&(tree->current));
	}
	right = tree->right;
	left = tree->left;
	free(tree);
	free_tree(left);
	free_tree(right);
}

void	free_hash_table(t_hash **table)
{
	int		i;
	t_hash	*cur_hash;

	i = 0;
	cur_hash = *table;
	while (i < cur_hash->quant)
	{
		free_hash_list(&(cur_hash->node[i]));
		i++;
	}
	free(cur_hash->node);
	free(cur_hash);
	*table = NULL;
}


int		count_command(char *path)
{
	DIR				*dir;
	struct dirent	*d;
	int				res;

	res = 0;
	dir = opendir(path);
	if (dir != NULL)
	{
		while ((d = readdir(dir)) != NULL)
		{
			if (ft_strcmp(d->d_name, ".")
			!= 0 && ft_strcmp(d->d_name, "..") != 0)
				res++;
		}
		closedir(dir);
	}
	return (res);
}

int		counter(void)
{
	char	*env;
	int		words;
	char	**split;
	int		count;
	int		i;

	i = 0;
	count = 0;
	env = ft_getenv("PATH");
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

void	get_bin_fresh(t_hash_node **node, int hash_i, char *name, char *path)
{
	node[hash_i] = (t_hash_node *)malloc(sizeof(t_hash_node) * 1);
	node[hash_i]->name = ft_strdup(name);
	node[hash_i]->path = ft_strdup(path);
	node[hash_i]->next = NULL;
}

void	get_bin_used(t_hash_node **node, int hash_i, char *name, char *path)
{
	t_hash_node *cur;

	cur = node[hash_i];
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = (t_hash_node *)malloc(sizeof(t_hash_node) * 1);
	cur->next->name = ft_strdup(name);
	cur->next->path = ft_strdup(path);
	cur->next->next = NULL;
}

void	get_bin_from_path(char *path, t_hash *new)
{
	DIR				*dir;
	struct dirent	*d;
	int				hash_i;
	t_hash_node		**node;

	dir = opendir(path);
	node = new->node;
	if (dir != NULL)
	{
		while ((d = readdir(dir)) != NULL)
		{
			if (d->d_name[0] != '.')
			{
				hash_i = hashing(d->d_name, new->quant);
				if (node[hash_i] == NULL)
					get_bin_fresh(node, hash_i, d->d_name, path);
				else
					get_bin_used(node, hash_i, d->d_name, path);
			}
		}
		closedir(dir);
	}
}

void	insert_in_table(t_hash *new)
{
	char	*env;
	char	**split;
	int		words;
	int		i;

	i = 0;
	env = ft_getenv("PATH");

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
	else
		perror_cmnd(SHELLNAME, NULL, GETENVERR);
}

t_hash	*create_table(void)
{
	t_hash	*new;
	int		count;
	int		i;

	i = 0;
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


//char	*ft_getenv(const char *name, char **envp)
char	*ft_getenv(char *name)
{
	int		i;
	char	*ret;
	int		len;

	i = 0;
	len = (int)ft_strlen(name) + 1;
	while (g_my_env[i])
	{
		ret = ft_strstr(g_my_env[i], name);
		if (ret != NULL)
		{
			if (test_getenv(name, g_my_env[i]) == 1)
				return (ret + len);
		}
		i++;
	}
	return (NULL);
}

int		count_pointers(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	copy_env_to(char **envp, char **copy)
{
	int i;
	int j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '\0')
		{
			copy[i][j] = envp[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
}

char	**create_env_copy(char **envp, int c)
{
	char	**copy;
	int		i;

	i = 0;
	copy = (char **)malloc(sizeof(char *) * (c + 1));
	while (i < c)
	{
		copy[i] = (char *)malloc(sizeof(char) * (ft_strlen(envp[i]) + 1));
		i++;
	}
	copy[i] = NULL;
	copy_env_to(envp, copy);
	return (copy);
}

void	free_parse(char **parse, int w)
{
	int i;

	i = 0;
	w++;
	while (i < w)
	{
		free(parse[i]);
		i++;
	}
	free(parse);
}

int		ft_echo(char **parse)
{
	int i;

	i = 1;
	while (parse[i])
	{
		if (ft_strcmp(parse[i], " ") == 0)
		{
			i++;
			continue;
		}
		ft_putstr(parse[i]);
		if (parse[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
}

int		ft_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putendl(envp[i]);
		i++;
	}
	return (1);
}


int		ft_exit(char **envp)
{
	free_copy_envp(&envp);
	free_hash_table(&g_table);
	exit(0);
	return (1);
}

int		check_builtin(t_tree *ast)
{
	if (ft_strcmp(ast->argv[0], "echo") == 0)
		return (1);
	if (ft_strcmp(ast->argv[0], "env") == 0)
		return (1);
	if (ft_strcmp(ast->argv[0], "exit") == 0)
		return (1);
	if (ft_strcmp(ast->argv[0], "setenv") == 0)
		return (1);
	if (ft_strcmp(ast->argv[0], "unsetenv") == 0)
		return (1);
	if (ft_strcmp(ast->argv[0], "cd") == 0)
		return (1);
	if (ft_strcmp(ast->argv[0], "history") == 0)
		return (1);
	return (0);
}

int		builtin_execution(t_tree *ast)
{
	int res;

	res = 0;
	if (ft_strcmp(ast->argv[0], "echo") == 0)
		res = ft_echo(ast->argv);
	if (ft_strcmp(ast->argv[0], "env") == 0)
		res = ft_env(g_my_env);
	if (ft_strcmp(ast->argv[0], "exit") == 0)
		res = ft_exit(g_my_env);
	if (ft_strcmp(ast->argv[0], "setenv") == 0)
		res = ft_setenv(ast->argv[1], ast->argv[2]);
	if (ft_strcmp(ast->argv[0], "unsetenv") == 0)
		res = ft_unsetenv(ast->argv[1]);
	if (ft_strcmp(ast->argv[0], "cd") == 0)
		res = cd_cmnd(ast->argv);
	if (ft_strcmp(ast->argv[0], "history") == 0)
		res = display_history(ast->argv);
	return (res);
}

int		execute_builtin(t_tree *ast)
{
	t_tree	*redirs;
	int		fd;
	int		res;
	int		save;

	fd = 1;
	redirs = get_redirs_node(ast);
	if (redirs)
		aggregation_order(redirs->current, 1);
	fd = get_redirections(ast, fd, 3, 0);
	save = dup(1);
	dup2(fd, 1);
	res = builtin_execution(ast);
	close(fd);
	dup2(save, 1);
	close(save);
	return (res);
}


void	args_counter(t_tree *ast, t_tree *tmp)
{
	if (ast == NULL)
		return ;
	if (ast->type == 4)
		tmp->args += 1;
	args_counter(ast->left, tmp);
	args_counter(ast->right, tmp);
}

void	argv_creation(t_tree *ast, t_tree *tmp)
{
	if (ast == NULL)
		return ;
	if (ast->type == 4)
	{
		tmp->argv[tmp->cur] = ft_strdup(ast->current->buf);
		tmp->cur += 1;
	}
	argv_creation(ast->left, tmp);
	argv_creation(ast->right, tmp);
}

void	create_argv(t_tree *ast)
{
	t_tree *tmp;

	tmp = ast;
	args_counter(ast, tmp);
	ast->argv = (char **)malloc(sizeof(char *) * (ast->args + 1));
	argv_creation(ast, tmp);
	ast->argv[ast->cur] = NULL;
}


int		check_path(char *path)
{
	struct stat s;

	if ((lstat(path, &s)) == -1)
	{
		perror_cmnd(SHELLNAME, path, CMNDNTFND);
		return (-1);
	}
	if (access(path, X_OK) == -1)
	{
		perror_cmnd(SHELLNAME, path, PMDND);
		return (-1);
	}
	if (ft_strcmp(path, "./") == 0 || ft_strcmp(path, "/") == 0)
		return (-1);
	return (0);
}

char	*create_path(char *name, char *path)
{
	char *new;
	char *res;

	if (ft_strcmp(path, "/") != 0)
		new = ft_strjoin(path, "/");
	else
		new = path;
	res = ft_strjoin(new, name);
	if (ft_strcmp(path, "/") != 0)
		free(new);
	return (res);
}

char	*get_cmd(char *cmd, int hash)
{
	t_hash_node *node;

	if (hash == 0)
		return (NULL);
	if (g_table->node[hash] == NULL)
		return (NULL);
	else
	{
		node = g_table->node[hash];
		while (node)
		{
			if (ft_strcmp(cmd, node->name) == 0)
				return (create_path(node->name, node->path));
			node = node->next;
		}
	}
	return (NULL);
}

int		argv_checker(char **argv)
{
	int		hash;
	char	*upd;

	hash = hashing(argv[0], g_table->quant);
	upd = get_cmd(argv[0], hash);
	if (upd == NULL)
	{
		if (check_path(argv[0]) == 0)
			return (1);
		return (0);
	}
	else
	{
		free(argv[0]);
		argv[0] = ft_strdup(upd);
		free(upd);
		if (check_path(argv[0]) == 0)
			return (1);
		return (0);
	}
}

void	execute_start_fork(t_tree *ast, int in, int out, t_tree *redirs)
{
	dup2(in, 0);//
	dup2(out, 1);//
	close(in);//
	if (redirs)
		aggregation_order(redirs->current, out);
	execve(ast->argv[0], ast->argv, g_my_env);
}

int		execute_start(t_tree *ast, int in, int out)
{
	pid_t	pid;
	t_tree	*redirs;

	redirs = get_redirs_node(ast);
	in = get_redirections(ast, in, 4, 0);
	out = get_redirections(ast, out, 3, 1);
	if (argv_checker(ast->argv) == 1)
	{
		pid = fork();
		if (pid == 0)
			execute_start_fork(ast, in, out, redirs);
		else if (pid < 0)
			perror_cmnd(SHELLNAME, NULL, FORKERR);
		else
			close(out);
		return (0);
	}
	close(in);//
	close(out);//
	return (1);
}

void	close_fds(int out, int temp)
{
	close(out);//
	close(temp);//
}

void	execute_right_cmd(t_tree *ast, int in, int out, int temp)
{
	t_tree	*redirs;
	pid_t	pid;

	redirs = get_redirs_node(ast);
	pid = fork();
	if (pid == 0)
	{
		dup2(temp, 0);
		close(in);
		if (check_for_redir(ast, 3) == 1)
			dup2(out, 1);
		else if (ast->parent && ast->parent->parent
		&& ast->parent->parent->type == 1)
			dup2(out, 1);
		if (redirs)
			aggregation_order(redirs->current, out);
		execve(ast->argv[0], ast->argv, g_my_env);
	}
	else if (pid < 0)
		perror_cmnd(SHELLNAME, NULL, FORKERR);
	else
	{
		if (ast->parent->parent == NULL || (ast->parent->parent
		&& ast->parent->parent->type != 1))
			waitpid(pid, NULL, 0);
		close_fds(out, temp);
	}
}

int		execute_right(t_tree *ast, int in, int out, int temp)
{
	temp = get_redirections(ast, temp, 4, 1);
	out = get_redirections(ast, out, 3, 1);
	create_argv(ast);
	if (argv_checker(ast->argv) == 1)
	{
		if (check_builtin(ast) == 0)
			execute_right_cmd(ast, in, out, temp);
		else
		{
			execute_builtin(ast);
			close(out);
		}
		return (0);
	}
	close(in);//
	close(out);//
	return (1);
}

void	simple_execution_fork(t_tree *ast, int in, int out)
{
	t_tree	*redirs;
	pid_t	pid;

	redirs = get_redirs_node(ast);
	if (argv_checker(ast->argv) == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(in, 0);
			dup2(out, 1);
			if (redirs)
				aggregation_order(redirs->current, out);
			execve(ast->argv[0], ast->argv, g_my_env);//
		}
		else if (pid < 0)
			perror_cmnd(SHELLNAME, NULL, FORKERR);
		else
			waitpid(pid, NULL, 0);

	}
}

void	simple_execution(t_tree *ast)
{
	int		in;
	int		out;

	in = 0;
	out = 1;
	out = get_redirections(ast, out, 3, 0);
	in = get_redirections(ast, in, 4, 0);
	create_argv(ast);
	if (check_builtin(ast) == 0)
		simple_execution_fork(ast, in, out);
	else
		execute_builtin(ast);
}

void	create_files(t_tree *ast)
{
	int fd;

	fd = get_redirections(ast, 0, 3, 0);
	if (fd != 0)
		close(fd);
}

int		execute_tree_type_one_builtin(t_tree *ast, int fd[2])
{
	int temp;
	int tmp_fd;

	temp = dup(1);
	dup2(fd[1], 1);
	execute_builtin(ast->left);
	dup2(temp, 1);
	close(temp);
	close(fd[1]);
	tmp_fd = fd[0];
	return (tmp_fd);
}

int		execute_tree_type_one_start(t_tree *ast, int fd[2])
{
	int tmp_fd;
	int res;

	tmp_fd = -1;
	res = 0;
	create_argv(ast->left);
	if (check_builtin(ast->left))
	{
		tmp_fd = execute_tree_type_one_builtin(ast, fd);
		pipe(fd);
	}
	else
	{
		res = execute_start(ast->left, fd[0], fd[1]);
		if (res == 0)
		{
			tmp_fd = fd[0];
			pipe(fd);
		}
	}
	return (tmp_fd);
}



int		execute_tree_type_one_tmp(t_tree *ast, int fd[2])
{
	int tmp_fd;

	tmp_fd = -1;
	if (check_for_redir(ast->right, 3) == 0)
		tmp_fd = fd[0];
	else
		tmp_fd = get_redirections(ast->right, fd[1], 3, 1);
	return (tmp_fd);
}

void	director_suka(int tmp_fd)
{
	if (tmp_fd != -1)
		close(tmp_fd);
}

void	execute_tree_type_one(t_tree *ast)
{
	int fd[2];
	int start;
	int tmp_fd;

	tmp_fd = -1;
	start = 0;
	while (ast->left->type == 1)
		ast = ast->left;
	while (ast != NULL && ast->type == 1)
	{
		pipe(fd);
		if (start == 0)
		{
			start = 1;
			tmp_fd = execute_tree_type_one_start(ast, fd);
		}
		if (tmp_fd != -1)
		{
			if (execute_right(ast->right, fd[0], fd[1], tmp_fd) == 1)
				break ;
			tmp_fd = execute_tree_type_one_tmp(ast, fd);
		}
		ast = ast->parent;
	}
	director_suka(tmp_fd);
}

void	execute_tree(t_tree *ast)
{
	signals(1);
	if (ast == NULL)
		return ;
	if (ast->type == 1)
	{
		create_files(ast);
		execute_tree_type_one(ast);
	}
	else if (ast->type == 2)
	{
		execute_tree(ast->left);
		execute_tree(ast->right);
	}
	else if (ast->type == 3)
		simple_execution(ast);
}


void	splitterok(t_token **list, t_token **right)
{
	t_token *temp;

	temp = *list;
	*right = NULL;
	if (temp == NULL)
	{
		return ;
	}
	if (temp->next)
	{
		*right = temp->next;
		temp->next = NULL;
	}
}

t_tree	*create_node(t_token *list, int type, t_tree *parent)
{
	t_tree *res;

	res = ft_memalloc(sizeof(t_tree));
//	res = (t_tree *)malloc(sizeof(t_tree) * 1);

//	res->left = NULL;
//	res->right = NULL;
//	res->in = 0;
//	res->out = 1;
//	res->t_pipes = 0;
//	res->t_semis = 0;
//	res->argv = NULL;
//	res->args = 0;
//	res->cur = 0;
//	res->exe = 0;
//	res->fd = 0;
	res->parent = parent;
	res->current = list;
	if (list == NULL)
		res->type = 0;
	else
		res->type = type;
	return (res);
}

void	split_list(t_token **list, t_token **right, t_tree *ast, int type)
{
	t_token *temp;

	temp = *list;
	if (temp == NULL)
		return ;
	while (temp->next)
	{
		if (temp->next && temp->next->type == type)
		{
			ast->t_pipes -= 1;
			if (ast->t_pipes == 0)
			{
				*right = temp->next->next;
				free(temp->next->buf);
				free(temp->next);
				temp->next = NULL;
				break ;
			}
		}
		temp = temp->next;
	}
}

void	split_semicolomn(t_token **left, t_token **right)
{
	t_token *list;

	list = *left;
	if (list == NULL)
		return ;
	while (list->next && list->next->type != TYPE_CMND)
		list = list->next;
	if (list->next && list->next->next)
	{
		*right = list->next->next;
		free(list->next->buf);
		free(list->next);
	}
	else
		*right = NULL;
	list->next = NULL;
}

int		count_token_types(t_token *list, int type)
{
	int i;

	i = 0;
	while (list)
	{
		if (list->type == type)
			i++;
		list = list->next;
	}
	return (i);
}

void	create_tree_type_two(t_tree *ast, t_token *left, t_token *right)
{
	if (ast->t_pipes == 0 && ast->t_semis == 0)
		ast->type = 3;
	else if (ast->t_semis == 0 && ast->t_pipes > 0)
		ast->type = 1;
	else
	{
		split_semicolomn(&left, &right);
		ast->left = create_node(left, 2, ast);
		ast->right = create_node(right, 2, ast);
		create_tree(ast->left);
		create_tree(ast->right);
	}
}

void	create_tree_type_one(t_tree *ast, t_token *left, t_token *right)
{
	if (ast->t_pipes == 0)
		ast->type = 3;
	else
	{
		split_list(&left, &right, ast, 1);
		ast->left = create_node(left, 1, ast);
		ast->right = create_node(right, 2, ast);
		create_tree(ast->left);
		create_tree(ast->right);
	}
}

void	create_tree(t_tree *ast)
{
	t_token *left;
	t_token *right;

	left = ast->current;
	right = NULL;
	if (ast == NULL)
		return ;
	ast->t_pipes = count_token_types(ast->current, 1);
	ast->t_semis = count_token_types(ast->current, 2);
	if (ast->type == 2)
		create_tree_type_two(ast, left, right);
	if (ast->type == 1)
		create_tree_type_one(ast, left, right);
	if (ast->type == 3)
	{
		if (ast->current->type >= 3 && ast->current->type <= 9)
			ast->type = 5;
		else
		{
			splitterok(&left, &right);
			ast->left = create_node(left, 4, ast);
			ast->right = create_node(right, 3, ast);
			create_tree(ast->right);
		}
	}
}


int		type(char *buf)
{
	if (ft_strcmp(buf, "|") == 0)
		return (1);
	if (ft_strcmp(buf, ";") == 0)
		return (2);
	if (ft_strcmp(buf, ">") == 0)
		return (3);
	if (ft_strcmp(buf, "<") == 0)
		return (4);
	if (ft_strcmp(buf, ">>") == 0)
		return (3);
	if (ft_strcmp(buf, "<<") == 0)
		return (6);
	if (ft_strcmp(buf, "<&") == 0)
		return (7);
	if (ft_strcmp(buf, ">&") == 0)
		return (8);
	return (0);
}

void	append(t_token **head, t_token *new)
{
	t_token *tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int		buf_word_len(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';'
	&& cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<'
	&& cmd[i] != '"' && cmd[i] != 39)
		i++;
	return (i);
}

char	*create_buf(char *cmd)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = buf_word_len(cmd);
	res = NULL;
	if (len > 0)
	{
		res = (char *)malloc(sizeof(char) * (len + 1));
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';'
		&& cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>'
		&& cmd[i] != '"' && cmd[i] != 39)
		{
			res[i] = cmd[i];
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}

t_token	*create_token_new(char *buf)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token) * 1);
	new->buf = buf;
	new->type = type(buf);
	new->next = NULL;
	return (new);
}

char	*create_token_buf(char *cmd, size_t i, size_t cmd_len)
{
	char *buf;

	buf = NULL;
	if (i < cmd_len && i + 1 < cmd_len && cmd[i] == '>' && cmd[i + 1] == '>')
		buf = ft_strdup(">>");
	else if (i < cmd_len && i + 1 < cmd_len
	&& cmd[i] == '<' && cmd[i + 1] == '<')
		buf = ft_strdup("<<");
	else if (i < cmd_len && i + 1 < cmd_len
	&& cmd[i] == '<' && cmd[i + 1] == '&')
		buf = ft_strdup("<&");
	else if (i < cmd_len && i + 1 < cmd_len
	&& cmd[i] == '>' && cmd[i + 1] == '&')
		buf = ft_strdup(">&");
	else if (cmd[i] && cmd[i] == ';')
		buf = ft_strdup(";");
	else if (cmd[i] && cmd[i] == '|')
		buf = ft_strdup("|");
	else if (cmd[i] && cmd[i] == '>')
		buf = ft_strdup(">");
	else if (cmd[i] && cmd[i] == '<')
		buf = ft_strdup("<");
	return (buf);
}

t_token	*create_token(char *cmd, size_t i, size_t cmd_len)
{
	t_token	*new;
	char	*buf;

	buf = NULL;
	new = NULL;
	buf = create_token_buf(cmd, i, cmd_len);
	if (buf != NULL)
		new = create_token_new(buf);
	return (new);
}

t_token	*create_new(char *cmd, size_t i, size_t cmd_len)
{
	t_token	*new;
	char	*buf;

	new = NULL;
	buf = create_buf(&cmd[i]);
	if (buf != NULL)
	{
		new = (t_token *)malloc(sizeof(t_token) * 1);
		new->buf = buf;
		new->next = NULL;
		new->type = type(buf);
	}
	else
		new = create_token(cmd, i, cmd_len);
	return (new);
}

size_t	lexer_count_i(char *cmd, int i)
{
	if (cmd[i + 1] && cmd[i] == '>' && cmd[i + 1] == '>')
		i += 2;
	else if (cmd[i + 1] && cmd[i] == '<' && cmd[i + 1] == '<')
		i += 2;
	else if (cmd[i + 1] && cmd[i] == '<' && cmd[i + 1] == '&')
		i += 2;
	else if (cmd[i + 1] && cmd[i] == '>' && cmd[i + 1] == '&')
		i += 2;
	else if (cmd[i] == ';' || cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
		i++;
	else
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';'
		&& cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<')
			i++;
	return (i);
}

t_token	*lexer(char *cmd)
{
	t_token	*head;
	t_token *new;
	size_t	i;
	size_t	len;

	len = ft_strlen(cmd);
	i = 0;
	head = NULL;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'
		|| cmd[i] == '"' || cmd[i] == 39))
			i++;
		if (cmd[i] == '\0')
			break ;
		new = create_new(cmd, i, len);
		append(&head, new);
		i = lexer_count_i(cmd, i);
	}
	return (head);
}


char	*sub_line_stuf(char *parse)
{
	char *res;

	if (ft_strlen(parse) == 1)
		res = ft_strdup("$");
	else
		res = ft_strdup(" ");
	return (res);
}

char	*sub_line_dollar(char *parse)
{
	char *res;
	char *seek;

	seek = ft_getenv(&parse[1]);
	if (seek == NULL)
	{
		res = sub_line_stuf(parse);
		free(parse);
	}
	else
	{
		res = ft_strdup(seek);
		free(parse);
	}
	return (res);
}

char	*sub_line(char *parse)
{
	char *seek;
	char *res;

	res = parse;
	if (parse[0] == '$')
		res = sub_line_dollar(parse);
	else if (parse[0] == '~')
	{
		seek = ft_getenv("HOME");//
		if (seek == NULL)
			res = NULL;
		else
		{
			res = ft_strjoin(seek, &parse[1]);
			free(parse);
		}
	}
	return (res);
}

int		semantics_semicolomn(t_token *list)
{
	if (list->type == 2)
	{
		if (list->next && list->next->type == 2)
		{
			perror_cmnd(SHELLNAME, NULL, PARSEERR_SEMICOLS);
			return (1);
		}
	}
	return (0);
}

int		semantics(t_token *list)
{
	int first;

	first = 1;
	if (list && list->next == NULL)
	{
		if (list->type == 2)
			return (1);
	}
	while (list)
	{
		if (list->type != 1)
			first = 0;
		if (semantics_semicolomn(list))
			return (1);
		if (list->type == 1)
		{
			if ((list->next && list->next->type == 1) || first == 1)
			{
				perror_cmnd(SHELLNAME, NULL, PARSEERR_PIPE);
				return (1);
			}
		}
		list = list->next;
	}
	return (0);
}

void	update_lexer(t_token **list)
{
	t_token *temp;
	t_token *head;

	head = *list;
	if (head->type == 2 && head->next && head->next->type != 2)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->buf);
		free(temp);
	}
	head = *list;
	while (head)
	{
		if (head->next && head->next->type == 8)
		{
			head->type = 9;
			if (head->next->next)
				head->next->next->type = 9;
		}
		head->buf = sub_line(head->buf);
		head = head->next;
	}
}

void	action(char *cmd)
{
	t_token	*list;
	t_tree	*ast;

	list = lexer(cmd);
	update_lexer(&list);
	if (semantics(list) == 1)
	{
		free_token_list(&list);
		return ;
	}
	ast = create_node(list, 2, NULL);
	create_tree(ast);
	execute_tree(ast);
	free_tree(ast);
}

void	print_usage(void)
{
	ft_putstr_fd("usage: ", STDOUT_FILENO);
	ft_putstr_fd(SHELLNAME, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

t_shell *create_g_shell()
{
	t_shell *res;

	if (!(res = (t_shell *)malloc(sizeof(t_shell))))
		return (NULL);
	ft_bzero(res, sizeof(t_shell));
	return (res);
}

int		main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc == 1)
	{
		g_shell = create_g_shell();
		g_my_env = create_env_copy(env, count_pointers(env));
		g_table = create_table();
		g_shell->history = init_history();
		cmnd_loop();
	}
	else
		print_usage();
	return (EXIT_SUCCESS);
}

