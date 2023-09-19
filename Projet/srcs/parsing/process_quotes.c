/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:10:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/19 13:50:36 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Connect the single quotes together
 * @author xcharra
 */
void	process_single_quotes(t_char_lst **tmp, bool *q)
{
	(*tmp)->s_quote = true;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && *q)
	{
		(*tmp)->s_quote = true;
		if ((*tmp)->c == '\'')
			*q = false;
		(*tmp) = (*tmp)->next;
	}
}

/**
 * @brief Connect the double quotes together
 * @author xcharra
 */
void	process_double_quotes(t_char_lst **tmp, bool *q)
{
	(*tmp)->d_quote = true;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && *q)
	{
		(*tmp)->d_quote = true;
		if ((*tmp)->c == '\"')
			*q = false;
		(*tmp) = (*tmp)->next;
	}
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
	bool		q;

	tmp = lst;
	q = false;
	while (tmp)
	{
		if (tmp->c == '\'')
		{
			q = true;
			process_single_quotes(&tmp, &q);
		}
		else if (tmp->c == '\"')
		{
			q = true;
			process_double_quotes(&tmp, &q);
		}
		else
			tmp = tmp->next;
	}
	if (q == true)
		return (ft_fdprintf(2, MSH UN_QUOTE), true);
	else
		return (false);
}
