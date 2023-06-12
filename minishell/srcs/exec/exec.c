/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/12 16:53:11 by syluiset         ###   ########.fr       */
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
			minish->cmds->cmd_c = ft_gb_strdup(minish->cmds->cmd->cmd,
					&(minish->garbage));
			minish->cmds->cmd_tab = reforme_d_tab_cmd(&(minish->cmds->cmd),
					minish->cmds->cmd_c, &(minish->garbage));
		}
		minish->cmds = minish->cmds->next;
	}
}
