/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:10:05 by xcharra           #+#    #+#             */
/*   Updated: 2022/11/16 10:21:56 by xcharra          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check(char s, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] && s == set[i])
			return (1);
		else if (set[i] && s != set[i])
			i++;
	}
	return (0);
}

static size_t	delimit(char *s, char *set, size_t mod)
{
	size_t	start;
	size_t	end;

	start = 0;
	end = ft_strlen(s) - 1;
	if (mod == 0)
	{
		while (s[start] && check(s[start], set) == 1)
			start++;
		return (start);
	}
	if (mod == 1)
	{
		while (end != 0 && check(s[end], set) == 1)
			end--;
		return (end + 1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	start = delimit((char *)s1, (char *)set, 0);
	end = delimit((char *)s1, (char *)set, 1);
	if (!s1)
		return (NULL);
	trimed = ft_substr((char *)s1, start, end - start);
	return (trimed);
}
