/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:28:39 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/22 16:45:56 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_gbsubstr(char const *s,
			unsigned int start, size_t len, t_garbage **gb)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	sub = ft_malloc(gb, sizeof(*s), (len + 1));
	if (!sub)
		return (NULL);
	while (i != len && s[i] && (start + i) < ft_strlen(s))
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
