/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:47:38 by chduong           #+#    #+#             */
/*   Updated: 2022/04/22 16:34:17 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **cmd, t_list *env)
{
	if (cmd && cmd[1])
	{
		ft_putstr_fd("env: no arguments taken\n", 2);
		g_status = 127;
		return ;
	}
	while (env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
	g_status = 0;
}
