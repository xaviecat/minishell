/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_is_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:14:27 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/05 13:53:51 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	redir_is_valid(t_word_lst **lst, t_garbage **gb)
{
	while (*lst)
	{
		if ((*lst)->type == redir || (*lst)->type == hd \
			|| (*lst)->type == appnd || (*lst)->type == open_file)
		{
			if (!(*lst)->next || (*lst)->next->type == w_pipe)
			{
				if (!(*lst)->next)
					ft_fdprintf(2, RED NL_TKN RESET);
				else
					ft_fdprintf(2, RED PIPE_TKN RESET);
				free_error_word_lst(gb, lst);
				return (0);
			}
		}
		if ((*lst)->next)
			*lst = (*lst)->next;
		else
			break ;
	}
	while ((*lst)->prev)
		*lst = (*lst)->prev;
	return (1);
}

