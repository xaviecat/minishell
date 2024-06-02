/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gbstrtrim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:41:13 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/10 14:37:14 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief cut set chars appearing before string start and after string end.
 * Allocates the new string in garbage collector
 * @param s1 the string to trim
 * @param set the characters to remove from start and end of string
 * @return the new allocated string
 */
char	*ft_gbstrtrim(char const *s1, char const *set, t_garbage **gb)
{
	char const	*start;
	char		*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_gbstrdup(s1, gb));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	start = s1;
	while (*s1)
		s1++;
	if (s1 == start)
		return (ft_gbcalloc(1, 1, gb));
	s1--;
	while (ft_strchr(set, *s1))
		s1--;
	s1++;
	str = ft_gbcalloc((s1 - start + 1), sizeof(char), gb);
	if (!str)
		return (NULL);
	return (ft_memcpy(str, start, s1 - start));
}
