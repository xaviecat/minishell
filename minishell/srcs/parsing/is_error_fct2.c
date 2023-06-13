/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error_fct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:19:56 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/12 17:42:51 by xcharra          ###   ########.fr       */
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
