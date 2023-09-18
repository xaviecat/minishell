/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:12:47 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/22 18:01:09 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str);
	if (c == '\0')
		return (&((char *)str)[i]);
	while (i > 0 && ((char *)str)[i] != (unsigned char)c)
		i--;
	if (((char *)str)[i] == (unsigned char)c)
		return (&((char *)str)[i]);
	return (NULL);
}
