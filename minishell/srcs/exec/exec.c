/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/16 12:32:20 by syluiset         ###   ########.fr       */
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
		if (msh->lst_n->builtin == true)
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
	int			status_pid;

	status_pid = 0;
	msh->prev_pipe[0] = -1;
	msh->prev_pipe[1] = -1;
	first = msh->lst_n;
	//signal_hub_ign();
	while (msh->lst_n)
	{
		if (pipe(msh->curr_pipe) < 0)
			return (perror("pipe error")); //! ERROR A CHECK
		msh->lst_n->pid = fork();
		if (msh->lst_n->pid < 0)
			return (perror("fork error")); //! ERROR A CHECK
		else if (msh->lst_n->pid == 0) //? Child
		{
			if (msh->prev_pipe[0] != -1)
			{
				dup2(msh->prev_pipe[0], STDIN_FILENO);
				close(msh->prev_pipe[0]);
				close(msh->prev_pipe[1]);
			}
			if (msh->lst_n->next)
			{
				dup2(msh->curr_pipe[1], STDOUT_FILENO);
				close(msh->curr_pipe[0]);
				close(msh->curr_pipe[1]);
			}
			signal_hub_exec();
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
		}
		msh->lst_n = msh->lst_n->next;
	}
	if (msh->prev_pipe[0] != -1)
	{
		close(msh->prev_pipe[0]);
		close(msh->prev_pipe[1]);
	}
	msh->lst_n = first;
	while (msh->lst_n)
	{
	//	if (msh->lst_n->next)
		waitpid(msh->lst_n->pid, &status_pid, 0);
		if (WIFSIGNALED(status_pid))
		{
//			if (WTERMSIG(status_pid) == SIGINT)
//				signal_sigint(SIGINT);
//			else if (WTERMSIG(SIGQUIT))
//				signal_sigquit(SIGQUIT);
			signal_exec(WTERMSIG(status_pid));
		}
		else
			g_exit_status = WEXITSTATUS(status_pid);
		//if (g_exit_status == EXIT_FAILURE)
			//return ; //TOUT FREE AND EXIT avec code failure
		msh->lst_n = msh->lst_n->next;
	}
	signal_hub_exec();
	msh->lst_n = first;
}