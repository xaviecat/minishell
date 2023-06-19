/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 19:25:52 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/19 14:48:15 by syluiset         ###   ########.fr       */
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

void	execution(t_msh *msh)
{
	t_node_lst	*first;
	int			status_pid;

	status_pid = 0;
	msh->prev_pipe[0] = -1;
	msh->prev_pipe[1] = -1;
	first = msh->lst_n;
	signal_hub_ign();
	while (msh->lst_n)
    {
		if (pipe(msh->curr_pipe) < 0)
			return (perror("pipe error")); //! ERROR A CHECK
		msh->lst_n->pid = fork();
		if (msh->lst_n->pid < 0)
			return (perror("fork error")); //! ERROR A CHECK
		else if (msh->lst_n->pid == 0) //? Child
		{
			if (msh->lst_n->heredoc)
			{
				if (pipe(msh->lst_n->pipehd) < 0)
					return ; //! ERROR
				msh->lst_n->hdpid = fork();
				if (msh->lst_n->hdpid < 0)
					return ; //! ERROR
				else if (msh->lst_n->hdpid == 0) //? Child heredoc
				{
					while (msh->lst_n->heredoc)
					{
						ft_fdprintf(msh->lst_n->pipehd[1], "%s\n",
							msh->lst_n->heredoc->word);
						msh->lst_n->heredoc = msh->lst_n->heredoc->next;
					}
					close(msh->lst_n->pipehd[0]);
					close(msh->lst_n->pipehd[1]);
					exit(EXIT_SUCCESS);
				}
				else //? Parents heredoc
				{
					if (dup2(msh->lst_n->pipehd[0], STDIN_FILENO) < 0)
						return ; //! ERROR
					close(msh->lst_n->pipehd[0]);
					close(msh->lst_n->pipehd[1]);
				}
			}
			else if (msh->lst_n->fds && msh->lst_n->fds->in > 0)
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
			signal_hub_exec();
			if (msh->lst_n->cmdpath)
				execve(msh->lst_n->cmdpath, msh->lst_n->cmdtab, msh->envp);
			//! ERROR
			//perror(msh->lst_n->cmdtab[0]);
			exit(EXIT_FAILURE);
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