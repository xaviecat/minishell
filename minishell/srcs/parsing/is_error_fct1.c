/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error_fct1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:19:56 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/26 16:08:26 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

bool	is_amp_error(t_char_lst *lst)
{
	if (lst->c == '&' && !lst->s_quote && !lst->d_quote)
	{
		if (lst->next && lst->next->c == '&')
			return (ft_fdprintf(2, RED MSH D_AMP RESET), true);
		return (ft_fdprintf(2, RED MSH S_AMP RESET), true);
	}
	return (false);
}

bool	is_pipe_error(t_char_lst *lst)
{
	if (lst->c == '|' && lst->next && lst->next->c == '|'
		&& !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, RED MSH D_PIPE RESET), true);
	return (false);
}

bool	is_semicolon_error(t_char_lst *lst)
{
	if (lst->c == ';' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, RED MSH SEMICOLON RESET), true);
	return (false);
}

bool	is_backslash_error(t_char_lst *lst)
{
	if (lst->c == '\\' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, RED MSH BACKSLASH RESET), true);
	return (false);
}

bool	is_dollar_error(t_char_lst *lst)
{
	if (lst->c == '$' && lst->next && lst->next->c == '$' && !lst->s_quote)
		return (ft_fdprintf(2, RED MSH D_DOLLAR RESET), true);
	if (lst->c == '$' && lst->next && ft_isdigit(lst->next->c) && !lst->s_quote)
		return (ft_fdprintf(
				2, RED MSH S_DOLLAR"%c'\n"RESET, lst->next->c), true);
	return (false);
}
