/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gbitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:57:21 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/19 12:59:55 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static char	*ifpos(int n, int len, int i, t_garbage **gb)
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
	nbr = ft_malloc (gb, sizeof(*nbr), len + 1);
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

static char	*ifneg(int n, int len, int i, t_garbage **gb)
{
	char	*nbr;
	int		ntmp;

	ntmp = n;
	nbr = ft_malloc (gb, sizeof(*nbr), (len + 1));
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

char	*ft_gbitoa(int n, t_garbage **gb)
{
	int	ntmp;
	int	len;
	int	i;

	ntmp = n;
	len = 0;
	i = 0;
	if (ntmp == -2147483648)
		return (ft_gbstrdup("-2147483648", gb));
	if (ntmp == 0)
		return (ft_gbstrdup("0", gb));
	if (n > 0)
		return (ifpos(ntmp, len, i, gb));
	if (n < 0)
	{
		len += 1;
		ntmp *= -1;
		while (ntmp != 0)
		{
			len += 1;
			ntmp /= 10;
		}
		return (ifneg(n * -1, len, i, gb));
	}
	return (NULL);
}
