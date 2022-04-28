/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 15:27:23 by chduong           #+#    #+#             */
/*   Updated: 2022/04/21 17:20:53 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!p)
		return (NULL);
	if (s1)
		ft_strlcpy(p, s1, len1 + 1);
	if (!s1 && s2)
		ft_strlcpy(p, s2, len2 + 1);
	else if (s1 && s2)
		ft_strlcat(p, s2, len1 + len2 + 1);
	return (p);
}
