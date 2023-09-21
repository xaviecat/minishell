/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_fds_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:39:22 by xcharra           #+#    #+#             */
/*   Updated: 2023/09/21 16:50:47 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief Initialize each boxes of pipe_fd tab at -1 to facilitate error
 * management and closing of fds
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 */
void	init_pipe_fd(int pipe_fd[3][2])
{
	pipe_fd[PREV][0] = -1;
	pipe_fd[PREV][1] = -1;
	pipe_fd[CURR][0] = -1;
	pipe_fd[CURR][1] = -1;
	pipe_fd[HD][0] = -1;
	pipe_fd[HD][1] = -1;
}

/**
 * @brief Close each end of a pipe if there are > 0
 * @param pipe[2] a pipe
 */
void	close_pipe(int pipe[2])
{
	if (!pipe)
		return ;
	if (pipe[0] > 0)
		close(pipe[0]);
	if (pipe[1] > 0)
		close(pipe[1]);
}

/**
 * @brief Close all open fds which come from pipe or file opening
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 */
void	close_all(int pipe_fd[3][2], t_msh *msh)
{
	t_node_lst	*current;

	current = msh->lst_n;
	if (pipe_fd)
	{
		close_pipe(pipe_fd[PREV]);
		close_pipe(pipe_fd[CURR]);
		close_pipe(pipe_fd[HD]);
	}
	while (msh->lst_n->prev)
		msh->lst_n = msh->lst_n->prev;
	while (msh->lst_n)
	{
		if (msh->lst_n->fds)
		{
			if (msh->lst_n->fds->in > 0)
				close(msh->lst_n->fds->in);
			if (msh->lst_n->fds->out > 1)
				close(msh->lst_n->fds->out);
		}
		msh->lst_n = msh->lst_n->next;
	}
	msh->lst_n = current;
}

/**
 * @brief Close all fds and free all the malloc'd memory, and may display an
 * error message and can exit the minishell
 * @param msh global struct that contain all of command and other stuff
 * necessary to the execution
 * @param pipe_fd[3][2] int tab with 3 pipe fds
 * @param mode if there are mode > 0 this function exit minishell and set an
 * exit  code
 * @param why if why is non null then perror display the adequate error
 */
void	clear_mem_fds(t_msh *msh, int pipe_fd[3][2], int mode, char *why)
{
	close_all(pipe_fd, msh);
	ft_free_all(&(msh->garbage));
	free(msh->garbage);
	free(msh);
	rl_clear_history();
	if (why)
		perror(why);
	if (mode >= 0)
		exit(mode);
}
