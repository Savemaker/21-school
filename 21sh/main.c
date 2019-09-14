/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 20:45:46 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/09/14 16:30:32 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

typedef struct my_pipe{
	char *cmd;
	int fd_in;
	int fd_out;
	struct my_pipe *next;
}my_pipe;

int		*create_tab(int words)
{
	int *res;
	int i;

	i = 0;
	words++;
	res = (int *)malloc(sizeof(int) * words);
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
	k = 0;
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
	int len;
	int *tab;
	int j;

	i = 0;
	j = 0;
	len = 0;
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

char	**ft_split_delim(char *cmd, int words, char delim)
{
	char	**res;
	int		*tab;
	int		i;

	i = 0;
	tab = count_each_word_delim(cmd, words, delim);
	res = (char **)malloc(sizeof(char *) * (words + 1));
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

int		count_words(char *cmd)
{
	int i;
	int w;

	i = 0;
	w = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '"' || cmd[i] == 39)
			i++;
		if (cmd[i] != '\0')
			w++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i]
		!= ' ' && cmd[i] != '"' && cmd[i] != 39)
			i++;
	}
	return (w);
}

int		*count_each_word(char *cmd, int words)
{
	int i;
	int len;
	int *tab;
	int j;

	i = 0;
	j = 0;
	len = 0;
	tab = create_tab(words);
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '"' || cmd[i] == 39)
			i++;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i]
		!= ' ' && cmd[i] != '"' && cmd[i] != 39)
		{
			tab[j]++;
			i++;
		}
		j++;
	}
	return (tab);
}

void	copy_split(char **res, char *cmd)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] == '\t' || cmd[i] == ' ' || cmd[i] == '"' || cmd[i] == 39)
			i++;
		k = 0;
		if (cmd[i] == '\0')
			break ;
		while (cmd[i] != '\0' && cmd[i] != '\t' && cmd[i]
		!= ' ' && cmd[i] != '"' && cmd[i] != 39)
			res[j][k++] = cmd[i++];
		res[j][k] = '\0';
		j++;
	}
}

char	**ft_full_split(char *cmd, int words)
{
	char	**res;
	int		*tab;
	int		i;

	i = 0;
	tab = count_each_word(cmd, words);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	while (i < words)
	{
		res[i] = (char *)malloc(sizeof(char) * tab[i] + 1);
		i++;
	}
	free(tab);
	res[i] = NULL;
	copy_split(res, cmd);
	return (res);
}


//  command: ls | cat - e | grep '21'

my_pipe *create_new_pipe(char *line)
{
	my_pipe *res;

	res = (my_pipe *)malloc(sizeof(my_pipe) * 1);
	res->cmd = ft_strdup(line);
	res->fd_in = 0;
	res ->fd_out = 1;
	res->next = NULL;
	return (res);
}

void	append(my_pipe **head, my_pipe *new)
{
	my_pipe *tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp ->next;
		tmp->next = new;
	}
}

my_pipe *creation(char **pipes)
{
	my_pipe *new;
	my_pipe *head;
	int		i;

	i = 0;
	head = NULL;
	while (pipes[i])
	{
		new = create_new_pipe(pipes[i]);
		append(&head, new);
		i++;
	}
	return (head);
}

void	create_struct(char *cmd)
{
	char	**pipes;
	int		words;
	int		d_words;
	my_pipe	*new;

	words = count_words(cmd);
	d_words = count_words_delim(cmd, '|');
	pipes = ft_split_delim(cmd, d_words, '|');
	new = creation(pipes);
	
}

int main()
{
	char *cmd;

	while (1)
	{
		cmd = readline("-> ");
		create_struct(cmd);
	}
}