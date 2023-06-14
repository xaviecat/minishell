/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syluiset <syluiset@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:30:33 by syluiset          #+#    #+#             */
/*   Updated: 2023/06/14 16:28:43 by syluiset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\nCtrl+C recu \n");
	}
	else if (signum == SIGQUIT)
	{
		printf("Ctrl+\\ recu\n");
	}
	else if (signum == SIGTSTP)
	{
		printf("Ctrl+D recu\n");
	}
}
