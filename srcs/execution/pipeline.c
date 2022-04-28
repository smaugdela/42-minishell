/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:47:56 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/24 20:42:59 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_handler(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (pipe(tmp->pipefd) == -1)
				perror("MiniShell: Pipe failed");
			else
			{
				if (tmp->previous->out > -1)
					close(tmp->previous->out);
				tmp->previous->out = tmp->pipefd[1];
				if (tmp->next->in > -1)
					close(tmp->next->in);
				tmp->next->in = tmp->pipefd[0];
			}
		}
		tmp = tmp->next;
	}
}

void	file_handler(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		if (is_redir_token(tmp) == true && tmp->next != NULL)
		{
			tmp->heredoc_expand = tmp->next->heredoc_expand;
			tmp->cmd = malloc(sizeof(char *) * 2);
			if (tmp->cmd == NULL)
				return (perror("MiniShell: malloc failed"));
			tmp->cmd[0] = pop_first_cmd(&(tmp->next), data);
			tmp->cmd[1] = NULL;
		}
		if (tmp->type == LESS && tmp->cmd != NULL)
			less_handler(get_filepath(&tmp->cmd[0]), &tmp, data);
		else if (tmp->type == GREAT && tmp->cmd != NULL)
			great_handler(get_filepath(&tmp->cmd[0]), &tmp, data);
		else if (tmp->type == DLESS && tmp->cmd != NULL)
			heredoc(tmp->cmd[0], &tmp, data);
		else if (tmp->type == DGREAT && tmp->cmd != NULL)
			dgreat_handler(get_filepath(&tmp->cmd[0]), &tmp, data);
		else
			tmp = tmp->next;
	}
}

static int	launch_cmd(char **envp, t_data *data, int nb_process)
{
	t_token	*tmp;
	int		i;
	pid_t	exit_process;

	tmp = data->token_list;
	exit_process = 0;
	i = 0;
	while (tmp && exit_process != -1 && i < nb_process)
	{
		if (tmp->type == WORD && tmp->cmd != NULL)
		{
			tmp->pid = fork_exec(tmp, envp, data);
			exit_process = tmp->pid;
			++i;
		}
		tmp = tmp->next;
	}
	return (exit_process);
}

static void	wait_cmd(int nb_process, pid_t exit_process)
{
	int		wstatus;
	pid_t	pid;

	wstatus = 0;
	while (nb_process)
	{
		pid = wait(&wstatus);
		if (pid == exit_process)
		{
			if (WIFEXITED(wstatus))
				g_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
			{
				g_status = 128 + WTERMSIG(wstatus);
				check_exit_status();
			}
			else if (WIFSTOPPED(wstatus))
				g_status = 128 + WSTOPSIG(wstatus);
		}
		--nb_process;
	}
}

/*
Launch the execution of the whole token_list, and frees it.
Reproduce the behavior of multiple pipes, adding file redirectors too.
*/
void	executor(char **envp, t_data *data)
{
	int		nb_process;
	int		exit_process;

	if (data->token_list == NULL)
		return ;
	set_signal(MUTE);
	pipe_handler(data);
	file_handler(data);
	nb_process = count_cmd(data);
	exit_process = launch_cmd(envp, data, nb_process);
	if (exit_process != -1)
		wait_cmd(nb_process, exit_process);
	if (data->token_list)
		free_toklist(&data->token_list);
	set_signal(DEFAULT);
}
