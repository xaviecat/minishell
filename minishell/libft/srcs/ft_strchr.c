/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:29:27 by xcharra           #+#    #+#             */
/*   Updated: 2023/03/27 11:03:32 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (((char *)str)[i] && ((char *)str)[i] != (unsigned char)c)
		i++;
	if (((char *)str)[i] == (unsigned char)c)
		return (&((char *)str)[i]);
	return (NULL);
}
