/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/15 16:14:22 by xcharra          ###   ########.fr       */
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
	t_cmd_list	*first;

	first = msh->cmds;
	while (msh->cmds)
	{
		if (msh->cmds->builtin == true)
			find_builtin(msh);
		else
		{
			if (msh->cmds->cmd)
				msh->cmds->cmdtab = reforme_d_tab_cmd(&(msh->cmds->cmd),
						msh->cmds->cmd->cmd, &(msh->garbage));
		}
		msh->cmds = msh->cmds->next;
	}
	msh->cmds = first;
	return (1);
}

void	execution(t_minish *msh)
{
	t_cmd_list	*first;

	msh->prev_pipe[0] = -1;
	msh->prev_pipe[1] = -1;
	first = msh->cmds;
	while (msh->cmds)
	{
		if (pipe(msh->curr_pipe) < 0)
			return (perror("pipe error")); //! ERROR A CHECK
		msh->cmds->pid = fork();
		if (msh->cmds->pid < 0)
			return (perror("fork error")); //! ERROR A CHECK
		else if (msh->cmds->pid == 0) //? Child
		{
			if (msh->prev_pipe[0] != -1)
			{
				dup2(msh->prev_pipe[0], STDIN_FILENO);
				close(msh->prev_pipe[0]);
				close(msh->prev_pipe[1]);
			}
			if (msh->cmds->next)
			{
				dup2(msh->curr_pipe[1], STDOUT_FILENO);
				close(msh->curr_pipe[0]);
				close(msh->curr_pipe[1]);
			}
//			for (int j; msh->cmds->cmdtab[j]; j++ )
//				ft_fdprintf(2, BGRED"[%d] = %s\n"RESET RESET, j, msh->cmds->cmdtab[j]);
			execve(msh->cmds->cmdpath, msh->cmds->cmdtab, msh->envp);
		}
		else //? Parent
		{
			if (msh->prev_pipe[0] != -1)
			{
				close(msh->prev_pipe[0]);
				close(msh->prev_pipe[1]);
			}
			if (msh->cmds->next)
			{
				msh->prev_pipe[0] = msh->curr_pipe[0];
				msh->prev_pipe[1] = msh->curr_pipe[1];
			}
		}
		msh->cmds = msh->cmds->next;
	}
	if (msh->prev_pipe[0] != -1)
	{
		close(msh->prev_pipe[0]);
		close(msh->prev_pipe[1]);
	}
	msh->cmds = first;
	while (msh->cmds && waitpid(msh->cmds->pid, NULL, 0) > 0)
		if (msh->cmds->next)
			msh->cmds = msh->cmds->next;
	msh->cmds = first;
}