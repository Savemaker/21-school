#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct tree{
	struct tree *left;
	struct tree *right;
	char *buf;
}tree;

typedef struct tokens{
	char *buf;
	int type;
	struct tokens *next;
}tkn;

tkn *create_new_tkn(char *buf)
{
	tkn *res;

	res = (tkn *)malloc(sizeof(tkn) * 1);
	res->buf = strdup(buf);
}

tkn *create_tokens(char **parse)
{
	int i;
	tkn *new;
	tkn *head;

	head = NULL;
	i = 0;
	while (parse[i])
	{
		new = 
	}
}

int main()
{
    char *line;
    char **parse;
    int res;
	tree *res;
	tkn *tokens;

    line = "1 + 1";
	int w = count_words(line);
    parse = ft_full_split(line, w);
	tokens = 

}