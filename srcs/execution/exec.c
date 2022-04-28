/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:22:31 by chduong           #+#    #+#             */
/*   Updated: 2022/04/22 22:40:51 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	for_child(t_token *elem, t_data *data, char **envp)
{
	close_unused_fd(elem, data);
	if (elem->in == -2)
		free_exit(data, 1);
	if (elem->in > -1)
	{
		if (dup2(elem->in, 0) == -1)
			return (perror("MiniShell: Error"));
		close(elem->in);
	}
	if (elem->out > -1)
	{
		if (dup2(elem->out, 1) == -1)
			return (perror("MiniShell: Error"));
		close(elem->out);
	}
	if (exec_builtins(elem, data) == true)
		free_exit(data, EXIT_SUCCESS);
	exec_cmd(elem->cmd, envp, data);
}

static void	fork_exec_aux(t_token *elem)
{
	if (elem->in > -1)
	{
		close(elem->in);
		elem->in = -1;
		if (elem->previous && elem->previous->type == PIPE)
			close(elem->previous->pipefd[0]);
	}
	if (elem->out > -1)
	{
		close(elem->out);
		elem->out = -1;
		if (elem->next && elem->next->type == PIPE)
			close(elem->next->pipefd[1]);
	}
}

pid_t	fork_exec(t_token *elem, char **envp, t_data *data)
{
	pid_t	pid;

	if (in_pipeline(elem) == false && is_builtin(elem->cmd[0]) == true)
	{
		standalone_builtin(elem, data);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("MiniShell: Error");
		return (-1);
	}
	else if (pid == 0)
	{
		set_signal(RESET);
		for_child(elem, data, envp);
	}
	fork_exec_aux(elem);
	return (pid);
}
