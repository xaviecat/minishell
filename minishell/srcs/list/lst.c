/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 17:19:21 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmd_list	*lst_cmd_new(t_w_cmd_list *cmds, t_fd_list *fds,
						t_redir_list *redir, t_garbage **gb)
{
	t_cmd_list	*new;

	new = ft_malloc(gb, sizeof(t_cmd_list), 1);
	if (!new)
		return (NULL);
	new->cmd = cmds;
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
