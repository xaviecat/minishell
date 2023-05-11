/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xcharra <xcharra@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:09:22 by xcharra           #+#    #+#             */
/*   Updated: 2023/05/11 14:39:25 by xcharra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h'
#include "../../incs/minishell.h"

void	seek_redirection(t_minish *mnsh)
{
	t_cmd_list	*cmdlst;
	int 		i;
	int 		c;

	cmdlst = mnsh->cmd;
	i = 0;
	c = 0;
	while(cmdlst)
	{
		while (cmdlst->cmd[0][i] != '<')
			i++;
		while (cmdlst->cmd[0][i + c] == '<')
			c++;
		while (cmdlst->cmd[0][i + c] != '<' || cmdlst->cmd[0][i + c] != ' ')
			i++;
		cmdlst = cmdlst->next;
		i = 0;
	}
}