/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:50:49 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/03 13:32:49 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief wait for the fork, and get their status_pid
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param status_pid
 */
static void	wait_fork(t_msh *msh, int status_pid)
{
	t_node_lst	*first;

	first = msh->lst_n;
	while (msh->lst_n)
	{
		waitpid(msh->lst_n->pid, &status_pid, 0);
		if (WIFSIGNALED(status_pid))
			signal_exec(WTERMSIG(status_pid));
		else
			g_exit_status = WEXITSTATUS(status_pid);
		msh->lst_n = msh->lst_n->next;
	}
	signal_hub_exec();
	msh->lst_n = first;
}

/**
 * @brief initialize a pipe and create a new process and iterate in the node
 * list and redo
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 */
void	forking(t_msh *msh)
{
	t_node_lst	*first;
	int			status_pid;
	int			pipe_fd[3][2];

	status_pid = 0;
	init_pipe_fd(pipe_fd);
	first = msh->lst_n;
	signal_hub_ign();
	while (msh->lst_n)
	{
		if (pipe(pipe_fd[CURR]) < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "pipe"));
		msh->lst_n->pid = fork();
		if (msh->lst_n->pid < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "fork"));
		else if (msh->lst_n->pid == 0)
			child(msh, pipe_fd);
		else
			parent(msh, pipe_fd);
		msh->lst_n = msh->lst_n->next;
	}
	if (pipe_fd[PREV][0] != -1)
		close_pipe(pipe_fd[PREV]);
	msh->lst_n = first;
	wait_fork(msh, status_pid);
}
