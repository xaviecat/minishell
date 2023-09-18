/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:25:15 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/15 13:48:20 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *mdst, const void *msrc, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || mdst == msrc)
		return (mdst);
	while (i < n)
	{
		((char *)mdst)[i] = ((char *)msrc)[i];
		i++;
	}
	return (mdst);
}
