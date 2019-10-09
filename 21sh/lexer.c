/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeqqo <gbeqqo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:14:14 by gbeqqo            #+#    #+#             */
/*   Updated: 2019/10/09 16:30:58 by gbeqqo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
