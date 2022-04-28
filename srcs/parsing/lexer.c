/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:48:39 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/24 20:49:37 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Trims spaces from "str_in", frees it, and returns a newly malloc'd string.
*/
char	*cleaner(char *str_in)
{
	char	*str_out;

	if (!str_in)
		return (NULL);
	str_out = ft_strtrim(str_in, " \t\n\r\v\f");
	free(str_in);
	str_in = NULL;
	return (str_out);
}

static void	add_token(t_token **list, t_token *token)
{
	t_token	*tmp;

	if (*list == NULL)
	{
		*list = token;
		token->previous = NULL;
		token->index = 0;
	}
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
		token->previous = tmp;
		token->index = tmp->index + 1;
	}
}

/*
Create and add a new token to the list.
*/
bool	create_token(t_token_type type, char *data, t_token **list)
{
	t_token	*token;

	if (data == NULL || type == NONE)
		return (false);
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("MiniShell: malloc failed");
		return (false);
	}
	token->type = type;
	token->data = data;
	token->next = NULL;
	token->cmd = NULL;
	token->to_delete = true;
	token->in = -1;
	token->out = -1;
	token->heredoc_expand = true;
	token->pid = -1;
	add_token(list, token);
	return (true);
}

/*
Will return position of the next char from charset.
Returns 0 otherwise.
*/
size_t	find_char_set(const char *str, char *charset)
{
	size_t	i;
	size_t	j;

	if (!str || !charset)
		return (0);
	i = 1;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
				return (i);
			j++;
		}
		++i;
	}
	return (0);
}

/*
Converts "input" string to token list exploitable by the analyzer.
Frees the "input" string (through cleaner function).
*/
t_token	*lexer(char *input)
{
	char	*str;
	t_token	*token_list;

	if (!input)
		return (NULL);
	str = cleaner(input);
	if (str == NULL)
	{
		ft_putstr_fd("Error: Corrupted Input\n", 2);
		return (NULL);
	}
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	token_list = scanner(str);
	free(str);
	if (token_list == NULL)
	{
		ft_putstr_fd("Error: Tokenizer Failed\n", 2);
		return (NULL);
	}
	return (token_list);
}
