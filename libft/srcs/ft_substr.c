/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:46:08 by chduong           #+#    #+#             */
/*   Updated: 2021/06/11 14:36:59 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	p = malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (NULL);
	if (ft_strlen(s) > start)
		ft_strlcpy(p, s + start, len + 1);
	else
		*p = 0;
	return (p);
}
