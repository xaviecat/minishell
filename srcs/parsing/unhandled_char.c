/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unhandled_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:43:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/03 13:33:12 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Iterate through the list to see if there are any unhandled characters
 * @param lst list of characters
 * @return true if there are any unhandled characters
 * @return false if it's not the case
 */
bool	is_forbidden_char(t_char_lst *lst)
{
	static t_unhandled_tab	is_error_fct[11] = {&is_amp_error, &is_pipe_error,
		&is_semicolon_error, &is_backslash_error, &is_dollar_error,
		&is_exclamation_error, &is_parenthesis_error,
		&is_star_error, &is_dot_error, NULL};
	size_t					i;

	while (lst)
	{
		i = 0;
		while (is_error_fct[i])
		{
			if (is_error_fct[i](lst) == false)
				i++;
			else
				return (true);
		}
		lst = lst->next;
	}
	return (false);
}

/**
 * @brief Check if there are a < error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_smaller_bracket_error(t_char_lst **lst)
{
	int	i;

	i = 0;
	while ((*lst) && (*lst)->c == '<')
	{
		(*lst) = (*lst)->next;
		i++;
	}
	if (i == 3)
		return (printf(MSH S_SM_A_BRA), true);
	else if (i > 3)
		return (printf(MSH D_SM_A_BRA), true);
	return (false);
}

/**
 * @brief Check if there are a > error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_greater_bracket_error(t_char_lst **lst)
{
	int	i;

	i = 0;
	while ((*lst) && (*lst)->c == '>')
	{
		(*lst) = (*lst)->next;
		i++;
	}
	if (i == 3)
		return (ft_fdprintf(2, MSH S_GR_A_BRA), true);
	else if (i > 3)
		return (ft_fdprintf(2, MSH D_GR_A_BRA), true);
	return (false);
}

/**
 * @brief Check if there are a bad redirection error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_bad_redir(t_char_lst *lst)
{
	while (lst)
	{
		if (lst->next && lst->c == '<' && lst->next->c == '>')
		{
			ft_fdprintf(2, MSH NL_TKN);
			return (true);
		}
		if (lst->c == '<')
		{
			if (is_smaller_bracket_error(&lst))
				return (true);
		}
		else if (lst->c == '>')
		{
			if (is_greater_bracket_error(&lst))
				return (true);
		}
		else if (lst)
			lst = lst->next;
	}
	return (false);
}

/**
 * @brief Check if there are a some unhandled char or features error in char
 * list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	unhandled_char(t_char_lst *lst)
{
	if (process_quotes(lst))
		return (true);
	if (is_forbidden_char(lst))
		return (true);
	if (is_bad_redir(lst))
		return (true);
	return (false);
}
