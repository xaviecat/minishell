/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:38:11 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/15 13:48:07 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *mem1, const void *mem2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && ((char *)mem1)[i] == ((char *)mem2)[i])
		i++;
	if (i == n)
		return (0);
	return (((unsigned char *)mem1)[i] - ((unsigned char *)mem2)[i]);
}
