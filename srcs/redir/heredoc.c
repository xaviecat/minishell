/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaust <nfaust@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 13:35:07 by nfaust            #+#    #+#             */
/*   Updated: 2023/10/09 16:22:18 by nfaust           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/***
 * @brief displays the heredoc
 * @return the word list containing heredoc lines.
 * if no lines are entered returns null
 */
t_word_lst	*display_heredoc(t_word_lst *heredoc,
			t_msh *msh, t_redir_lst *redirs)
{
	destroy_heredoc(heredoc, &(msh->garbage));
	g_exit_status = 0;
	heredoc = run_heredoc(redirs->filename, &(msh->garbage));
	if ((!heredoc && errno == ENOMEM)
		|| (!does_contain_quotes(redirs->filename)
			&& !expand_heredoc(heredoc, msh)))
		return (NULL);
	return (heredoc);
}

/**
 * @brief displays and catches heredoc content
 * @return 0 on malloc issue, 2 if signals caught, 1 on success
 */
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
				if (!heredoc && g_exit_status == 130)
					return (2);
			}
			redirs = redirs->next;
		}
		msh->lst_n->heredoc = heredoc;
		msh->lst_n = msh->lst_n->next;
	}
	return (msh->lst_n = first, 1);
}
