/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_is_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:14:27 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/01 15:03:48 by syluiset         ###   ########.fr       */
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
					ft_fdprintf(2, "syntax error near unexpected token `newline'\n");
				else
					ft_fdprintf(2, "syntax error near unexpected token `|'\n");
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

