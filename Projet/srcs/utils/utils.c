/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:51 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/04 15:29:04 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

/**
 * @brief check if a char is a whitespace
 * (space, \\t, \\n, \\v, \\f, \\r)
 * @param c the char to check
 * @return 1 if the char is a whitespace, \n 0 if not
 */
int	ft_isspace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

/**
 * @brief count the number of chars in a string cutted by 'cut_whitespaces'
 * @param str the source string in wich you want to count chars to keep
 * @return the number of chars in the final string
 */
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
char	*cut_whitespaces(char *str, t_garbage **gb)
{
	size_t	trimed_len;
	size_t	j;
	size_t	counter;
	char	*trimed_str;

	trimed_str = ft_gbstrtrim(str, " \t\n\v\f\r", gb);
	if (str)
		ft_free(gb, str);
	if (!trimed_str)
		return (NULL);
	trimed_len = ft_strlen(trimed_str);
	counter = count_chars_to_keep(trimed_str);
	str = ft_malloc(gb, sizeof(char), counter + 1);
	if (!str)
		return (ft_free(gb, trimed_str), NULL);
	j = 0;
	while (trimed_str[0])
	{
		while (ft_isspace(trimed_str[0]) && trimed_str[1]
			&& ft_isspace(trimed_str[1]))
			trimed_str++;
		str[j++] = trimed_str++[0];
	}
	return (ft_free(gb, trimed_str - trimed_len), str[j] = 0, str);
}

int	does_contain_quotes(char *str)
{
	size_t	i;

	i = 0;
	while (str[i++])
	{
		if (str[i - 1] == '\'' || str[i - 1] == '"')
			return (1);
	}
	return (0);
}

/**
 * @brief rechecks if a command is a builtin after expand
 * and update the corresponding member of the structure msh
 */
void	recheck_builtin(t_msh *msh)
{
	t_node_lst	*lst_n_cpy;

	lst_n_cpy = msh->lst_n;
	while (lst_n_cpy)
	{
		if (lst_n_cpy->lst_cmd)
			if (lst_n_cpy->lst_cmd->cmd)
				lst_n_cpy->builtin = builtin_or_command(
						lst_n_cpy->lst_cmd->cmd);
		lst_n_cpy = lst_n_cpy->next;
	}
}
