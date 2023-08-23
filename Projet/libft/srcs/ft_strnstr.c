/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:08:18 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/08 16:46:05 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	k;
	size_t	l;

	if (!to_find[0])
		return ((char *)str);
	l = ft_strlen(to_find);
	i = 0;
	while (i != n && str[i])
	{
		k = 0;
		while (i != n && k < l && str[i] == to_find[k])
		{
			if (k == l - 1)
				return (&((char *)str)[i - k]);
			i++;
			k++;
		}
		i -= k;
		i++;
	}
	return (0);
}
