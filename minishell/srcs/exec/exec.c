/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 18:36:14 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Execute all function pars in the cmd_list, it should be an builtin or
 * a command with complete path
 * @param minish
 * @return 0 if all worked fine, 1 if an error occurred
 */
int	exec_all(t_minish *msh)
{
	while (msh->cmds)
	{
		if (msh->cmds->builtin == true)
			find_builtin(msh);
		else
		{
			if (msh->cmds->cmd)
				msh->cmds->cmdtab = reforme_d_tab_cmd(&(msh->cmds->cmd),
						msh->cmds->cmdpath, &(msh->garbage));
		}
		msh->cmds = msh->cmds->next;
	}
	return (1);
}
