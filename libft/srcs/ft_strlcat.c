/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:25:31 by chduong           #+#    #+#             */
/*   Updated: 2021/05/31 15:56:46 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = ft_strlen(dst);
	if (dstsize > i)
	{
		while (*src && i < dstsize - 1)
		{
			dst[i++] = *src;
			src++;
		}
		dst[i] = '\0';
		return (ft_strlen(dst) + ft_strlen(src));
	}
	return (dstsize + ft_strlen(src));
}
