/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:37:46 by smagdela          #+#    #+#             */
/*   Updated: 2022/04/26 11:51:07 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_data *data)
{
	int		count;
	t_token	*tmp;

	count = 0;
	if (data == NULL || data->token_list == NULL)
		return (0);
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->cmd && tmp->cmd[0])
			++count;
		tmp = tmp->next;
	}
	return (count);
}

char	*get_filepath(char **filename)
{
	char	*pwd;
	char	*filepath;

	if (filename == NULL || *filename == NULL)
		return (NULL);
	if (*filename[0] == '/')
		return (ft_strdup(*filename));
	pwd = getcwd(NULL, 0);
	filepath = path_join(pwd, *filename);
	free(pwd);
	pwd = NULL;
	free(*filename);
	*filename = NULL;
	return (filepath);
}

void	check_exit_status(void)
{
	if (g_status == (128 | SIGQUIT))
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	else if (g_status == (128 | SIGSEGV))
		ft_putstr_fd("Segmentation fault (core dumped)\n",
			STDERR_FILENO);
	else if (g_status == (128 | SIGINT))
		ft_putchar_fd('\n', STDERR_FILENO);
}

void	less_fail(int fd, t_token **elem)
{
	perror("MiniShell: Error");
	if ((*elem)->previous == NULL && (*elem)->next)
	{
		if ((*elem)->next->in > -1)
			close((*elem)->next->in);
		(*elem)->next->in = fd;
	}
	else if ((*elem)->previous)
	{
		if ((*elem)->previous->in > -1)
			close((*elem)->previous->in);
		(*elem)->previous->in = fd;
	}
}
