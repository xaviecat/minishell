/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:10:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/15 12:17:55 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	process_single_quotes(t_char_lst **tmp)
{
	bool		sq;

	sq = true;
	(*tmp)->quote = true;
	(*tmp) = (*tmp)->next;
	while ((*tmp) && sq == true)
	{
		(*tmp)->quote = true;
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
	while ((*tmp) && dq == true)
	{
		(*tmp)->d_quote = true;
		if ((*tmp)->c == '\"')
			dq = false;
		(*tmp) = (*tmp)->next;
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
}
