/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_reduce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:19:43 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/08 15:50:09 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Replace current VAR token with the expanded WORD version of it,
if the VAR is found in the environement.
*/
void	expand(t_token *elem, t_data *env_data)
{
	char	*to_free;

	if (elem->type != VAR)
		return ;
	elem->type = WORD;
	if (heredoc_expand_exception(elem) == true)
		return ;
	to_free = elem->data;
	elem->data = find_envar(elem->data + 1, env_data);
	free(to_free);
	to_free = NULL;
	if (elem->data == NULL)
	{
		perror("MiniShell: malloc failed");
		elem->data = ft_strdup("");
		return ;
	}
}

/*
Used to replace the previous sample of toklist with one token only,
and frees accordingly (links "elem" to "tmp").

			  Redirect...
	/-->-->-->-->-->-->-->-->-->-->-->-->\
   |									  |
elem-> | elem+1->elem+2->...->tmp-1-> | tmp->tmp+1->...

		  ^...then frees this part.^

Refreshes to the new indexes too.
*/
void	relink_toklist(t_token *elem, t_token *tmp, char *new_data,
		t_token **token_list)
{
	t_token	*to_free;

	if (elem->next == tmp)
		return ;
	if ((elem->type == WORD || elem->type == VAR) && elem->data != NULL)
		free(elem->data);
	elem->data = new_data;
	elem->type = WORD;
	elem->to_delete = false;
	to_free = elem->next;
	while (to_free != NULL && to_free != tmp)
	{
		lst_pop(to_free, token_list);
		to_free = elem->next;
	}
	while (to_free != NULL)
	{
		if (to_free->previous == NULL)
			to_free->index = 0;
		else
			to_free->index = to_free->previous->index + 1;
		to_free = to_free->next;
	}
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (including environment variables) will become one and
only one token of type WORD, WITHOUT the quotes on each sides.
To use with single quotes.
*/
void	reduce_all(t_token **elem, t_token *end,
		t_token **token_list)
{
	t_token	*tmp;
	char	*new_data;

	tmp = *elem;
	if (tmp == NULL)
		return ;
	tmp = tmp->next;
	new_data = ft_strdup("");
	while (tmp != NULL && tmp->index < end->index)
	{
		new_data = my_strcat(new_data, tmp->data);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	relink_toklist(*elem, tmp->next, new_data, token_list);
	glue_together(elem, token_list);
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (BUT NOT environement variables) will become one and
only one token of type WORD, AFTER EXPANDING ENVIRONMENT VARIABLES,
WITHOUT the quotes on each sides.
To use with double quotes.
*/
void	reduce(t_token **elem, t_token *end, t_data *env_data,
		t_token **token_list)
{
	t_token	*tmp;
	char	*new_data;

	tmp = *elem;
	if (tmp == NULL)
		return ;
	tmp = tmp->next;
	new_data = ft_strdup("");
	while (tmp != NULL && tmp->index < end->index)
	{
		if (tmp->type == VAR)
		{
			if (ft_strlen(tmp->data) == 1)
				tmp->type = WORD;
			else
				expand(tmp, env_data);
		}
		new_data = my_strcat(new_data, tmp->data);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	relink_toklist(*elem, tmp->next, new_data, token_list);
	glue_together(elem, token_list);
}

/*
Reduce everything between "elem" and the elem with index "end" from toklist.
Meaning everything (including environment variables) will become one and
only one token of type WORD, merging every data attributes from them in one
array of strings "cmd", including data from "elem" and "end"th token.
To use with checker_words.
*/
bool	reduce_words(t_token *elem, size_t end, t_token **token_list)
{
	t_token	*tmp;
	char	**cmd;
	size_t	i;

	if (elem == NULL || elem->index > end)
		return (false);
	cmd = (char **)malloc(sizeof(char *) * (end - elem->index + 2));
	if (cmd == NULL)
	{
		perror("MiniShell: malloc failed");
		return (false);
	}
	tmp = elem;
	i = 0;
	while (tmp != NULL && tmp->index <= end)
	{
		cmd[i] = ft_strdup(tmp->data);
		tmp = tmp->next;
		++i;
	}
	cmd[i] = NULL;
	relink_toklist(elem, tmp, NULL, token_list);
	elem->cmd = cmd;
	return (true);
}
