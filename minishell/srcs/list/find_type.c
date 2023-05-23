/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:17:00 by syluiset          #+#    #+#             */
/*   Updated: 2023/05/23 16:34:14 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_a_bultin(char *word)
{
	if (ft_strncmp(word, "exit", 5) == 0)
		return (builtin);
	if (ft_strncmp(word, "echo", 5) == 0)
		return (builtin);
	if (ft_strncmp(word, "cd", 3) == 0)
		return (builtin);
	if (ft_strncmp(word, "pwd", 4) == 0)
		return (builtin);
	if (ft_strncmp(word, "export", 7) == 0)
		return (builtin);
	if (ft_strncmp(word, "unset", 6) == 0)
		return (builtin);
	if (ft_strncmp(word, "env", 4) == 0)
		return (builtin);
	return (command);
}

/**
 * @brief checking if the word is part of the first group of type
 * @param word
 * @return the type of the word, not_define if is not part of the first group
 */
int	get_cat_of_word(char *word)
{
	if (ft_strncmp(word, "<", 2) == 0)
		return (open_file);
	if (ft_strncmp(word, "<<", 3) == 0)
		return (hd);
	if (ft_strncmp(word, ">", 2) == 0)
		return (redir);
	if (ft_strncmp(word, ">>", 3) == 0)
		return (appnd);
	if (ft_strncmp(word, "-", 1) == 0)
		return (param);
	if (ft_strncmp(word, "|", 1) == 0)
		return (w_pipe);
	if (ft_strchr(word, '$') != NULL)
		return (expand);
	if (ft_strchr(word, '\'') != NULL)
		return (in_s_quote);
	if (ft_strchr(word, '\"') != NULL)
		return (in_d_quote);
	return (not_define);
}

/**
 * @brief give a type to the character c
 * @param c
 * @return type of character
 */
int	find_type_of_c(char c)
{
	if (c == 9 || c == 32)
		return (space);
	if (c == '\'')
		return (s_quote);
	if (c == '\"')
		return (d_quote);
	if (c == '|')
		return (c_pipe);
	if (c == '-')
		return (dash);
	if (c == '<' || c == '>')
		return (a_bracket);
	if (c == '$')
		return (dollar);
	return (charc);
}

/**
 * @brief find the type to all the list of character
 * @param lst
 */
void	give_type_in_lst(t_char_lst **lst)
{
	t_char_lst	*first;

	first = *lst;
	while (*lst)
	{
		(*lst)->type = find_type_of_c((*lst)->c);
		*lst = (*lst)->next;
	}
	*lst = first;
}

