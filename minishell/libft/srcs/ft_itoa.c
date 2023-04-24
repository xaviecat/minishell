/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:39:42 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/16 13:20:09 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ifpos(int n, int len, int i)
{
	char	*nbr;
	int		ntmp;

	ntmp = n;
	while (ntmp != 0)
	{
		len += 1;
		ntmp /= 10;
	}
	ntmp = n;
	nbr = malloc (sizeof(*nbr) * (len + 1));
	if (!nbr)
		return (NULL);
	while (ntmp != 0)
	{
		nbr[len - 1 - i] = (ntmp % 10) + '0';
		ntmp /= 10;
		i++;
	}
	nbr[len] = '\0';
	return (nbr);
}

static char	*ifneg(int n, int len, int i)
{
	char	*nbr;
	int		ntmp;

	ntmp = n;
	nbr = malloc (sizeof(*nbr) * (len + 1));
	if (!nbr)
		return (NULL);
	while (ntmp != 0)
	{
		nbr[len - 1 - i] = (ntmp % 10) + '0';
		ntmp /= 10;
		i++;
	}
	nbr[len] = '\0';
	nbr[0] = '-';
	return (nbr);
}

char	*ft_itoa(int n)
{
	int	ntmp;
	int	len;
	int	i;

	ntmp = n;
	len = 0;
	i = 0;
	if (ntmp == -2147483648)
		return (ft_strdup("-2147483648"));
	if (ntmp == 0)
		return (ft_strdup("0"));
	if (n > 0)
		return (ifpos(ntmp, len, i));
	if (n < 0)
	{
		len += 1;
		ntmp *= -1;
		while (ntmp != 0)
		{
			len += 1;
			ntmp /= 10;
		}
		return (ifneg(n * -1, len, i));
	}
	return (NULL);
}
