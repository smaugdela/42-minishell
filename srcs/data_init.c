/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:37:56 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/20 14:19:19 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shlvl_up(t_data *data, char *lvl)
{
	char	*newlvl;
	char	*shlvl;

	newlvl = ft_itoa(ft_atoi(lvl) + 1);
	shlvl = malloc(sizeof(char) * (ft_strlen(newlvl) + 7));
	ft_strlcpy(shlvl, "SHLVL=", 7);
	ft_strlcat(shlvl, newlvl, ft_strlen(newlvl) + 7);
	ft_lstadd_back(&data->env, ft_lstnew(shlvl, "SHLVL", newlvl));
	free(newlvl);
	free(shlvl);
}

static void	init_env(t_data *data, char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (ft_strncmp(tmp[0], "SHLVL", 6) == 0)
			shlvl_up(data, tmp[1]);
		else
			ft_lstadd_back(&data->env, ft_lstnew(envp[i], tmp[0], tmp[1]));
		free_tab(tmp);
		++i;
	}
}

static void	create_env(t_data *data)
{
	char	*tmp;
	char	*cwd;
	int		len;

	cwd = getcwd(NULL, 0);
	len = ft_strlen(cwd);
	tmp = malloc(sizeof(char) * (len + 5));
	ft_strlcpy(tmp, "PWD=", 5);
	ft_strlcat(tmp, cwd, len + 5);
	ft_lstadd_back(&data->env, ft_lstnew(tmp, "PWD", cwd));
	free(tmp);
	free(cwd);
	ft_lstadd_back(&data->env, ft_lstnew("SHLVL=1", "SHLVL", "1"));
	ft_lstadd_back(&data->env,
		ft_lstnew("_=/usr/bin/env", "_", "/usr/bin/env"));
}

void	data_init(t_data *data, char **envp)
{
	data->line = NULL;
	data->env = NULL;
	data->path = ft_split(getenv("PATH"), ':');
	data->newpath = 0;
	g_status = 0;
	data->token_list = NULL;
	if (envp && *envp)
		init_env(data, envp);
	else
		create_env(data);
	data->export = cpy_env(data->env);
	sort_export(data->export);
}
