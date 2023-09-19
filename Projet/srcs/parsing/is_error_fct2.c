/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error_fct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:19:56 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/30 17:00:44 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	is_exclamation_error(t_char_lst *lst)
{
	if (lst->c == '!' && !lst->s_quote && !lst->d_quote)
		return (true);
	return (false);
}

bool	is_colon_error(t_char_lst *lst)
{
	if (lst->c == ':' && !lst->s_quote && !lst->d_quote)
		return (true);
	return (false);
}

bool	is_star_error(t_char_lst *lst)
{
	if (lst->c == '*' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH STAR), true);
	return (false);
}

bool	is_parenthese_error(t_char_lst *lst)
{
	if (lst->c == '(' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH P_OPEN), true);
	else if (lst->c == ')' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH P_CLOSE), true);
	return (false);
}

bool	is_dot_error(t_char_lst *lst)
{
	if (lst->c == '.' && !lst->s_quote
		&& !lst->d_quote && !lst->next && !lst->prev)
		return (ft_fdprintf(2, MSH DOT), true);
	return (false);
}
