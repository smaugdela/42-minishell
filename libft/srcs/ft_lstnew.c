/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:21:12 by chduong           #+#    #+#             */
/*   Updated: 2022/03/30 19:44:58 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *envp, char *var, char *value)
{
	t_list	*a;

	a = malloc(sizeof(t_list));
	if (!a)
		return (NULL);
	a->line = NULL;
	a->var = NULL;
	a->value = NULL;
	if (envp)
		a->line = ft_strdup(envp);
	if (var)
		a->var = ft_strdup(var);
	if (value)
		a->value = ft_strdup(value);
	a->prev = NULL;
	a->next = NULL;
	return (a);
}
