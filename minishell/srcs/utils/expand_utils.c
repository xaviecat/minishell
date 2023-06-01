/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:01:30 by nfaust            #+#    #+#             */
/*   Updated: 2023/05/31 16:58:38 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/***
 * @brief duplicate str until one char matches the charset
 * @param str the string that you wanr to duplicate
 * @param charset the charset of delimiters
 * @return the duplicated string
 */
char *ft_gbstrdup_to_charset(char *str, char *charset, t_garbage **gb)
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
	new_str = ft_malloc(gb, sizeof(char), new_str_len + char_not_found);
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

/**
 * @brief find out if the env var is a dollar surrounded by no quotes
 * @param env_var the environment variable
 * @param cmd the total cmd
 * @param start the start index ($pos)
 * @return 1 if the $ sybol is alone \n 0 if not
 */
int	is_dollar_alone(char *env_var, char *cmd, size_t start)
{
	if (ft_strlen(env_var) == 1 && !(cmd[start + 1]
			&& (cmd[start + 1] != '"' || cmd[start + 1] != '\'')))
		return (1);
	return (0);
}

void ft_free_mcmd(char *env_var, char *cmd, char *exp_env_var, t_garbage **gb)
{
	ft_free(gb, env_var);
	ft_free(gb, cmd);
	ft_free(gb, exp_env_var);
}

/**
 * @brief allocate modified command (expanded) and fill it with
 * corresponding char
 * @param cmd all parameters are inherited from modify command
 * @param start
 * @param exp_env_v
 * @param env_var
 * @return the modified command
 */
char *fill_mdcmd(char *cmd, size_t start, char *exp_env_v, char *env_var)
{
	size_t	i;
	char	*m_cmd;

	m_cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1
				+ (ft_strlen(exp_env_v) - ft_strlen(env_var))));
	if (!m_cmd)
		return (NULL);
	str_cpy_to_x(cmd, m_cmd, '$');
	i = 0;
	while (exp_env_v[i])
		m_cmd[start++] = exp_env_v[i++];
	i = (start - i) + ft_strlen(env_var);
	while (cmd[i])
		m_cmd[start++] = cmd[i++];
	m_cmd[start] = 0;
	return (m_cmd);
}
