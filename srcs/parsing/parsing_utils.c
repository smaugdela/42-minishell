/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:26:15 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/26 12:38:18 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	str_copy(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str2[i])
	{
		str1[i] = str2[i];
		++i;
	}
}

/*
Takes 2 strings and return only one newly malloc'dstring,
concatenation of the two arguments.
WARNING: Frees the first argument!
*/
char	*my_strcat(char *dest, char *str)
{
	size_t	len1;
	size_t	len2;
	char	*tmp;

	len1 = ft_strlen(dest);
	len2 = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (tmp == NULL)
		return (NULL);
	if (dest != NULL)
	{
		str_copy(tmp, dest);
		free(dest);
	}
	if (str != NULL)
		str_copy(tmp + len1, str);
	tmp[len1 + len2] = '\0';
	return (tmp);
}

size_t	ft_envarlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str && str[0] == '$')
	{
		if (ft_isdigit(str[1]))
			return (2);
		i = 1;
	}
	else
	{
		if (str && ft_isdigit(str[0]))
			return (1);
	}
	while (str && str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| ft_is_in_charset(str[i], "_?")))
	{
		if (str[i] == '?')
		{
			++i;
			break ;
		}
		++i;
	}
	return (i);
}

/*
Finds "envar" in "envp" and returns its value,
according to the environment format.
If no envar with such a name exists, returns an empty string "".
Even if empty, the string is malloc'd, so that double frees won't happen.
Treats special envar like $?.
Returns NULL in case an error occured.
*/
char	*find_envar(char *envar, t_data *env_data)
{
	t_list	*tmp;
	size_t	envar_len;
	size_t	env_var_len;

	tmp = env_data->env;
	envar_len = ft_strlen(envar);
	if (envar_len == 1 && envar[0] == '?')
		return (ft_itoa(g_status));
	while (tmp != NULL)
	{
		env_var_len = ft_strlen(tmp->var);
		if (envar_len == env_var_len
			&& ft_strncmp(tmp->var, envar, envar_len) == 0)
		{
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

void	lst_pop(t_token *elem, t_token **token_list)
{
	t_token	*tmp;

	if (elem == NULL)
		return ;
	if (elem == *token_list)
		*token_list = (*token_list)->next;
	if (elem->type == WORD || elem->type == VAR)
		free(elem->data);
	if (elem->next != NULL)
		elem->next->previous = elem->previous;
	if (elem->previous != NULL)
		elem->previous->next = elem->next;
	if (elem->cmd != NULL)
		free_tab(elem->cmd);
	tmp = *token_list;
	free(elem);
	elem = NULL;
	while (tmp != NULL)
	{
		if (tmp->previous == NULL)
			tmp->index = 0;
		else
			tmp->index = tmp->previous->index + 1;
		tmp = tmp->next;
	}
}
