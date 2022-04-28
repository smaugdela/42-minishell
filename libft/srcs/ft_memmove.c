/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 16:27:42 by chduong           #+#    #+#             */
/*   Updated: 2021/06/14 19:11:45 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	i = 0;
	if (dst == src)
		return (dst);
	while (len-- > 0)
	{
		if (src < dst)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		else
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		++i;
	}	
	return (dst);
}
