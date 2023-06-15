/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:44:20 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 14:59:27 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief find which builtin as been called, and executed it
 * @param sh
 * @return 0 if an error occurred, 1 if it worked fine
 */
int	find_builtin(t_minish *sh)
{
	char	*cp_cmd;

	cp_cmd = ft_gbstrdup(sh->cmds->cmd->cmd, &(sh->garbage));
	if (ft_strncmp(cp_cmd, "exit", 5) == 0)
		b_exit(&sh);
	else if (ft_strncmp(cp_cmd, "echo", 5) == 0)
		b_echo(sh->cmds->cmd);
	else if (ft_strncmp(cp_cmd, "cd", 3) == 0)
		b_cd(sh->cmds->cmd, sh);
	else if (ft_strncmp(cp_cmd, "pwd", 4) == 0)
		b_pwd(sh->envp);
	else if (ft_strncmp(cp_cmd, "export", 7) == 0)
		b_export(sh, sh->cmds->cmd);
	else if (ft_strncmp(cp_cmd, "unset", 6) == 0)
	{
		if (!b_unset(sh))
			return (0);
	}
	else if (ft_strncmp(cp_cmd, "env", 4) == 0)
		b_env(sh->envp);
	return (1);
}
