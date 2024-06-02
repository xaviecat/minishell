/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gbsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:15:28 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/12 11:56:49 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @biref count the number of string after splitting
 * @return the total count of string + 1
 */
static size_t	countwords(char const *s, char c)
{
	size_t	i;
	size_t	wcount;

	i = 0;
	wcount = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
		wcount++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i])
				wcount++;
			else
				return (wcount);
		}
		i++;
	}
	return (wcount);
}

/**
 * @brief fills the tab with the splitted string
 */
static void	filltab(char *s, char c, char **tbl, t_garbage **gb)
{
	size_t	start;
	size_t	wcount;
	size_t	i;
	size_t	l;

	wcount = countwords(s, c);
	i = 0;
	l = 0;
	while (i != wcount)
	{
		while (s[l] == c)
			l++;
		if (s[l] && s[l] != c)
		{
			start = l;
			while (s[l] && s[l] != c)
				l++;
			tbl[i] = ft_gbsubstr(s, start, l - start, gb);
			if (!tbl[i])
				return (ft_gbtabfree(tbl, gb));
			i++;
		}
	}
}

/**
 * @brief split a string on each char c found
 * and allocates the new tab in garbage collector
 * @param s the string to split
 * @param c the char to split on
 * @return the splitted string in a string tab on sucess \n
 * NULL on allocation error
 */
char	**ft_gbsplit(char const *s, char c, t_garbage **gb)
{
	char	**tbl;
	size_t	wcount;

	if (!s)
		return (NULL);
	wcount = countwords(s, c);
	tbl = ft_malloc(gb, sizeof(char *), (wcount + 1));
	if (!tbl)
		return (0);
	filltab((char *)s, c, tbl, gb);
	tbl[wcount] = NULL;
	return (tbl);
}
