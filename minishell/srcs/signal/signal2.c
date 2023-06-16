/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:54:13 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/16 12:16:52 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	signal_term(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 128 + signum;
	}
}

void	signal_sigint(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_exit_status = 128 + signum;
}

void	signal_sigquit(int signum)
{
	ft_putendl_fd("Quit (core dumped)", 2);
	//write(2, "Quit (core dumped)\n", 19);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	g_exit_status = 128 + signum;
}

void	signal_heredoc(int signum)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 128 + signum;
}

void	signal_exec(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_status = 128 + signum;
	}
//	if (signum == SIGTSTP)
//	{
//		rl_redisplay();
//		g_exit_status = 128 + signum;
//	}
	if (signum == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_status = 128 + signum;
	}
}