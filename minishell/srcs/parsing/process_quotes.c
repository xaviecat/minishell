/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:10:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/15 19:02:44 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	is_quote_alone(t_char_lst *lst)
{
	t_char_lst	*tmp;

	tmp = char_lst_last(lst);
	while (tmp)
	{
		if (tmp->s_quote && tmp->c == '\'' && !tmp->prev->s_quote)
		{
			tmp->s_quote = false;
			tmp->a_quote = true;
			return ;
		}
		else if (tmp->d_quote && tmp->c == '\"' && !tmp->prev->d_quote)
		{
			tmp->d_quote = false;
			tmp->a_quote = true;
			return ;
		}
		else if (tmp->s_quote && tmp->c == '\'')
		{
			while (tmp && tmp->s_quote)
				tmp = tmp->prev;
		}
		else if (tmp->d_quote && tmp->c == '\"')
		{
			while (tmp && tmp->d_quote)
				tmp = tmp->prev;
		}
		else if (tmp->s_quote && tmp->c != '\'')
		{
			while (tmp && tmp->s_quote)
			{
				if (tmp->s_quote && tmp->c == '\'')
				{
					tmp->s_quote = false;
					tmp->a_quote = true;
					return ;
				}
				tmp->s_quote = false;
				tmp = tmp->prev;
			}
			tmp->s_quote = false;
		}
		else if (tmp->d_quote && tmp->c != '\"')
		{
			while (tmp && tmp->d_quote)
			{
				if (tmp->d_quote && tmp->c == '\"')
				{
					tmp->d_quote = false;
					tmp->a_quote = true;
					return ;
				}
				tmp->d_quote = false;
				tmp = tmp->prev;
			}
			tmp->d_quote = false;
		}
		else
			tmp = tmp->prev;
	}
}

void	process_quotes(t_char_lst *lst)
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
	is_quote_alone(lst);
}

/*
 * salut 'ca va' "la famille" '"'"
 * salut 'ca va' "la famille" '   ' "" '"'" "'"'
 */

