/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:51:32 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/22 16:29:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **cmd)
{
	char	*pwd;

	if (cmd && cmd[1] && cmd[1][0] == '-')
	{
		ft_putstr_fd("Minishell: pwd: no options taken\n", 2);
		g_status = 2;
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		g_status = 1;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
		g_status = 0;
	}
}
