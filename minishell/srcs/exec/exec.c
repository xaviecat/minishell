/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 15:03:06 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Execute all function pars in the cmd_list, it should be an builtin or
 * a command with complete path
 * @param minish
 * @return 0 if all worked fine, 1 if an error occurred
 */
int	exec_all(t_minish *minish)
{
	while (minish->cmds)
	{
		if (minish->cmds->builtin == true)
		{
			if (!find_builtin(minish))
				return (0);
		}
		else
		{
			minish->cmds->cmdpath = ft_gbstrdup(minish->cmds->cmd->cmd,
					&(minish->garbage));
			minish->cmds->cmdtab = reforme_d_tab_cmd(&(minish->cmds->cmd),
					minish->cmds->cmdpath, &(minish->garbage)); //peut renvoyer NULL
		}
		minish->cmds = minish->cmds->next;
	}
	return (1);
}
