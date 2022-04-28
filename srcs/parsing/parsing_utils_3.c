/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:40:03 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/22 13:01:17 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tabhere(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("[%s] ", tab[i]);
		++i;
	}
	printf("\n");
}

static void	type_display(t_token *tmp)
{
	if (tmp->type == WORD && tmp->cmd != NULL)
	{
		printf("%zu WORD (cmd) : ", tmp->index);
		print_tabhere(tmp->cmd);
	}
	else if (tmp->type == WORD && tmp->data != NULL)
		printf("%zu WORD (data) : [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == PIPE)
		printf("%zu PIPE: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == LESS)
		printf("%zu LESS: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == GREAT)
		printf("%zu GREAT: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DLESS)
		printf("%zu DLESS: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DGREAT)
		printf("%zu DGREAT: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == VAR)
		printf("%zu VAR: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == DQUOTE)
		printf("%zu DQUOTE: [%s]\n", tmp->index, tmp->data);
	else if (tmp->type == SQUOTE)
		printf("%zu SQUOTE: [%s]\n", tmp->index, tmp->data);
}

/*
Temporary function used to display the tokenlist ,
in order to check tokenizer's good behavior.
Erase it before defense, as it contains forbidden functions.
*/
void	display_toklist(t_token *token_list)
{
	t_token	*tmp;

	tmp = token_list;
	while (tmp != NULL)
	{
		type_display(tmp);
		tmp = tmp->next;
	}
}

/*
Deletes every WORD token which are only spaces.
*/
void	suppress_spaces(t_token **token_list)
{
	t_token	*tmp;
	t_token	*to_pop;

	tmp = *token_list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD
			&& !ft_strncmp(tmp->data, " ", ft_strlen(tmp->data))
			&& tmp->to_delete == true)
		{
			to_pop = tmp;
			tmp = tmp->next;
			lst_pop(to_pop, token_list);
		}
		else
			tmp = tmp->next;
	}
}

void	reparse_envar(t_token **elem, t_data *data)
{
	t_token	*end;

	end = envar_split(elem);
	if ((*elem)->previous == NULL)
		data->token_list = *elem;
	if (end != NULL && end != *elem)
	{
		glue_to_prev(elem, &data->token_list);
		glue_to_next(&end, &data->token_list);
	}
	else if (end != NULL && end == *elem)
		glue_together(elem, &data->token_list);
}
