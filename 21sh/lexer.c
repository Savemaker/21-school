#include "21sh.h"

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


void	append(token **head, token *new)
{
	token *tmp;

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

int buf_word_len(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';' && cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<')
		i++;
	return (i);
}

char *create_buf(char *cmd)
{
	char *res;
	int len;
	int i;

	i = 0;
	len = buf_word_len(cmd);
	res = NULL;
	if (len > 0)
	{
		res = (char *)malloc(sizeof(char) * (len + 1));
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';' && cmd[i] != '|' && cmd[i] != '<' && cmd[i] != '>')
		{
			res[i] = cmd[i];
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}

token *create_token(char *cmd, int i, size_t cmd_len)
{
	token	*new;
	char	*buf;

	buf = NULL;
	new = NULL;
	if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '>' && cmd[i+1] == '>')
		buf = ft_strdup(">>");
	else if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '<' && cmd[i+1] == '<')
		buf = ft_strdup("<<");
	else if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '<' && cmd[i+1] == '&')
		buf = ft_strdup("<&");
	else if (i < cmd_len  && i + 1 < cmd_len  && cmd[i] == '>' && cmd[i+1] == '&')
		buf = ft_strdup(">&");
	else if (cmd[i] && cmd[i] == ';')
		buf = ft_strdup(";");
	else if (cmd[i] && cmd[i] == '|')
		buf = ft_strdup("|");
	else if (cmd[i] && cmd[i] == '>')
		buf = ft_strdup(">");
	else if (cmd[i] && cmd[i] == '<')
		buf = ft_strdup("<");
	if (buf != NULL)
	{
		new = (token *)malloc(sizeof(token) * 1);
		new->buf = buf;
		new->type = type(buf);
		new->next = NULL;
	}
	return (new);
}

token *create_new(char *cmd, int i, size_t cmd_len)
{
	token *new;
	char *buf;

	new = NULL;
	buf = create_buf(&cmd[i]);
	if (buf != NULL)
	{
		new = (token *)malloc(sizeof(token) * 1);
		new->buf = buf;
		new->next = NULL;
		new->type = type(buf);
	}
	else
		new = create_token(cmd, i, cmd_len);
	return (new);
}

token *lexer(char *cmd)
{
	token *head;
	token *new;
	int i;
	size_t len;

	len = ft_strlen(cmd);
	i = 0;
	head = NULL;
	while (cmd[i])
	{
		while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t' || cmd[i] == '"' || cmd[i] == 39))
			i++;
		if (cmd[i] == '\0')
			break ;
		new = create_new(cmd, i, len);
		append(&head, new);
		if (cmd[i + 1] && cmd[i] == '>' && cmd[i+1] == '>')
			i += 2;
		else if (cmd[i + 1] && cmd[i] == '<' && cmd[i+1] == '<')
			i += 2;
		else if (cmd[i + 1] && cmd[i] == '<' && cmd[i+1] == '&')
			i += 2;
		else if (cmd[i + 1] && cmd[i] == '>' && cmd[i+1] == '&')
			i += 2;
		else if (cmd[i] == ';' || cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
			i++;
		else
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != ';' && cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<')
				i++;
	}
	return (head);
}
