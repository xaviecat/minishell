/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:10:59 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/12 14:31:13 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	process_quotes(t_char_lst *lst)
{
	t_char_lst	*tmp;
	int			i;
	bool		sq;
	bool		dq;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (i == 0)
		{
			if (tmp->c == '\'')
			{
				tmp->quote = true;
				tmp = tmp->next;
			}
			else if (tmp->c == '\"')
			{
				tmp->d_quote = true;
				tmp = tmp->next;
			}
		}
		else
		{

		}
		i++;
	}
}