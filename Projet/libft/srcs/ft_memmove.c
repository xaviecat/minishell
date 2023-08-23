/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:32:49 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/15 13:48:26 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *mdst, const void *msrc, size_t n)
{
	size_t	i;

	i = 0;
	if (mdst < msrc)
	{
		while (i < n)
		{
			((unsigned char *)mdst)[i] = ((unsigned char *)msrc)[i];
			i++;
		}
	}
	else if (mdst > msrc)
	{
		while (n != 0)
		{
			n--;
			((unsigned char *)mdst)[n] = ((unsigned char *)msrc)[n];
		}
	}
	return (mdst);
}
