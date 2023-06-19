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
	t_node_lst		*cmds;
	t_redir_lst		*redirs;
	t_word_lst		*heredoc;

	cmds = msh->lst_n;
	while (cmds)
	{
		redirs = cmds->redirs;
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
		cmds = cmds->next;
	}
	return (1);
}
