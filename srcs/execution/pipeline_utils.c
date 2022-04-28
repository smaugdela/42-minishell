/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:00:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/24 20:31:02 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_tablen(char **tab)
{
	size_t	i;

	i = 0;
	while (tab && tab[i])
		++i;
	return (i);
}

static char	**ft_tabcat(char **tab1, char **tab2)
{
	char	**new_tab;
	size_t	new_tab_len;
	int		i;
	int		j;

	new_tab_len = ft_tablen(tab1) + ft_tablen(tab2);
	new_tab = malloc(sizeof(char *) * (new_tab_len + 1));
	if (new_tab == NULL)
	{
		perror("MiniShell: malloc failed");
		return (NULL);
	}
	i = -1;
	while (tab1 && tab1[++i])
		new_tab[i] = ft_strdup(tab1[i]);
	j = -1;
	while (tab2 && tab2[++j])
		new_tab[j + i] = ft_strdup(tab2[j]);
	if ((j + i) < 0)
		j = -1 * i;
	new_tab[j + i] = NULL;
	free_tab(tab1);
	return (new_tab);
}

void	merge_cmd(t_token *elem, t_data *data)
{
	t_token	*tmp;
	t_token	*to_pop;

	if (elem == NULL)
		return ;
	tmp = elem->next;
	while (tmp && tmp->type == WORD)
	{
		elem->cmd = ft_tabcat(elem->cmd, tmp->cmd);
		to_pop = tmp;
		tmp = tmp->next;
		lst_pop(to_pop, &data->token_list);
	}
}

static void	pop_first_cmd_aux(t_token **elem, char **str, size_t i)
{
	char	**cmd_tmp;

	cmd_tmp = malloc(sizeof(char *) * i);
	if (cmd_tmp == NULL)
	{
		perror("MiniShell: malloc failed");
		free(*str);
		*str = NULL;
		return ;
	}
	i = 0;
	while ((*elem)->cmd && (*elem)->cmd[i])
	{
		if ((*elem)->cmd[i + 1] == NULL)
		{
			cmd_tmp[i] = NULL;
			break ;
		}
		cmd_tmp[i] = ft_strdup((*elem)->cmd[i + 1]);
		++i;
	}
	free_tab((*elem)->cmd);
	(*elem)->cmd = cmd_tmp;
}

/*
Removes the first string from the string array "cmd" in token elem.
Returns this string, or NULL if any error occurs.
*/
char	*pop_first_cmd(t_token **elem, t_data *data)
{
	char	*str;
	size_t	i;

	if (elem == NULL || *elem == NULL
		|| (*elem)->type != WORD || (*elem)->cmd == NULL)
		return (NULL);
	str = ft_strdup((*elem)->cmd[0]);
	i = ft_tablen((*elem)->cmd);
	if (i <= 1)
		lst_pop(*elem, &data->token_list);
	else
		pop_first_cmd_aux(elem, &str, i);
	return (str);
}
