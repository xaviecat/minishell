/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:54:13 by syluiset          #+#    #+#             */
/*   Updated: 2023/09/19 14:37:01 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/**
 * @brief The necessary function call to get a new line in the terminal
 * @param signum
 */
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

/**
 * @brief The necessary function call to get a new line in the heredoc
 * @param signum
 */
void	signal_heredoc(int signum)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_exit_status = 128 + signum;
}

/**
 * @brief The necessary function call to get a new line during execution
 * @param signum
 */
void	signal_exec(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_exit_status = 128 + signum;
	}
	if (signum == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", 2);
		g_exit_status = 128 + signum;
	}
}
