/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:15 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/26 15:42:25 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_data *data)
{
	t_list	*old;
	t_list	*pwd;
	char	*tmp;

	pwd = grep("PWD", data);
	old = grep("OLDPWD", data);
	if (old)
	{
		free(old->value);
		free(old->line);
		old->value = ft_strdup(pwd->value);
		old->line = var_join("OLDPWD", pwd->value);
	}
	else
	{
		tmp = var_join("OLDPWD", pwd->value);
		ft_lstadd_back(&data->env, ft_lstnew(tmp, "OLDPWD", pwd->value));
		free(tmp);
	}
}

void	update_pwd(char *path, t_data *data)
{
	char	*newpwd;
	t_list	*pwd_env;

	if (g_status == 0)
	{
		newpwd = getcwd(NULL, 0);
		pwd_env = grep("PWD", data);
		free(pwd_env->line);
		pwd_env->line = var_join("PWD", newpwd);
		free(pwd_env->value);
		pwd_env->value = ft_strdup(newpwd);
		free(newpwd);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	go_home(t_data *data)
{
	t_list	*env;

	env = grep("HOME", data);
	if (env)
	{
		g_status = chdir(env->value) * -1;
		update_pwd(env->value, data);
	}
	else
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", STDERR_FILENO);
		g_status = 1;
	}
}

void	cd(char **arg, t_data *data)
{
	char	*path;

	if (count_str(arg) > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		g_status = 1;
		return ;
	}
	path = arg[1];
	update_oldpwd(data);
	if (ft_strncmp(arg[0], "cd", 3) == 0 && !path)
		go_home(data);
	else
	{
		g_status = chdir(path) * -1;
		update_pwd(path, data);
	}
	update_env(data);
}
