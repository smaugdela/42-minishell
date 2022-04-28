/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:40:24 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/24 20:41:31 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	matriochka_aux(char **str, t_data *data, size_t i)
{
	char	*envar_name;
	char	*envar_value;
	char	*new_data;
	size_t	len;

	envar_name = ft_substr(*str, i + 1, ft_envarlen(*str + i + 1));
	envar_value = find_envar(envar_name, data);
	new_data = ft_substr(*str, 0, i);
	new_data = my_strcat(new_data, envar_value);
	new_data = my_strcat(new_data, *str + i + ft_strlen(envar_name) + 1);
	free(envar_name);
	len = ft_strlen(envar_value);
	free(envar_value);
	free(*str);
	*str = new_data;
	return (len - 1);
}

/*
Expand environement variables inside the already expanded ones, if present.
*/
void	matriochka(char **str, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(*str) && (*str)[i])
	{
		if ((*str)[i] == '$')
		{
			i += matriochka_aux(str, data, i);
		}
		++i;
	}
}

static void	heredoc_aux(t_token **tmp)
{
	if ((*tmp)->previous)
	{
		if ((*tmp)->previous->in > -1)
			close((*tmp)->previous->in);
		(*tmp)->previous->in = (*tmp)->pipefd[0];
	}
	else if ((*tmp)->next)
	{
		if ((*tmp)->next->in > -1)
			close((*tmp)->next->in);
		(*tmp)->next->in = (*tmp)->pipefd[0];
	}
}

void	heredoc(char *delim, t_token **tmp, t_data *data)
{
	pid_t	pid;

	if (!delim || !*tmp)
		return (perror("MiniShell: Bad Heredoc"));
	if (pipe((*tmp)->pipefd) == -1)
		return (perror("MiniShell: Pipe failed"));
	heredoc_aux(tmp);
	pid = fork();
	if (pid < 0)
		return (perror("MiniShell: Error"));
	else if (pid == 0)
		child_prompt(delim, tmp, data);
	close((*tmp)->pipefd[1]);
	waitpid(pid, NULL, 0);
	end_handlers(NULL, tmp, data);
}
