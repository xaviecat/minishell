/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:35:07 by nfaust            #+#    #+#             */
/*   Updated: 2023/06/19 14:30:26 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	heredoc_handling(t_msh *msh)
{
	t_node_lst		*first;
	t_redir_lst		*redirs;
	t_word_lst		*heredoc;

	first = msh->lst_n;
	while (msh->lst_n)
	{
		redirs = msh->lst_n->redirs;
		heredoc = NULL;
		while (redirs)
		{
			if (redirs->redir == inin)
			{
				heredoc = display_heredoc(heredoc, msh, redirs);
				if (!heredoc && errno == ENOMEM)
					return (0);
			}
			redirs = redirs->next;
		}
		msh->lst_n->heredoc = heredoc;
		msh->lst_n = msh->lst_n->next;
	}
	msh->lst_n = first;
	return (1);
}
