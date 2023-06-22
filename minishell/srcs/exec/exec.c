/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/21 19:03:06 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	get_cmdtab(t_msh *msh)
{
	t_node_lst	*first;

	first = msh->lst_n;
	while (msh->lst_n)
	{
		if (msh->lst_n->lst_cmd)
			msh->lst_n->cmdtab = create_cmdtab(msh->lst_n->lst_cmd,
					&(msh->garbage));
		msh->lst_n = msh->lst_n->next;
	}
	msh->lst_n = first;
	return (1);
}

void	close_pipe(int pipefd[2])
{
	if (!pipefd)
		return ;
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
//		dprintf(2, GREEN"hdchild = [%d]\n"RESET, getpid());
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

void	redirect_fds_in(t_msh *msh, int *prev_pipe, int *curr_pipe)
{

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
}

void	redirect_fds_out(t_msh *msh, int *prev_pipe, int *curr_pipe)
{
	if (msh->lst_n->fds && msh->lst_n->fds->out > 1)
	{
		if (dup2(msh->lst_n->fds->out, STDOUT_FILENO) < 0)
			return; //! ERROR
		close_pipe(prev_pipe);
	}
	else if (msh->lst_n->next)
	{
		if (dup2(curr_pipe[1], STDOUT_FILENO) < 0)
			return; //! ERROR
		close_pipe(curr_pipe);
	}
}

void	builtin_execution(t_msh *msh)
{
	static t_builtin_tab	builtin_tab[8] = {&b_echo, &b_env, &b_pwd, &b_cd, NULL
		/*&b_export*/, &b_unset, &b_exit, NULL};
//	int ret_val;

//	ret_val = 0;
//	ft_fdprintf(2, RED"builtin = %d\n"RESET, msh->lst_n->builtin);
	builtin_tab[msh->lst_n->builtin](msh);
}

void	child(t_msh *msh, int *prev_pipe, int *curr_pipe)
{
	//dprintf(2, GREEN"child = [%d]\n"RESET, getpid());
	redirect_fds_in(msh, prev_pipe, curr_pipe);
	redirect_fds_out(msh, prev_pipe, curr_pipe);
	signal_hub_exec();
	close_pipe(prev_pipe);
	close_pipe(curr_pipe);
	if (msh->lst_n->builtin == e_none && msh->lst_n->cmdpath)
		execve(msh->lst_n->cmdpath, msh->lst_n->cmdtab, msh->envp);
	else if (msh->lst_n->builtin < e_none)
		builtin_execution(msh);
	exit(msh->lst_n->exit_code); //! en cas d'erreur set le exit code
}

void	parent(t_msh *msh, int *prev_pipe, int *curr_pipe)
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

void	wait_fork(t_msh *msh, int status_pid)
{
	t_node_lst	*first;

	first = msh->lst_n;
	while (msh->lst_n)
	{
		//	if (msh->lst_n->next)
		waitpid(msh->lst_n->pid, &status_pid, 0);
		if (WIFSIGNALED(status_pid))
			signal_exec(WTERMSIG(status_pid));
		else
			g_exit_status = WEXITSTATUS(status_pid);
		//if (g_exit_status == EXIT_FAILURE)
		//return ; //TOUT FREE AND EXIT avec code failure
		msh->lst_n = msh->lst_n->next;
	}
	signal_hub_exec();
	msh->lst_n = first;
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
			child(msh, prev_pipe, curr_pipe);
		else //? Parent
			parent(msh, prev_pipe, curr_pipe);
		msh->lst_n = msh->lst_n->next;
		usleep(1000);
	}
	if (prev_pipe[0] != -1)
		close_pipe(prev_pipe);
	msh->lst_n = first;
	wait_fork(msh, status_pid);
}

void	execution(t_msh *msh)
{
//	dprintf(2, GREEN"parents = [%d]\n"RESET, getpid());
//	dprintf(2, GREEN"%zu\n"RESET, msh->n_node);
	if (msh->n_node >= 1 && (msh->lst_n->builtin < e_cd
			|| msh->lst_n->builtin == e_none))
		forking(msh);
	else if (msh->n_node == 1 && msh->lst_n->builtin >= e_cd)
		builtin_execution(msh);
}
