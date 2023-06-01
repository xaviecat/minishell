/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unhandled_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:43:08 by xcharra           #+#    #+#             */
/*   Updated: 2023/06/01 17:34:56 by xcharra          ###   ########.fr       */
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
		if (lst->c == '\\' && !lst->s_quote && !lst->d_quote)
			return (ft_fdprintf(2,
					"minishell: feature not handled: '\\'\n"), true);
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
		return (printf("minishell: syntax error near unexpected token `<'\n"),
			true);
	else if (i > 3)
		return (printf("minishell: syntax error near unexpected token `<<'\n"),
			true);
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
		return (printf("minishell: syntax error near unexpected token `>'\n"),
			true);
	else if (i > 3)
		return (printf("minishell: syntax error near unexpected token `>>'\n"),
			true);
	return (false);
}

bool	is_bad_redir(t_char_lst *lst)
{
	while (lst)
	{
		if ((lst->c == '<' && is_smaller_bracket_error(&lst))
			|| (lst->c == '>' && is_greater_bracket_error(&lst))) //Segfault si line = < ou <<
			return (true);
		if (lst)
			lst = lst->next;
	}
	return (false);
}
