/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:11:03 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/26 16:30:24 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_new_var(char *var, t_data *data)
{
	t_list	*env;

	env = grep(var, data);
	if (!env)
		return (true);
	else
		return (false);
}

static void	change_var(char *envl, char **arg, t_data *data)
{
	t_list	*env;

	env = grep(arg[0], data);
	free(env->line);
	env->line = ft_strdup(envl);
	free(env->value);
	if (arg[1])
		env->value = ft_strdup(arg[1]);
	else
		env->value = NULL;
}

static void	print_export(t_data *data)
{
	int		i;
	t_list	*env;
	char	**tmp;

	i = 0;
	env = data->env;
	while (data->export[i])
	{
		tmp = ft_split(data->export[i++], '=');
		env = grep(tmp[0], data);
		printf("declare -x %s=\"%s\"\n", env->var, env->value);
		free_tab(tmp);
	}
}

static void	export_var(char *arg, t_data *data)
{
	char	**tmp;

	if (valid_var(arg))
	{
		tmp = ft_split(arg, '=');
		if (ft_strncmp(tmp[0], "PATH", 5) == 0)
			data->newpath = true;
		if (is_new_var(tmp[0], data))
			ft_lstadd_back(&data->env, ft_lstnew(arg, tmp[0], tmp[1]));
		else
			change_var(arg, tmp, data);
		free_tab(tmp);
	}
}

void	export(char **arg, t_data *data)
{
	int		i;

	i = 1;
	if (arg[i])
	{
		while (arg[i])
			export_var(arg[i++], data);
		update_env(data);
	}
	else
		print_export(data);
}
