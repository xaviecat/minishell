/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:23:46 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 14:23:46 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
