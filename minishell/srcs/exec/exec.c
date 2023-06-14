/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 13:22:55 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exec_all(t_minish *minish)
{
	while (minish->cmds)
	{
		if (minish->cmds->builtin == true)
			find_builtin(minish);
		else
		{
			minish->cmds->cmdpath = ft_gbstrdup(minish->cmds->cmd->cmd,
					&(minish->garbage));
			minish->cmds->cmdtab = reforme_d_tab_cmd(&(minish->cmds->cmd),
					minish->cmds->cmdpath, &(minish->garbage));
		}
		minish->cmds = minish->cmds->next;
	}
}
