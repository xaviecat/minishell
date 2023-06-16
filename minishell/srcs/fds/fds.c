/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:45:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/15 17:17:57 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_fd_lst	*create_fd(t_garbage **gb, t_redir_lst *redirs)
{
	t_fd_lst	*new;

	new = new_fds(gb);
	if (!new)
		return (NULL);
	if (redirs->redir == in)
		new->in = open(redirs->filename, O_RDONLY, 0444);
	//		if (redirs->redir == inin)
	//			new->in = ;//HEREDOC
	if (redirs->redir == out)
		new->out = open(redirs->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (redirs->redir == outout)
		new->out = open(redirs->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	return (new);
}

t_fd_lst	*create_fds_list(t_redir_lst *redirs, t_garbage **gb)
{
	t_fd_lst		*fds;
	t_fd_lst		*new;

	if (!redirs)
		return (NULL);
	fds = new_fds(gb);
	if (!fds)
		return (NULL);
	while (redirs)
	{
		if (fds->in != STDIN_FILENO)
			close(fds->in);
		if (fds->out != STDOUT_FILENO)
			close(fds->out);
		new = create_fd(gb, redirs);
		if (!new)
			return (free_error_fds(gb, &fds), NULL);
		fds_add_back(&fds, new);
		if (new->in == -1)
			return (perror(redirs->filename), fds);
		if (new->out == -1)
			return (perror(redirs->filename), fds);
		redirs = redirs->next;
	}
	return (fds);
}
