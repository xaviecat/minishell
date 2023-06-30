/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error_fct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:19:56 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/28 13:13:35 by syluiset         ###   ########.fr       */
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
		return (ft_fdprintf(2, RED MSH STAR RESET), true);
	return (false);
}

bool	is_parenthese_error(t_char_lst *lst)
{
	if (lst->c == '(' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, RED MSH P_OPEN RESET), true);
	else if (lst->c == ')' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, RED MSH P_CLOSE RESET), true);
	return (false);
}