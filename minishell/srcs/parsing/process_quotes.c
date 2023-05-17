/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:10:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/17 17:10:57 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Connect the single quotes together
 * @author xcharra
 */
void	process_single_quotes(t_char_lst **tmp)
{
	bool		sq;

	sq = true;
	(*tmp)->s_quote = true;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && sq)
	{
		(*tmp)->s_quote = true;
		if ((*tmp)->c == '\'')
			sq = false;
		(*tmp) = (*tmp)->next;
	}
}

/**
 * @brief Connect the double quotes together
 * @author xcharra
 */
void	process_double_quotes(t_char_lst **tmp)
{
	bool		dq;

	dq = true;
	(*tmp)->d_quote = true;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && dq)
	{
		(*tmp)->d_quote = true;
		if ((*tmp)->c == '\"')
			dq = false;
		(*tmp) = (*tmp)->next;
	}
}

/**
 * @brief Search for any unclosed quotes if the last characters of the
 * list isn't a quote
 * @param tmp
 * @return true if there are a non closed quote
 * @return false if all quotes are closed
 * @author xcharra
 */
bool	seek_alone_quote(t_char_lst **tmp)
{
	while (((*tmp) && (*tmp)->s_quote) || ((*tmp) && (*tmp)->d_quote))
	{
		if (((*tmp)->s_quote && (*tmp)->c == '\'')
			|| ((*tmp)->d_quote && (*tmp)->c == '\"'))
		{
			(*tmp)->s_quote = false;
			(*tmp)->d_quote = false;
			(*tmp)->a_quote = true;
			return (true);
		}
		(*tmp)->s_quote = false;
		(*tmp)->d_quote = false;
		(*tmp) = (*tmp)->prev;
	}
	(*tmp)->s_quote = false;
	(*tmp)->d_quote = false;
	return (false);
}

/**
 * @brief Search for any unclosed quotes
 * @param lst
 * @return true if there are a non closed quote
 * @return false if all quotes are closed
 * @author xcharra
 */
bool	is_quote_alone(t_char_lst *lst)
{
	t_char_lst	*tmp;

	tmp = char_lst_last(lst);
	while (tmp)
	{
		if ((tmp->s_quote && tmp->c == '\''
				&& (!tmp->prev || !tmp->prev->s_quote))
			|| (tmp->d_quote && tmp->c == '\"'
				&& (!tmp->prev || !tmp->prev->d_quote)))
		{
			tmp->s_quote = false;
			tmp->d_quote = false;
			tmp->a_quote = true;
			return (true);
		}
		else if ((tmp->s_quote && tmp->c != '\'')
			|| (tmp->d_quote && tmp->c != '\"'))
		{
			if (seek_alone_quote(&tmp))
				return (true);
		}
		else
			return (false);
	}
	return (false);
}

/**
 * @brief Connect the quotes together and evaluate if any of them is not closed
 * @param lst Contain the whole command line characters in chained list
 * @return true if there are a non closed quote
 * @return false if all quotes are closed
 * @author xcharra
 */
bool	process_quotes(t_char_lst *lst)
{
	t_char_lst	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->c == '\'')
			process_single_quotes(&tmp);
		else if (tmp->c == '\"')
			process_double_quotes(&tmp);
		else
			tmp = tmp->next;
	}
	return (is_quote_alone(lst));
}
