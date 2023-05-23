/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:43:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/17 18:41:56 by xcharra          ###   ########.fr       */
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
				return (ft_fdprintf(2,
						"minishell: feature not handled: '&&'\n"), true);
			return (ft_fdprintf(2,
					"minishell: feature not handled: '&'\n"), true);
		}
		if (lst->c == '|' && lst->next && lst->next->c == '|'
			&& !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2,
					"minishell: feature not handled: '||'\n"), true);
		if (lst->c == ';' && !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2,
					"minishell: feature not handled: ';'\n"), true);
		lst = lst->next;
	}
	return (false);
}
