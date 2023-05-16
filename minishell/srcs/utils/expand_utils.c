/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:01:30 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/15 18:54:34 by nfaust           ###   ########.fr       */
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

//char *replace_unexpected_whitespaces(char *cmd)
//{
//	size_t	end_index;
//	size_t	i;
//	char	*tmp;
//	char	*result;
//
//	i = 0;
//	end_index = 0;
//	while (cmd[i])
//	{
//		tmp = ft_strdup_to_charset(cmd, "\'\"");
//		if (!tmp)
//			return (NULL);
//		while (cmd[i] != '"' && cmd[i] != '\'')
//			end_index++;
//		cmd += end_index;
//		i = 0;
//	}
//}

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
