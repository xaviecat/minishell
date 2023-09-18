/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/30 10:26:09 by xcharra          ###   ########.fr       */
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

void	init_pipe_fd(int pipe_fd[3][2])
{
	pipe_fd[PREV][0] = -1;
	pipe_fd[PREV][1] = -1;
	pipe_fd[CURR][0] = -1;
	pipe_fd[CURR][1] = -1;
	pipe_fd[HD][0] = -1;
	pipe_fd[HD][1] = -1;
}

void	close_pipe(int pipe[2])
{
	if (!pipe)
		return ;
	if (pipe[0] > 0)
		close(pipe[0]);
	if (pipe[1] > 0)
		close(pipe[1]);

}

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

void	handle_heredoc(t_msh *msh, int pipe_fd[3][2])
{
	pid_t		hdpid;

	if (pipe(pipe_fd[HD]) < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "pipe"));
//	dprintf(2, GREEN"pipe_hd[0] = [%d], pipe_hd[1] = [%d]\n"RESET, pipe_fd[HD][0], pipe_fd[HD][1]);
	hdpid = fork();
	if (hdpid < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "fork"));
	else if (hdpid == 0) //? Child heredoc
	{
//		dprintf(2, GREEN"hdchild = [%d]\n"RESET, getpid());
		while (msh->lst_n->heredoc)
		{
			ft_fdprintf(pipe_fd[HD][1], "%s\n", msh->lst_n->heredoc->word);
			msh->lst_n->heredoc = msh->lst_n->heredoc->next;
		}
		clear_mem_fds(msh, pipe_fd, EXIT_SUCCESS, NULL);
	}
	else //? Parents heredoc
	{
		if (dup2(pipe_fd[HD][0], STDIN_FILENO) < 0)
			return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, "dup2"));
//		close_pipe(pipe_fd[CURR]); //! HD CURR
		close_pipe(pipe_fd[HD]);
	}
}

void	redirect_fds_in(t_msh *msh, int pipe_fd[3][2])
{
	if (msh->lst_n->heredoc)
		handle_heredoc(msh, pipe_fd);
	else if (msh->lst_n->fds && msh->lst_n->fds->in < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, NULL)); //! ERROR A GERER
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

void	redirect_fds_out(t_msh *msh, int pipe_fd[3][2])
{
	if (msh->lst_n->fds && msh->lst_n->fds->out < 0)
		return (clear_mem_fds(msh, pipe_fd, EXIT_FAILURE, NULL)); //! ERROR A GERER
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
		close_pipe(pipe_fd[CURR]);
	}
}

void	builtin_execution(t_msh *msh)
{
	static t_builtin_tab	builtin_tab[8] = {&b_echo, &b_env, &b_pwd, &b_cd,
		b_export, &b_unset, &b_exit, NULL};

	g_exit_status = builtin_tab[msh->lst_n->builtin](msh);
}

void	child(t_msh *msh, int pipe_fd[3][2])
{
//	dprintf(2, GREEN"child = [%d]\n"RESET, getpid());
	redirect_fds_in(msh, pipe_fd);
	redirect_fds_out(msh, pipe_fd);
	signal_hub_exec();
	if (msh->lst_n->builtin == e_none && msh->lst_n->cmdpath)
		execve(msh->lst_n->cmdpath, msh->lst_n->cmdtab, msh->envp);
	else if (msh->lst_n->builtin < e_none)
		builtin_execution(msh);
	clear_mem_fds(msh, pipe_fd, g_exit_status, NULL);
}

void	parent(t_msh *msh, int pipe_fd[3][2])
{
	if (pipe_fd[PREV][0] != -1)
	{
		close(pipe_fd[PREV][0]);
		close(pipe_fd[PREV][1]);
	}
	if (msh->lst_n->next)
	{
		pipe_fd[PREV][0] = pipe_fd[CURR][0];
		pipe_fd[PREV][1] = pipe_fd[CURR][1];
	}
	else
	{
		close(pipe_fd[CURR][0]);
		close(pipe_fd[CURR][1]);
	}
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
		waitpid(msh->lst_n->pid, &status_pid, 0);
		if (WIFSIGNALED(status_pid))
			signal_exec(WTERMSIG(status_pid));
		else
			g_exit_status = WEXITSTATUS(status_pid);
//		if (g_exit_status == EXIT_FAILURE)
//			return (clear_mem_fds(msh, NULL, EXIT_FAILURE, NULL));
		msh->lst_n = msh->lst_n->next;
	}
	signal_hub_exec();
	msh->lst_n = first;
}

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

void	execution(t_msh *msh)
{
//	dprintf(2, GREEN"parents = [%d]\n"RESET, getpid());
//	dprintf(2, GREEN"%zu\n"RESET, msh->n_node);
	if ((msh->n_node >= 1 && (msh->lst_n->builtin < e_cd
				|| msh->lst_n->builtin == e_none)) || msh->n_node > 1)
		forking(msh);
	else if (msh->n_node == 1 && msh->lst_n->builtin >= e_cd)
		builtin_execution(msh);
}

/*
 *
 * <<eof cat | cat -e > out | cat <out1 < out2 < out
 *
 * */
