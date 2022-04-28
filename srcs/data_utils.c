/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:31:59 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/04 18:39:56 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cpy_env(t_list *env)
{
	char	**sort;
	int		i;

	sort = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	i = 0;
	while (env)
	{
		sort[i] = env->line;
		env = env->next;
		++i;
	}
	sort[i] = 0;
	return (sort);
}

void	sort_export(char **sort)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (sort[i])
	{
		j = i + 1;
		while (sort[j])
		{
			if (ft_strcmp(sort[i], sort[j]) > 0)
			{
				tmp = sort[i];
				sort[i] = sort[j];
				sort[j] = tmp;
			}
			++j;
		}
		++i;
	}
}

void	update_env(t_data *data)
{
	t_list	*path;

	free(data->export);
	data->export = cpy_env(data->env);
	sort_export(data->export);
	if (data->newpath == true)
	{
		path = grep("PATH", data);
		free_tab(data->path);
		data->path = ft_split(path->value, ':');
		data->newpath = false;
	}
}
