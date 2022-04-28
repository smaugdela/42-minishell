/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:24:39 by chduong           #+#    #+#             */
/*   Updated: 2022/02/28 14:57:32 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_str(char const *str, char set)
{
	int	count;

	count = 1;
	if (set == 0 || !ft_strchr(str, set))
		return (count);
	while (*str == set)
		++str;
	if (str[ft_strlen(str) - 1] == set)
		--count;
	while (*str && ft_strchr(str, set))
	{
		str = ft_strchr(str, set);
		while (*str == set)
			++str;
		++count;
	}
	return (count);
}

static int	sublen(char const *str, char set)
{
	int	i;

	i = 0;
	while (*str == set)
		++str;
	while (str[i] && str[i] != set)
		++i;
	return (i);
}

static char	*getnext(char *dst, char const *src, char c, size_t len)
{
	while (*src == c)
		++src;
	ft_strlcpy(dst, src, len + 1);
	return ((char *)src + len);
}

static char	**freeall(char **tab, int i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		strs;
	int		len;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	strs = count_str(s, c);
	tab = malloc(sizeof(*tab) * (strs + 1));
	if (!tab)
		return (NULL);
	while (*s && i < strs)
	{
		len = sublen(s, c);
		tab[i] = malloc(sizeof(**tab) * (len + 1));
		if (!tab[i])
			return (freeall(tab, i));
		s = getnext(tab[i], s, c, len);
		++i;
	}
	tab[i] = NULL;
	return (tab);
}
