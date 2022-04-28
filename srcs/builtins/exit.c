/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:08:07 by chduong           #+#    #+#             */
/*   Updated: 2022/04/25 18:37:50 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	only_digit(char *arg)
{
	if (*arg == '+' || *arg == '-')
		++arg;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	return (true);
}

static void	clear_list(t_list **list)
{
	t_list	*tmp;
	t_list	*to_free;

	tmp = *list;
	while (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		if (tmp->var)
			free(tmp->var);
		to_free = tmp;
		tmp = tmp->next;
		free(to_free);
		to_free = NULL;
	}
	*list = NULL;
}

void	free_exit(t_data *data, int opt)
{
	if (data->line)
		free(data->line);
	if (data->path)
		free_tab(data->path);
	if (data->export)
		free_tab(data->export);
	if (data->env)
		clear_list(&data->env);
	if (data->token_list)
		free_toklist(&data->token_list);
	rl_clear_history();
	exit(opt);
}

static bool	ft_checkllint(char *nb)
{
	char	*int_extremum;
	int		i;

	i = 0;
	if (nb[0] == '-')
	{
		int_extremum = "-9223372036854775808";
		i = 1;
	}
	else
		int_extremum = "9223372036854775807";
	if (ft_strlen(nb) >= ft_strlen(int_extremum))
	{
		while (nb[i])
		{
			if (nb[i] > int_extremum[i] || !ft_isdigit(nb[i]))
				return (false);
			++i;
		}
		return (true);
	}
	else
		return (true);
}

void	exit_ms(char **arg, t_data *data)
{
	int	nb_arg;

	nb_arg = count_str(arg);
	ft_putstr_fd("exit\n", 2);
	if (nb_arg == 1)
	{
		free_exit(data, EXIT_SUCCESS);
	}
	else
	{
		if (only_digit(arg[1]) == false || ft_checkllint(arg[1]) == false)
		{
			ft_putstr_fd("Minishell: exit:", STDERR_FILENO);
			ft_putstr_fd(arg[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			free_exit(data, 2);
		}
		else if (nb_arg > 2)
		{
			ft_putstr_fd("Minishell: exit: too many arguments\n", STDERR_FILENO);
			g_status = 1;
		}
		else
			free_exit(data, ft_atoi(arg[1]));
	}
}
