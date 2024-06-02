/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error_fct1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:19:56 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/03 13:33:18 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Check if there are a ampersand error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_amp_error(t_char_lst *lst)
{
	if (lst->c == '&' && !lst->s_quote && !lst->d_quote)
	{
		if (lst->next && lst->next->c == '&')
			return (ft_fdprintf(2, MSH D_AMP), true);
		return (ft_fdprintf(2, MSH S_AMP), true);
	}
	return (false);
}

/**
 * @brief Check if there are a double pipe error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_pipe_error(t_char_lst *lst)
{
	if (lst->c == '|' && lst->next && lst->next->c == '|'
		&& !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH D_PIPE), true);
	return (false);
}

/**
 * @brief Check if there are a semicolon error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_semicolon_error(t_char_lst *lst)
{
	if (lst->c == ';' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH SEMICOLON), true);
	return (false);
}

/**
 * @brief Check if there are a backslash error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_backslash_error(t_char_lst *lst)
{
	if (lst->c == '\\' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH BACKSLASH), true);
	return (false);
}

/**
 * @brief Check if there are a double dollar error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_dollar_error(t_char_lst *lst)
{
	if (lst->c == '$' && lst->next && lst->next->c == '$' && !lst->s_quote)
		return (ft_fdprintf(2, MSH D_DOLLAR), true);
	if (lst->c == '$' && lst->next && ft_isdigit(lst->next->c) && !lst->s_quote)
		return (ft_fdprintf(
				2, MSH S_DOLLAR"%c'\n", lst->next->c), true);
	return (false);
}
