/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 16:21:31 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	exec_all(t_minish *msh)
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
}
