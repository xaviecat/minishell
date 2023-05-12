/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:01:30 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/12 18:48:19 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/***
 * @brief duplicate str until one char matches the charset
 * @param str the string that you wanr to duplicate
 * @param charset the charset of delimiters
 * @return the duplicated string
 */
char	*ft_strdup_to_charset(char *str, char *charset)
{
	size_t	new_str_len;
	size_t	i;
	char	*new_str;
	int		char_not_found;

	new_str_len = 0;
	char_not_found = 1;
	while (str[new_str_len] && char_not_found)
	{
		i = 0;
		while (charset[i])
			if (str[new_str_len] == charset[i++])
				char_not_found = 0;
		new_str_len++;
	}
	new_str = malloc(sizeof(char) * (new_str_len + char_not_found));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < new_str_len + char_not_found - 1)
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str[i] = 0, new_str);
}

int ft_isspace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

static size_t	count_chars_to_keep(char *str)
{
	size_t	counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (str[i++])
		if ((ft_isspace(str[i - 1]) && !ft_isspace(str[i]))
			|| !ft_isspace(str[i - 1]))
			counter++;
	return (counter);
}

/**
 * @brief trim str and replaces whitespaces in str by one space (32) only
 * @param str the string you want spaces to be deleted from
 * @return cleaned string
 */
char	*cut_whitespaces(char *str)
{
	size_t	trimed_len;
	size_t	j;
	size_t	counter;
	char	*trimed_str;

	trimed_str = ft_strtrim(str, " \t\n\v\f\r");
	if (str)
		free(str);
	if (!trimed_str)
		return (NULL);
	trimed_len = ft_strlen(trimed_str);
	counter = count_chars_to_keep(trimed_str);
	str = malloc(sizeof(char) * (counter + 1));
	if (!str)
		return (free(trimed_str), NULL);
	j = 0;
	while (trimed_str[0])
	{
		while (ft_isspace(trimed_str[0]) && trimed_str[1]
			&& ft_isspace(trimed_str[1]))
			trimed_str++;
		str[j++] = trimed_str++[0];
	}
	return (free(trimed_str - trimed_len), str[j] = 0, str);
}

/**
 * @brief copy src to dest, until x is found in src. DST MUST BE ABLE TO CONTAIN
 * ALL CHARS BEFORE X IN SRC
 * @param src the string that you want to copy
 * @param dst the string where you want to copy src in
 * @param x the delimiter
 * @return dst
 */
char	*str_cpy_to_x(char *src, char *dst, char x)
{
	size_t	i;

	if (!src || !dst)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != x)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}