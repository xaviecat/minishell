/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:30:33 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/15 16:15:09 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

/////* TEST SIGNAL */
////
////struct	sigaction	sa_quit;
////struct	sigaction	sa_stop;
//////Ctrl+C
////sa_int.sa_handler = signal_handler;
////sa_int.sa_flags = 0;
////sigaction(SIGINT, &sa_int, NULL);
//////(Ctrl+\)
////sa_quit.sa_handler = signal_handler;
////sa_quit.sa_flags = 0;
//sigaction(SIGQUIT, &sa_quit, NULL);
//////Ctrl+D
////sa_stop.sa_handler = signal_handler;
////sa_stop.sa_flags = 0;
//sigaction(SIGTSTP, &sa_stop, NULL);

void	signal_hub_term(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_term;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_hub_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_hub_exec(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_exec;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
