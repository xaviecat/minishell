/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:52:25 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/03 13:33:00 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief In child process : call redirection functions and execute command by
 * execve or by builtins execution, in case of execve return the memory and the
 * fds are free and closed
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 */
void	child(t_msh *msh, int pipe_fd[3][2])
{
	redirect_fds_in(msh, pipe_fd);
	redirect_fds_out(msh, pipe_fd);
	signal_hub_exec();
	if (msh->lst_n->builtin == e_none && msh->lst_n->cmdpath)
		execve(msh->lst_n->cmdpath, msh->lst_n->cmdtab, msh->envp);
	else if (msh->lst_n->builtin < e_none)
		builtin_execution(msh);
	clear_mem_fds(msh, pipe_fd, g_exit_status, NULL);
}

/**
 * @brief In parent process : close the previous pipe if there one, if there is
 * a next node moves the fds from the current pipe to the previous pipe and if
 * there are not next node close the current pipe. If the actual node have fds
 * they are closed.
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 */
void	parent(t_msh *msh, int pipe_fd[3][2])
{
	if (pipe_fd[PREV][0] != -1)
		close_pipe(pipe_fd[PREV]);
	if (msh->lst_n->next)
	{
		pipe_fd[PREV][0] = pipe_fd[CURR][0];
		pipe_fd[PREV][1] = pipe_fd[CURR][1];
	}
	else
		close_pipe(pipe_fd[CURR]);
	if (msh->lst_n->fds)
	{
		if (msh->lst_n->fds->in > 0)
			close(msh->lst_n->fds->in);
		if (msh->lst_n->fds->out > 1)
			close(msh->lst_n->fds->out);
	}
}
