/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unhandled_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:43:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/08 12:46:17 by xcharra          ###   ########.fr       */
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
	static t_unhandled_char	is_error_fct[8] = {&is_amp_error, &is_pipe_error,
		&is_semicolon_error, &is_backslash_error, &is_dollar_error,
		&is_exclamation_error, &is_colon_error,	NULL};
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
		return (printf(RED S_SM_A_BRA RESET), true);
	else if (i > 3)
		return (printf(RED D_SM_A_BRA RESET), true);
	return (false);
}

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
		return (printf(RED S_GR_A_BRA RESET), true);
	else if (i > 3)
		return (printf(RED D_GR_A_BRA RESET), true);
	return (false);
}

bool	is_bad_redir(t_char_lst *lst)
{
	while (lst)
	{
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