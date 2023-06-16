/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/15 17:18:26 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_node_lst	*lst_cmd_new(t_cmd_lst *cmds, t_fd_lst *fds,
						   t_redir_lst *redir, t_garbage **gb)
{
	t_node_lst	*new;

	new = ft_malloc(gb, sizeof(t_node_lst), 1);
	if (!new)
		return (NULL);
	new->lst_cmd = cmds;
	new->builtin = false;
	new->redirs = redir;
	new->fds = fds;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

bool	builtin_or_command(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (true);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (true);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (true);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (true);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (true);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (true);
	return (false);
}
