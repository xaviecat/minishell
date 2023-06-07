/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unhandled_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:43:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/07 18:31:50 by xcharra          ###   ########.fr       */
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
	while (lst)
	{
		if (lst->c == '&' && !lst->s_quote && !lst->d_quote)
		{
			if (lst->next && lst->next->c == '&')
				return (ft_fdprintf(2, RED D_AMP RESET), true);
			return (ft_fdprintf(2, RED S_AMP RESET), true);
		}
		if (lst->c == '|' && lst->next && lst->next->c == '|'
			&& !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2,
								RED D_PIPE RESET), true);
		if (lst->c == ';' && !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2, RED SEMICOLON RESET), true);
		if (lst->c == '\\' && !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2, RED BACKSLASH RESET), true);
		if (lst->c == '$' && lst->next && lst->next->c == '$' && !lst->s_quote)
			return (ft_fdprintf(2, RED D_DOLLAR RESET), true);
		if (lst->c == '$' && lst->next && ft_isdigit(lst->next->c) && !lst->s_quote)
			return (ft_fdprintf(2, RED S_DOLLAR(\%c) RESET, lst->next->c), true);
		if (lst->c == '!' && !lst->s_quote && !lst->d_quote)
			return (true);
		if (lst->c == ':' && !lst->s_quote && !lst->d_quote)
			return (true);
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
		return (printf(RED S_GR_A_BRA RESET),
			true);
	else if (i > 3)
		return (printf(RED D_GR_A_BRA RESET),
			true);
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