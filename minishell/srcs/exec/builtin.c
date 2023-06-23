/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:44:20 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/16 16:49:04 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief find which builtin as been called, and executed it
 * @param sh
 * @return 0 if an error occurred, 1 if it worked fine
 */
int	find_builtin(t_msh *sh)
{
	char	*cp_cmd;

	cp_cmd = ft_gbstrdup(sh->lst_n->lst_cmd->cmd, &(sh->garbage));
	if (ft_strncmp(cp_cmd, "exit", 5) == 0)
		b_exit(sh);
	else if (ft_strncmp(cp_cmd, "echo", 5) == 0)
		g_exit_status = b_echo(sh);
	else if (ft_strncmp(cp_cmd, "cd", 3) == 0)
		g_exit_status = b_cd(sh);
	else if (ft_strncmp(cp_cmd, "pwd", 4) == 0)
		g_exit_status = b_pwd(sh);
	else if (ft_strncmp(cp_cmd, "export", 7) == 0)
		g_exit_status = b_export(sh);
	else if (ft_strncmp(cp_cmd, "unset", 6) == 0)
		g_exit_status = b_unset(sh);
	else if (ft_strncmp(cp_cmd, "env", 4) == 0)
		g_exit_status = b_env(sh);
	if (g_exit_status == ENOMEM)
		return (0);
	return (1);
}
