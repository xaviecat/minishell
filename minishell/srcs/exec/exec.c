/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/16 14:23:22 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Execute all function pars in the cmd_list, it should be an builtin or
 * a command with complete path
 * @param minish
 * @return 0 if all worked fine, 1 if an error occurred
 */
int	exec_all(t_msh *msh)
{
	t_node_lst	*first;

	first = msh->lst_n;
	while (msh->lst_n)
	{
		if (msh->lst_n->builtin > e_none)
			find_builtin(msh);
		else
		{
			if (msh->lst_n->lst_cmd)
				msh->lst_n->cmdtab = reforme_d_tab_cmd(&(msh->lst_n->lst_cmd),
								msh->lst_n->lst_cmd->cmd, &(msh->garbage));
		}
		msh->lst_n = msh->lst_n->next;
	}
	msh->lst_n = first;
	return (1);
}

void	execution(t_msh *msh)
{
	t_node_lst	*first;

	msh->prev_pipe[0] = -1;
	msh->prev_pipe[1] = -1;
	first = msh->lst_n;
	while (msh->lst_n)
	{
		if (pipe(msh->curr_pipe) < 0)
			return (perror("pipe error")); //! ERROR A CHECK
		msh->lst_n->pid = fork();
		if (msh->lst_n->pid < 0)
			return (perror("fork error")); //! ERROR A CHECK
		else if (msh->lst_n->pid == 0) //? Child
		{
			if (msh->lst_n->fds && msh->lst_n->fds->in > 0)
			{
				if (dup2(msh->lst_n->fds->in, STDIN_FILENO) < 0)
					return ; //! ERROR
				close(msh->prev_pipe[0]);
				close(msh->prev_pipe[1]);
			}
			else if (msh->prev_pipe[0] != -1)
			{
				if (dup2(msh->prev_pipe[0], STDIN_FILENO) < 0)
					return ; //! ERROR
				close(msh->prev_pipe[0]);
				close(msh->prev_pipe[1]);
			}
			if (msh->lst_n->fds && msh->lst_n->fds->out > 1)
			{
				if (dup2(msh->lst_n->fds->out, STDOUT_FILENO) < 0)
					return ; //! ERROR
				close(msh->prev_pipe[0]);
				close(msh->prev_pipe[1]);

			}
			else if (msh->lst_n->next)
			{
				if (dup2(msh->curr_pipe[1], STDOUT_FILENO) < 0)
					return ; //! ERROR
				close(msh->curr_pipe[0]);
				close(msh->curr_pipe[1]);
			}
			execve(msh->lst_n->cmdpath, msh->lst_n->cmdtab, msh->envp);
		}
		else //? Parent
		{
			if (msh->prev_pipe[0] != -1)
			{
				close(msh->prev_pipe[0]);
				close(msh->prev_pipe[1]);
			}
			if (msh->lst_n->next)
			{
				msh->prev_pipe[0] = msh->curr_pipe[0];
				msh->prev_pipe[1] = msh->curr_pipe[1];
			}
			else
			{
				close(msh->curr_pipe[0]);
				close(msh->curr_pipe[1]);
			}
			if (msh->lst_n->fds)
			{
				if (msh->lst_n->fds->in > 0)
					close(msh->lst_n->fds->in);
				if (msh->lst_n->fds->out > 0 && msh->lst_n->fds->out != 1)
					close(msh->lst_n->fds->out);
			}

		}
		msh->lst_n = msh->lst_n->next;
	}
	if (msh->prev_pipe[0] != -1)
	{
		close(msh->prev_pipe[0]);
		close(msh->prev_pipe[1]);
	}
	msh->lst_n = first;
	while (msh->lst_n && waitpid(msh->lst_n->pid, NULL, 0) > 0)
		if (msh->lst_n->next)
			msh->lst_n = msh->lst_n->next;
	msh->lst_n = first;
}