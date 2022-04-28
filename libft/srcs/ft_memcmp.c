/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 18:57:00 by chduong           #+#    #+#             */
/*   Updated: 2021/05/29 15:34:21 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char const	*t1;
	unsigned char const	*t2;

	t1 = s1;
	t2 = s2;
	if (n == 0)
		return (0);
	while (*t1 == *t2 && --n)
	{
		++t1;
		++t2;
	}
	return ((int)(*t1 - *t2));
}
