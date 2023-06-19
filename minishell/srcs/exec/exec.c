/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/19 18:57:25 by xcharra          ###   ########.fr       */
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
		{
			if (!find_builtin(msh))
				return (0);
		}
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

void	close_pipe(int pipefd[2])
{
	if (pipefd[0] > 0)
		close(pipefd[0]);
	if (pipefd[1] > 0)
		close(pipefd[1]);
}

void	handle_heredoc(t_msh *msh, int *curr_pipe)
{
	int			pipe_hd[2];
	pid_t		hdpid;

	if (pipe(pipe_hd) < 0)
		return ; //! ERROR
	hdpid = fork();
	if (hdpid < 0)
		return ; //! ERROR
	else if (hdpid == 0) //? Child heredoc
	{
//					dprintf(2, GREEN"hdchild = [%d]\n"RESET, getpid());
		while (msh->lst_n->heredoc)
		{
			ft_fdprintf(pipe_hd[1], "%s\n", msh->lst_n->heredoc->word);
			msh->lst_n->heredoc = msh->lst_n->heredoc->next;
		}
		close_pipe(curr_pipe);
		close_pipe(pipe_hd);
		exit(EXIT_SUCCESS);
	}
	else //? Parents heredoc
	{
		if (dup2(pipe_hd[0], STDIN_FILENO) < 0)
			return ; //! ERROR
		close_pipe(pipe_hd);
	}
}

void	child(t_msh *msh, int *prev_pipe, int *curr_pipe)
{
//			dprintf(2, GREEN"child = [%d]\n"RESET, getpid());
	if (msh->lst_n->heredoc)
		handle_heredoc(msh, curr_pipe);
	else if (msh->lst_n->fds && msh->lst_n->fds->in > 0)
	{
		if (dup2(msh->lst_n->fds->in, STDIN_FILENO) < 0)
			return ; //! ERROR
		close_pipe(prev_pipe);
	}
	else if (prev_pipe[0] != -1)
	{
		if (dup2(prev_pipe[0], STDIN_FILENO) < 0)
			return ; //! ERROR
		close_pipe(prev_pipe);
	}
	if (msh->lst_n->fds && msh->lst_n->fds->out > 1)
	{
		if (dup2(msh->lst_n->fds->out, STDOUT_FILENO) < 0)
			return ; //! ERROR
		close_pipe(prev_pipe);
	}
	else if (msh->lst_n->next)
	{
		if (dup2(curr_pipe[1], STDOUT_FILENO) < 0)
			return ; //! ERROR
		close_pipe(prev_pipe);
	}
	signal_hub_exec();
	if (msh->lst_n->cmdpath)
		execve(msh->lst_n->cmdpath, msh->lst_n->cmdtab, msh->envp);
	exit(EXIT_FAILURE); //! en cas d'erreur set le exit code
}

void	forking(t_msh *msh)
{
	t_node_lst	*first;
	int			status_pid;
	int			prev_pipe[2];
	int			curr_pipe[2];

	status_pid = 0;
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	first = msh->lst_n;
	signal_hub_ign();
	while (msh->lst_n)
	{
		if (pipe(curr_pipe) < 0)
			return (perror("pipe error")); //! ERROR A CHECK
		msh->lst_n->pid = fork();
		if (msh->lst_n->pid < 0)
			return (perror("fork error")); //! ERROR A CHECK
		else if (msh->lst_n->pid == 0) //? Child
		{
			child(msh, prev_pipe, curr_pipe);
		}
		else //? Parent
		{
			if (prev_pipe[0] != -1)
				close_pipe(prev_pipe);
			if (msh->lst_n->next)
			{
				prev_pipe[0] = curr_pipe[0];
				prev_pipe[1] = curr_pipe[1];
			}
			else
				close_pipe(curr_pipe);
			if (msh->lst_n->fds)
			{
				if (msh->lst_n->fds->in > 0)
					close(msh->lst_n->fds->in);
				if (msh->lst_n->fds->out > 1)
					close(msh->lst_n->fds->out);
			}

		}
		msh->lst_n = msh->lst_n->next;
	}
	if (prev_pipe[0] != -1)
		close_pipe(prev_pipe);
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

void	execution(t_msh *msh)
{
	pid_t	main_fork;

//	dprintf(2, GREEN"parents = [%d]\n"RESET, getpid());
	main_fork = fork();
	if (main_fork < 0)
		return ;
	else if (main_fork == 0)
	{
//		dprintf(2, GREEN"main_fork = [%d]\n"RESET, getpid());
		forking(msh);
	}
	else
		waitpid(main_fork, 0, 0);
}
