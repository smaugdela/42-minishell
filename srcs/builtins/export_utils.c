/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 10:31:59 by kennyduong        #+#    #+#             */
/*   Updated: 2022/04/25 19:47:52 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	print_error(char *varname)
{
	if (varname[0] == '-')
	{
		ft_putstr_fd("MiniShell: export: ", 2);
		ft_putstr_fd(varname, 2);
		ft_putstr_fd("': invalid option\n", 2);
		g_status = 2;
	}
	else
	{
		ft_putstr_fd("MiniShell: export: `", 2);
		ft_putstr_fd(varname, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_status = 1;
	}
	return (false);
}

bool	valid_var(char *varname)
{
	int	i;

	if (varname[0] != '_' && !ft_isalpha(varname[0]))
		return (print_error(varname));
	i = 1;
	while (varname[i] && varname[i] != '=')
	{
		if (varname[i] != '_' && !ft_isalnum(varname[i]))
			return (print_error(varname));
		++i;
	}
	return (true);
}
