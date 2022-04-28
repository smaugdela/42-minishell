/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:53:09 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/21 12:38:57 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Finds the next "elem_type" element in toklist,
and returns its index in the list;
If there are none, returns 0;
*/
size_t	is_closed(t_token *elem, t_token_type elem_type)
{
	t_token	*tmp;

	if (elem == NULL)
		return (0);
	tmp = elem->next;
	while (tmp != NULL)
	{
		if (tmp->type == elem_type)
			return (tmp->index);
		tmp = tmp->next;
	}
	return (0);
}

/*
Trims every boundary space from each WORD token in the list,
starting from "elem".
*/
/*
static void	trim_wordspaces(t_token *elem)
{
	t_token	*tmp;
	char	*to_del;

	tmp = elem;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			to_del = tmp->data;
			tmp->data = ft_strtrim(tmp->data, " \t\n\r\v\f");
			free(to_del);
		}
		tmp = tmp->next;
	}
}
*/

static bool	squote_manager(t_token **tmp, t_data *env_data)
{
	t_token	*ends_elem;
	size_t	ends;

	ends = is_closed(*tmp, SQUOTE);
	if (ends != 0)
	{
		ends_elem = *tmp;
		while (ends_elem != NULL && ends_elem->index < ends)
			ends_elem = ends_elem->next;
		if (ends_elem != (*tmp)->next)
			reduce_all(tmp, ends_elem, &env_data->token_list);
		else
		{
			relink_toklist(*tmp, (*tmp)->next->next, ft_strdup(""),
				&env_data->token_list);
			glue_together(tmp, &env_data->token_list);
		}
		if ((*tmp)->previous && (*tmp)->previous->type == VAR
			&& ft_strcmp((*tmp)->previous->data, "$") == 0)
			expand((*tmp)->previous, env_data);
		if (heredoc_expand_exception(*tmp) == true)
			(*tmp)->heredoc_expand = false;
		return (true);
	}
	return (false);
}

static bool	dquote_manager(t_token **tmp, t_data *env_data)
{
	t_token	*endd_elem;
	size_t	endd;

	endd = is_closed((*tmp), DQUOTE);
	if (endd != 0)
	{
		endd_elem = (*tmp);
		while (endd_elem != NULL && endd_elem->index < endd)
			endd_elem = endd_elem->next;
		if (endd_elem != (*tmp)->next)
			reduce(tmp, endd_elem, env_data, &env_data->token_list);
		else
		{
			relink_toklist(*tmp, (*tmp)->next->next, ft_strdup(""),
				&env_data->token_list);
			glue_together(tmp, &env_data->token_list);
		}
		if ((*tmp)->previous && (*tmp)->previous->type == VAR
			&& ft_strcmp((*tmp)->previous->data, "$") == 0)
			expand((*tmp)->previous, env_data);
		if (heredoc_expand_exception((*tmp)) == true)
			(*tmp)->heredoc_expand = false;
		return (true);
	}
	return (false);
}

/*
Check if quotes are closed, and reduce everything in between accordingly.
In the ends, calls "suppress_spaces" function in order to delete
any spaces which were not inside quotes, therefore unecessary.
*/
bool	checker_quotes(t_token *token_list, t_data *env_data)
{
	t_token	*tmp;
	bool	ret;

	tmp = token_list;
	ret = true;
	while (tmp != NULL && ret == true)
	{
		if (tmp->type == SQUOTE)
			ret = squote_manager(&tmp, env_data);
		else if (tmp->type == DQUOTE)
			ret = dquote_manager(&tmp, env_data);
		tmp = tmp->next;
	}
	return (ret);
}
