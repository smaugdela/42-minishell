/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:42:12 by chduong           #+#    #+#             */
/*   Updated: 2021/06/18 17:34:45 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	alphalen(long int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		++len;
	}
	while (n > 9)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*a;
	int				len;
	unsigned int	nb;

	nb = n;
	if (n < 0)
		nb = -n;
	len = alphalen(n);
	a = malloc(sizeof(char) * (len + 1));
	if (!a)
		return (NULL);
	a[len] = 0;
	while (len > 0)
	{
		a[--len] = nb % 10 + 48;
		nb /= 10;
	}
	if (n < 0)
		a[0] = '-';
	return (a);
}
