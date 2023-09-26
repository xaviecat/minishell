/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error_fct2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:19:56 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/25 11:55:36 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Check if there are a exclamation point error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_exclamation_error(t_char_lst *lst)
{
	if (lst->c == '!' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH EXCL), true);
	return (false);
}

/**
 * @brief Check if there are a star error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_star_error(t_char_lst *lst)
{
	if (lst->c == '*' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH STAR), true);
	return (false);
}

/**
 * @brief Check if there are a parenthesis error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_parenthesis_error(t_char_lst *lst)
{
	if (lst->c == '(' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH P_OPEN), true);
	else if (lst->c == ')' && !lst->s_quote && !lst->d_quote)
		return (ft_fdprintf(2, MSH P_CLOSE), true);
	return (false);
}

/**
 * @brief Check if there are a dot error in char list
 * @param lst list of char create from the command line
 * @return true if there is an error and false otherwise
 */
bool	is_dot_error(t_char_lst *lst)
{
	if (lst->c == '.' && !lst->s_quote
		&& !lst->d_quote && !lst->next && !lst->prev)
		return (ft_fdprintf(2, MSH DOT), true);
	return (false);
}
