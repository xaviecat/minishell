/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:34:59 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/14 17:41:10 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	ldst;

	i = 0;
	if (n == 0)
		return (ft_strlen(src));
	ldst = ft_strlen(dst);
	if (n > ldst)
	{
		while (ldst + i < n - 1 && src[i])
		{
			dst[ldst + i] = src[i];
			i++;
		}
		dst[ldst + i] = '\0';
	}
	else
		return (ft_strlen(src) + n);
	return (ldst + ft_strlen(src));
}
