/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:02:59 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/16 14:31:36 by xcharra          ###   ########.fr       */
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
	new->builtin = e_none;
	new->redirs = redir;
	new->fds = fds;
	new->cmdpath = NULL;
	new->cmdtab = NULL;
	new->heredoc = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * @brief find the good builtin if cmd is a builtin
 * @param cmd
 * @return the type of builtin of e_none if it is a non builtin command
 */
t_builtin	builtin_or_command(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (e_exit);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (e_echo);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (e_cd);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (e_pwd);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (e_export);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (e_unset);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (e_env);
	return (e_none);
}
