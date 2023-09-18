/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:28:11 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/15 13:48:01 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem, int c, size_t n )
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((char *)mem)[i] == (char)c)
			return (&((char *)mem)[i]);
		i++;
	}
	return (NULL);
}
