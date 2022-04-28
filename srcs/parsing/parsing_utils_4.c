/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:10:45 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/24 21:03:53 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	glue_to_prev(t_token **tmp, t_token **token_list)
{
	if (is_legit((*tmp)->previous) == true && (*tmp)->previous
		&& (*tmp)->previous->type == WORD)
	{
		*tmp = (*tmp)->previous;
		(*tmp)->data = my_strcat((*tmp)->data, (*tmp)->next->data);
		lst_pop((*tmp)->next, token_list);
	}
}

void	glue_to_next(t_token **tmp, t_token **token_list)
{
	if (is_legit((*tmp)->next) == true && (*tmp)->next
		&& (*tmp)->next->type == WORD)
	{
		(*tmp)->data = my_strcat((*tmp)->data, (*tmp)->next->data);
		lst_pop((*tmp)->next, token_list);
	}
}

static t_token	*envar_split_aux(t_token **elem)
{
	t_token	*tmp_list;
	char	**tab;
	int		i;

	tmp_list = NULL;
	if ((*elem)->data[0] == ' ')
	{
		if (create_token(WORD, ft_strdup(""), &tmp_list) == false)
			return (NULL);
	}
	tab = ft_split((*elem)->data, ' ');
	i = 0;
	while (tab[i])
	{
		if (create_token(WORD, ft_strdup(tab[i++]), &tmp_list) == false)
		{
			free_tab(tab);
			return (NULL);
		}
	}
	free_tab(tab);
	return (tmp_list);
}

static t_token	*envar_split_aux2(t_token **elem, t_token *tmp_list,
								t_token *tmp)
{
	if (ft_strlen((*elem)->data) > 0
		&& (*elem)->data[ft_strlen((*elem)->data) - 1] == ' ')
	{
		if (create_token(WORD, ft_strdup(""), &tmp_list) == false)
			return (NULL);
	}
	if ((*elem)->previous)
		(*elem)->previous->next = tmp_list;
	tmp_list->previous = (*elem)->previous;
	tmp = tmp_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if ((*elem)->next)
		(*elem)->next->previous = tmp;
	tmp->next = (*elem)->next;
	(*elem)->next = NULL;
	(*elem)->previous = NULL;
	free_toklist(elem);
	*elem = tmp_list;
	return (tmp);
}

/*
Splits the result of the "elem" envar expansion into a new list of
WORD tokens, on each space.
It then relinks this new little list of tokens inside the
"token_list", where "elem" once was.
It does it only when there are no redirection before itself.
*/
t_token	*envar_split(t_token **elem)
{
	t_token	*tmp;
	t_token	*tmp_list;

	tmp = (*elem)->previous;
	while (tmp && is_legit(tmp) == false)
		tmp = tmp->previous;
	if (tmp && (is_redir_token(tmp) == true || (*elem)->data == NULL))
		return (*elem);
	else
	{
		tmp_list = envar_split_aux(elem);
		if (tmp_list == NULL)
			return (*elem);
		return (envar_split_aux2(elem, tmp_list, tmp));
	}
}
