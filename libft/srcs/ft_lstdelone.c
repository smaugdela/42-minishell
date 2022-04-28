/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:54:00 by chduong           #+#    #+#             */
/*   Updated: 2022/04/27 11:49:31 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*next;

	if (!lst || !del)
		return ;
	prev = lst->prev;
	next = lst->next;
	if (lst->line)
		del(lst->line);
	if (lst->var)
		del(lst->var);
	if (lst->value)
		del(lst->value);
	free(lst);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}
