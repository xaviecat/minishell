/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:45:12 by syluiset          #+#    #+#             */
/*   Updated: 2023/10/10 13:16:00 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"
/**
 * @brief create a new node of fd_lst
 * @param gb
 * @return the new node
 */
t_fd_lst	*new_fds(t_garbage **gb)
{
	t_fd_lst	*fds;

	fds = ft_malloc(gb, sizeof(t_fd_lst), 1);
	if (!fds)
		return (NULL);
	fds->in = STDIN_FILENO;
	fds->out = STDOUT_FILENO;
	return (fds);
}

/**
 * @brief get the correct fds and stock it in the struct
 * @param fds
 * @param redirs
 */
void	get_fds(t_fd_lst **fds, t_redir_lst *redirs)
{
	if (redirs->redir == in)
		(*fds)->in = open(redirs->filename, O_RDONLY, 0444);
	if (redirs->redir == inin)
		(*fds)->in = -2;
	if (redirs->redir == out)
		(*fds)->out = open(redirs->filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (redirs->redir == outout)
		(*fds)->out = open(redirs->filename, O_RDWR | O_CREAT | O_APPEND, 0644);
}

/**
 * @brief create the list of all fds in the command
 * @param redirs
 * @param gb
 * @return the fd list created
 */
t_fd_lst	*create_fds_list(t_redir_lst *redirs, t_garbage **gb)
{
	t_fd_lst		*fds;

	if (!redirs)
		return (NULL);
	fds = new_fds(gb);
	if (!fds)
		return (NULL);
	if (redirs->redir != inin && !(del_quote_filename(&redirs, gb)))
		return (NULL);
	while (redirs)
	{
		if (fds->in > STDIN_FILENO && (redirs->redir == in
				|| redirs->redir == inin))
			close(fds->in);
		if (fds->out > STDOUT_FILENO && (redirs->redir == out
				|| redirs->redir == outout))
			close(fds->out);
		get_fds(&fds, redirs);
		if (fds->in == -1)
			return (perror(redirs->filename), fds);
		if (fds->out == -1)
			return (perror(redirs->filename), fds);
		redirs = redirs->next;
	}
	return (fds);
}
