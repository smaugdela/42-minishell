/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:52:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/24 20:40:46 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	end_handlers(char *filepath, t_token **tmp, t_data *data)
{
	if (filepath)
	{
		free(filepath);
		filepath = NULL;
	}
	if ((*tmp)->previous && (*tmp)->previous->type == PIPE)
		close((*tmp)->previous->pipefd[0]);
	if ((*tmp)->next && (*tmp)->next->type == PIPE)
		close((*tmp)->next->pipefd[1]);
	if ((*tmp)->previous)
	{
		*tmp = (*tmp)->previous;
		lst_pop((*tmp)->next, &data->token_list);
		merge_cmd(*tmp, data);
		*tmp = (*tmp)->next;
	}
	else
	{
		lst_pop(*tmp, &data->token_list);
		*tmp = data->token_list;
	}
}

void	less_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	fd = -2;
	if (access(filepath, R_OK) == 0)
	{
		fd = open(filepath, O_RDONLY);
		if ((*tmp)->previous == NULL && (*tmp)->next)
		{
			if ((*tmp)->next->in > -1)
				close((*tmp)->next->in);
			(*tmp)->next->in = fd;
		}
		else if ((*tmp)->previous)
		{
			if ((*tmp)->previous->in > -1)
				close((*tmp)->previous->in);
			(*tmp)->previous->in = fd;
		}
	}
	else
		less_fail(fd, tmp);
	end_handlers(filepath, tmp, data);
}

void	great_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if ((*tmp)->previous == NULL && (*tmp)->next)
		{
			if ((*tmp)->next->out > -1)
				close((*tmp)->next->out);
			(*tmp)->next->out = fd;
		}
		else if ((*tmp)->previous)
		{
			if ((*tmp)->previous->out > -1)
				close((*tmp)->previous->out);
			(*tmp)->previous->out = fd;
		}
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

void	dgreat_handler(char *filepath, t_token **tmp, t_data *data)
{
	int		fd;

	if (access(filepath, W_OK) == 0 || access(filepath, F_OK) == -1)
	{
		fd = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if ((*tmp)->previous == NULL && (*tmp)->next)
		{
			if ((*tmp)->next->out > -1)
				close((*tmp)->next->out);
			(*tmp)->next->out = fd;
		}
		else if ((*tmp)->previous)
		{
			if ((*tmp)->previous->out > -1)
				close((*tmp)->previous->out);
			(*tmp)->previous->out = fd;
		}
	}
	else
		perror("MiniShell: Error");
	end_handlers(filepath, tmp, data);
}

bool	is_redir_token(t_token *elem)
{
	if (elem == NULL)
		return (false);
	else if (elem->type == LESS || elem->type == DLESS
		|| elem->type == GREAT || elem->type == DGREAT)
		return (true);
	return (false);
}
