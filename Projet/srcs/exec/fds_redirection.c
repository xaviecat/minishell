/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:54:41 by xcharra           #+#    #+#             */
/*   Updated: 2023/10/10 13:13:29 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief create a fork to send the heredoc through the heredoc pipe to the
 * actual node
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 */
static void	handle_heredoc(t_msh *msh, int pipe_fd[3][2])
{
	pid_t		hdpid;

	if (pipe(pipe_fd[HD]) < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "pipe"));
	hdpid = fork();
	if (hdpid < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "fork"));
	else if (hdpid == 0)
	{
		while (msh->lst_n->heredoc)
		{
			ft_fdprintf(pipe_fd[HD][1], "%s\n", msh->lst_n->heredoc->word);
			msh->lst_n->heredoc = msh->lst_n->heredoc->next;
		}
		clear_mem_fds(msh, pipe_fd, EXIT_SUCCESS, NULL);
	}
	else
	{
		if (dup2(pipe_fd[HD][0], STDIN_FILENO) < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "dup2"));
		close_pipe(pipe_fd[HD]);
	}
}

/**
 * @brief redirects all fds that go to a node thanks to dup2
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 */
void	redirect_fds_in(t_msh *msh, int pipe_fd[3][2])
{
	if (msh->lst_n->fds && msh->lst_n->fds->in == -2)
		handle_heredoc(msh, pipe_fd);
	else if (msh->lst_n->fds && msh->lst_n->fds->in < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, NULL));
	else if (msh->lst_n->fds && msh->lst_n->fds->in > 0)
	{
		if (dup2(msh->lst_n->fds->in, STDIN_FILENO) < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "dup2"));
		close(msh->lst_n->fds->in);
	}
	else if (pipe_fd[PREV][0] != -1)
	{
		if (dup2(pipe_fd[PREV][0], STDIN_FILENO) < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "dup2"));
		close_pipe(pipe_fd[PREV]);
	}
}

/**
 * @brief redirects all fds that leave a node, thanks to dup2
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 */
void	redirect_fds_out(t_msh *msh, int pipe_fd[3][2])
{
	if (msh->lst_n->fds && msh->lst_n->fds->out < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, NULL));
	else if (msh->lst_n->fds && msh->lst_n->fds->out > 1)
	{
		if (dup2(msh->lst_n->fds->out, STDOUT_FILENO) < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "dup2"));
		close(msh->lst_n->fds->out);
		close_pipe(pipe_fd[PREV]);
	}
	else if (msh->lst_n->next)
	{
		if (dup2(pipe_fd[CURR][1], STDOUT_FILENO) < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "dup2"));
	}
	close_pipe(pipe_fd[CURR]);
}
