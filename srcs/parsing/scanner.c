/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:31:12 by smagdela          #+#    #+#             */
/*   Updated: 2022/03/31 17:30:37 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	categorizer_aux(t_input *input, t_token **token_list)
{
	int	ret;

	ret = categ_1(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_2(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_3(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_4(input, token_list);
	if (ret != 1)
		return (ret);
	ret = categ_5(input, token_list);
	if (ret != 1)
		return (ret);
	return (-1);
}

/*
Ask what category is the data from the input, and create token accordingly.
*/
bool	categorizer(t_input *input, t_token **token_list)
{
	int	ret;

	ret = categorizer_aux(input, token_list);
	if (ret == 0)
		return (true);
	free_toklist(token_list);
	return (false);
}

/*
Core function of the lexer.
*/
t_token	*scanner(const char *str)
{
	t_token		*token_list;
	t_input		input;

	if (!str)
	{
		ft_putstr_fd("Error: Null string passed to scanner\n", 2);
		return (NULL);
	}
	token_list = NULL;
	input.str = str;
	input.index = 0;
	while (input.index < ft_strlen(str))
	{
		if (categorizer(&input, &token_list) == false)
			break ;
	}
	return (token_list);
}
